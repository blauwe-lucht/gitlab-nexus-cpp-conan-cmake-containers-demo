#include <httplib.h>
#include <nlohmann/json.hpp>
#include <fibonacci.hpp>

using json = nlohmann::json;

int main() {
    httplib::Server svr;

    svr.Post("/fibonacci", [](const httplib::Request& req, httplib::Response& res) {
        try {
            auto j = json::parse(req.body);
            int n = j.at("number").get<int>();
            if (n < 0)
            {
                throw std::domain_error("negative");
            }

            Fibonacci fibonacci;
            long result = fibonacci.compute(n);
            json reply = {
                {"number", n},
                {"fibonacci", result}
            };
            res.set_content(reply.dump(), "application/json");
        }
        catch (std::exception& e)
        {
            json err = {{"error", e.what()}};
            res.status = 400;
            res.set_content(err.dump(), "application/json");
        }
    });

    const int port = 27372;
    std::cout << "Listening on port " << port << "...\n";
    svr.listen("0.0.0.0", port);
    return 0;
}
