#include "fibonacci_handler.hpp"
#include <iostream>
#include <httplib.h>

int main() {
    httplib::Server svr;
    FibonacciHandler handler;

    svr.Post("/fibonacci", [&handler](const httplib::Request& req, httplib::Response& res) {
        auto [status_code, response_body] = handler.handleRequest(req.body);
        res.status = status_code;
        res.set_content(response_body, "application/json");
    });

    const int port = 27372;
    std::cout << "Listening on port " << port << "...\n";
    svr.listen("0.0.0.0", port);
    return 0;
}