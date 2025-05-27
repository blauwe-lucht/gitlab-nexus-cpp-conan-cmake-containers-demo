#pragma once

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/network/tcp/server/ConnectionProvider.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/component.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"

/**
 * Class which creates and holds Application components and registers components in oatpp::base::Environment
 * Order of components initialization is from top to bottom
 */
class AppComponent {
public:
    
    /**
     * Create ConnectionProvider component which listens on the port
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, serverConnectionProvider)([] {
        return oatpp::network::tcp::server::ConnectionProvider::createShared({"0.0.0.0", 27372, oatpp::network::Address::IP_4});
    }());
    
    /**
     * Create Router component
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, httpRouter)([] {
        return oatpp::web::server::HttpRouter::createShared();
    }());
    
    /**
     * Create ConnectionHandler component which uses Router component to route requests
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, serverConnectionHandler)([] {
        OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router); // get Router component
        return oatpp::web::server::HttpConnectionHandler::createShared(router);
    }());
    
    /**
     * Create ObjectMapper component to serialize/deserialize DTOs in Controller's API
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::data::mapping::ObjectMapper>, apiObjectMapper)([] {
        return oatpp::parser::json::mapping::ObjectMapper::createShared();
    }());
    
    /**
     * General API docs info
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)([] {
        
        oatpp::swagger::DocumentInfo::Builder builder;
        
        const char* apiUrl = std::getenv("API_URL");
        if (!apiUrl) {
            apiUrl = "http://localhost:27372";
        }

        builder
        .setTitle("Fibonacci Web Service")
        .setDescription("REST API for Fibonacci number calculation")
        .setVersion("1.0")
        .setContactName("Fibonacci Service")
        .setLicenseName("Apache License, Version 2.0")
        .setLicenseUrl("http://www.apache.org/licenses/LICENSE-2.0")
        .addServer(apiUrl, "webservice");
        
        return builder.build();
    }());
    
    /**
     * Swagger-Ui Resources (optional)
     */
    OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)([] {
        const char* resPath = std::getenv("OATPP_SWAGGER_RES_PATH");
        if (resPath) {
            if (!std::filesystem::exists(resPath)) {
                throw std::runtime_error(std::string("Swagger resources directory does not exist: ") + resPath);
            }
            return oatpp::swagger::Resources::loadResources(resPath);
        } else {
            throw std::runtime_error("OATPP_SWAGGER_RES_PATH environment variable is not set");
        }
    }());
};
