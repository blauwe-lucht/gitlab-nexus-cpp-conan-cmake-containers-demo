FROM docker.io/library/nginx:alpine

# This should be passed when building the image:
ARG FIBONACCI_WEBUI_VERSION=unknown

# Copy files as root, then fix permissions
COPY index.html /usr/share/nginx/html/index.html
COPY entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh \
    && sed "s|__VERSION__|${FIBONACCI_WEBUI_VERSION}|g" /usr/share/nginx/html/index.html > /usr/share/nginx/html/index.tmp \
    && mv /usr/share/nginx/html/index.tmp /usr/share/nginx/html/index.html \
    && mkdir -p /var/cache/nginx/client_temp \
    && chown -R nginx:nginx /usr/share/nginx/html /entrypoint.sh /var/cache/nginx

USER nginx

ENTRYPOINT ["/entrypoint.sh"]