FROM docker.io/library/nginx:alpine

ARG FIBONACCI_WEBUI_VERSION=unknown

COPY index.html /usr/share/nginx/html/index.html
COPY entrypoint.sh /entrypoint.sh

RUN chmod +x /entrypoint.sh \
    && sed "s|__VERSION__|${FIBONACCI_WEBUI_VERSION}|g" /usr/share/nginx/html/index.html > /usr/share/nginx/html/index.tmp \
    && mv /usr/share/nginx/html/index.tmp /usr/share/nginx/html/index.html

ENTRYPOINT ["/entrypoint.sh"]