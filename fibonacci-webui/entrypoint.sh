#!/bin/sh

set -euo pipefail

API_URL="${FIBONACCI_API_URL:-http://fibonacci-webservice:27372}"
VERSION="${FIBONACCI_WEBUI_VERSION:-unknown}"

sed "s|__API_URL__|$API_URL|g; s|__VERSION__|$VERSION|g" /usr/share/nginx/html/index.html > /usr/share/nginx/html/index.tmp
mv /usr/share/nginx/html/index.tmp /usr/share/nginx/html/index.html

exec nginx -g 'daemon off;'
