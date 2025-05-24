#include "./controller/fibonacci_controller.hpp"
#include "./app_component.hpp"

#include "oatpp/web/server/HttpConnectionHandler.hpp"
#include "oatpp/web/server/HttpRouter.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/network/Server.hpp"

#include "oatpp-swagger/Controller.hpp"

#include <iostream>

#ifndef __APP_VERSION__
#define __APP_VERSION__ "unknown"
#endif

void run() {
    AppComponent components;
    
    OATPP_COMPONENT(std::shared_ptr<oatpp::web::server::HttpRouter>, router);
    
    oatpp::web::server::api::Endpoints docEndpoints;

    docEndpoints.append(router->addController(FibonacciController::createShared())->getEndpoints());

    router->addController(oatpp::swagger::Controller::createShared(docEndpoints));

    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ConnectionHandler>, connectionHandler);
    OATPP_COMPONENT(std::shared_ptr<oatpp::network::ServerConnectionProvider>, connectionProvider);

    oatpp::network::Server server(connectionProvider, connectionHandler);
    
    OATPP_LOGI("FibonacciService", "Server running on port %s", connectionProvider->getProperty("port").getData());
    
    server.run();
}

int main() {
    oatpp::base::Environment::init();
    
    std::cout << "Fibonacci Web Service v" << __APP_VERSION__ << "\n";
    std::cout << "Starting server...\n";
    
    run();
    
    /* Print how much objects were created during app running, and what have left-probably leaked */
    /* Disable object counting for release builds using '-D OATPP_DISABLE_ENV_OBJECT_COUNTERS' flag for better performance */
    std::cout << "\nEnvironment:\n";
    std::cout << "objectsCount = " << oatpp::base::Environment::getObjectsCount() << "\n";
    std::cout << "objectsCreated = " << oatpp::base::Environment::getObjectsCreated() << "\n\n";
    
    oatpp::base::Environment::destroy();
    
    return 0;
}