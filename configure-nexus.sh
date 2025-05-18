#!/bin/bash
set -euo pipefail

# === Configuration ===
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
source "$SCRIPT_DIR/.env"

NEXUS_URL="http://${NEXUS_HOST}:${NEXUS_PORT}"
ROLE_ID="anonymous-deploy"
ROLE_NAME="Anonymous Deploy Role"
ROLE_DESC="Allow anonymous to deploy to conan-hosted"
ROLE_PRIVILEGES=(
    nx-repository-view-conan-conan-hosted-add
    nx-repository-view-conan-conan-hosted-edit
    nx-repository-view-conan-conan-hosted-read
)
CONAN_UPLOAD_USER="conan-upload"
CONAN_UPLOAD_PASSWORD="Abcd1234!"


# === Utilities ===

log_info() {
    echo "[INFO] $*"
}

log_error() {
    echo "[ERROR] $*" >&2
}

get_preseeded_admin_password() {
    docker exec nexus sh -c 'cat /nexus-data/admin.password 2>/dev/null || true'
}

call_nexus_api() {
    local method="$1"
    local endpoint="$2"
    local data="${3:-}"
    local curl_args=(-s -f -u "${NEXUS_ADMIN_USER}:${NEXUS_ADMIN_PASSWORD}" -H "Content-Type: application/json" -X "$method")

    if [[ -n "$data" ]]; then
        curl_args+=(-d "$data")
    fi

    curl "${curl_args[@]}" "${NEXUS_URL}${endpoint}"
}

is_password_valid() {
    call_nexus_api GET "/service/rest/v1/status" >/dev/null 2>&1
}

change_admin_password() {
    log_info "Ensuring admin password is set to default"

    if is_password_valid; then
        log_info "Admin password is already set correctly"
        return
    fi
    
    log_info "Configured password is not valid, trying preseeded password from admin.password file"
    local preseeded_password=$(get_preseeded_admin_password)

    if [[ -z "$preseeded_password" ]]; then
        log_error "No valid current password found, and configured password is incorrect. Cannot continue."
        exit 1
    fi

    log_info "Attempting to change admin password using guessed password"
    if curl -s -f -u "admin:${preseeded_password}" \
        -H "Content-Type: text/plain" \
        -X PUT \
        -d "${NEXUS_ADMIN_PASSWORD}" \
        "${NEXUS_URL}/service/rest/v1/security/users/admin/change-password" >/dev/null; then

        log_info "Password changed successfully"
    else
        log_error "Failed to change admin password with guessed password"
        exit 1
    fi
}

create_conan_repo() {
    local repo="conan-hosted"
    log_info "Ensuring Conan hosted repo '${repo}' exists"

    if call_nexus_api GET "/service/rest/v1/repositories/${repo}" >/dev/null 2>&1; then
        log_info "Repository '${repo}' already exists, skipping creation"
        return
    fi

    local payload=$(jq -n \
        --arg name "$repo" \
        '{
            name: $name,
            online: true,
            storage: {
                blobStoreName: "default",
                strictContentTypeValidation: true,
                writePolicy: "allow"
            },
            "cleanup": {
                "policyNames": [
                "string"
                ]
            },
            "component": {
                "proprietaryComponents": true
            }
        }'
    )

    call_nexus_api POST "/service/rest/v1/repositories/conan/hosted" "$payload"
    log_info "Created Conan hosted repo '${repo}'"
}

enable_conan_realm() {
    local realm="ConanToken"
    log_info "Ensuring '${realm}' realm is active"

    local active=$(call_nexus_api GET "/service/rest/v1/security/realms/active")

    if echo "$active" | jq -e ".[] | select(. == \"$realm\")" >/dev/null; then
        log_info "'${realm}' is already active"
        return
    fi

    local updated=$(echo "$active" | jq ". + [\"$realm\"]")

    call_nexus_api PUT "/service/rest/v1/security/realms/active" "$updated"
    log_info "Activated '${realm}' successfully"
}

enable_anonymous_access() {
    log_info "Enabling anonymous access"
    call_nexus_api PUT "/service/rest/v1/security/anonymous" \
        '{"enabled":true,"userId":"anonymous","realmName":"NexusAuthorizingRealm"}'
}

define_anonymous_role() {
    log_info "Creating or updating role '${ROLE_ID}'"

    local privs_json
    privs_json=$(printf '%s\n' "${ROLE_PRIVILEGES[@]}" | jq -R . | jq -s .)

    local payload
    payload=$(jq -n \
        --arg id "$ROLE_ID" \
        --arg name "$ROLE_NAME" \
        --arg desc "$ROLE_DESC" \
        --argjson privs "$privs_json" \
        '{
            id: $id,
            name: $name,
            description: $desc,
            privileges: $privs,
            roles: []
        }')

    if call_nexus_api GET "/service/rest/v1/security/roles/${ROLE_ID}" >/dev/null 2>&1; then
        call_nexus_api PUT "/service/rest/v1/security/roles/${ROLE_ID}" "$payload"
    else
        call_nexus_api POST "/service/rest/v1/security/roles" "$payload"
    fi
}

assign_role_to_anonymous_user() {
    log_info "Assigning role '${ROLE_ID}' to anonymous user"

    local payload
    payload=$(jq -n \
        --arg userId "anonymous" \
        --argjson roles "[\"$ROLE_ID\"]" \
        '{
            userId: $userId,
            firstName: "Anonymous",
            lastName: "User",
            emailAddress: "anon@example.com",
            source: "default",
            status: "active",
            roles: $roles
        }')

    call_nexus_api PUT "/service/rest/v1/security/users/anonymous" "$payload"
}

is_existing_user() {
    local user_id="$1"
    local status=$(curl -s -o /dev/null -w "%{http_code}" -u "${NEXUS_ADMIN_USER}:${NEXUS_ADMIN_PASSWORD}" \
             -X GET "${NEXUS_URL}/service/rest/v1/security/users?userId=${user_id}" || true)
    [[ "$status" == "200" ]]
}

define_conan_upload_user() {
    log_info "Creating user '${CONAN_UPLOAD_USER}' with upload rights"
    local payload
    payload=$(jq -n \
        --arg userId    "$CONAN_UPLOAD_USER" \
        --arg pass      "$CONAN_UPLOAD_PASSWORD" \
        --argjson roles "[\"$ROLE_ID\"]" \
        '{
            userId:       $userId,
            firstName:    "Conan",
            lastName:     "Uploader",
            emailAddress: ($userId + "@example.com"),
            password:     $pass,
            source:       "default",
            status:       "active",
            roles:        $roles
        }')

    if is_existing_user ${CONAN_UPLOAD_USER}; then
        log_info "User exists; updating '${CONAN_UPLOAD_USER}'"
        call_nexus_api PUT "/service/rest/v1/security/users/${CONAN_UPLOAD_USER}" "$payload"
    else
        log_info "User not found; creating '${CONAN_UPLOAD_USER}'"
        call_nexus_api POST "/service/rest/v1/security/users" "$payload"
    fi
}

# === Main ===

change_admin_password
enable_anonymous_access
create_conan_repo
enable_conan_realm
define_anonymous_role
assign_role_to_anonymous_user
define_conan_upload_user

log_info "Done."
