FROM almalinux:9

# Install runtime dependencies
RUN dnf update -y && \
    dnf install -y \
        glibc \
        libgcc \
        libstdc++ \
    && dnf clean all \
    && rm -rf /var/cache/dnf

# Create a non-root user for running the application
RUN groupadd -r fibonacci && useradd -r -g fibonacci fibonacci

# Create application directory
WORKDIR /app

# Copy the binary from build directory
COPY build/Release/fibonacci-webservice /app/fibonacci-webservice

# Copy oatpp-swagger resources
COPY oatpp-swagger /app/oatpp-swagger

# Make the binary executable
RUN chmod +x /app/fibonacci-webservice

# Change ownership to fibonacci user
RUN chown -R fibonacci:fibonacci /app

# Switch to non-root user
USER fibonacci

# Expose the port the service runs on
EXPOSE 27372

# Point to the Swagger resources
ENV OATPP_SWAGGER_RES_PATH=/app/oatpp-swagger/res

# Set the entrypoint to run the service
ENTRYPOINT ["/app/fibonacci-webservice"]
