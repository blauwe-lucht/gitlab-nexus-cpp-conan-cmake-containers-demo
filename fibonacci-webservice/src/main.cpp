#include "fibonacci_handler.hpp"
#include <iostream>
#include <httplib.h>

#ifndef __APP_VERSION__
    #define __APP_VERSION__ "unknown"
#endif

int main() {
    httplib::Server svr;
    FibonacciHandler handler;

    // POST endpoint for Fibonacci calculation
    svr.Post("/fibonacci", [&handler](const httplib::Request& req, httplib::Response& res) {
        auto [status_code, response_body] = handler.handleRequest(req.body);
        res.status = status_code;
        res.set_content(response_body, "application/json");
    });

    // GET endpoint to retrieve the version
    svr.Get("/version", [](const httplib::Request&, httplib::Response& res) {
        res.status = 200;
        res.set_content("{\"version\": \"" + std::string(__APP_VERSION__) + "\"}", "application/json");
    });

    const int port = 27372;
    std::cout << "Fibonacci Web Service v" << __APP_VERSION__ << "\n";
    std::cout << "Listening on port " << port << "...\n";
    svr.listen("0.0.0.0", port);
    std::cout << "Server stopped.\n";
    return 0;
}