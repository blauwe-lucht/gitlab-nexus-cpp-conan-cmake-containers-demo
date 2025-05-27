FROM docker.io/nginxinc/nginx-unprivileged:1.27.5-alpine3.21

# This should be passed when building the image:
ARG FIBONACCI_WEBUI_VERSION=unknown

# Copy files as root, then fix permissions
COPY index.html /usr/share/nginx/html/index.html
COPY entrypoint.sh /entrypoint.sh

USER root
RUN chmod +x /entrypoint.sh \
    && sed "s|__VERSION__|${FIBONACCI_WEBUI_VERSION}|g" /usr/share/nginx/html/index.html > /usr/share/nginx/html/index.tmp \
    && mv /usr/share/nginx/html/index.tmp /usr/share/nginx/html/index.html \
    && chown -R nginx:nginx /usr/share/nginx/html /entrypoint.sh
USER nginx

EXPOSE 8080

ENTRYPOINT ["/entrypoint.sh"]
