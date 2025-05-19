#include "fibonacci_handler.hpp"
#include <limits>

FibonacciHandler::ValidationResult 
FibonacciHandler::validateInput(const std::string& request_body) const {
    try {
        if (request_body.empty()) {
            return {false, "Empty request body", 0};
        }

        auto j = json::parse(request_body);
        
        if (!j.contains("number")) {
            return {false, "Missing 'number' field", 0};
        }

        if (!j["number"].is_number_integer()) {
            return {false, "Field 'number' must be an integer", 0};
        }

        int number = j["number"].get<int>();
        
        if (number < 0) {
            return {false, "Number must be non-negative", 0};
        }

        // Check for overflow risk (fibonacci grows very quickly)
        if (number > 90) {  // Fibonacci(90) is close to long max
            return {false, "Number too large (maximum 90)", 0};
        }

        return {true, "", number};
    }
    catch (const json::parse_error& e) {
        return {false, "Invalid JSON: " + std::string(e.what()), 0};
    }
    catch (const json::type_error& e) {
        return {false, "JSON type error: " + std::string(e.what()), 0};
    }
    catch (const std::exception& e) {
        return {false, "Unexpected error: " + std::string(e.what()), 0};
    }
}

FibonacciHandler::ComputationResult 
FibonacciHandler::computeFibonacci(int n) const {
    try {
        long result = fibonacci_.compute(n);
        return {true, "", result};
    }
    catch (const std::domain_error& e) {
        return {false, "Domain error: " + std::string(e.what()), 0};
    }
    catch (const std::overflow_error& e) {
        return {false, "Overflow error: " + std::string(e.what()), 0};
    }
    catch (const std::exception& e) {
        return {false, "Computation error: " + std::string(e.what()), 0};
    }
}

std::string FibonacciHandler::createSuccessResponse(int number, long fibonacci_value) const {
    json response = {
        {"number", number},
        {"fibonacci", fibonacci_value}
    };
    return response.dump();
}

std::string FibonacciHandler::createErrorResponse(const std::string& error_message) const {
    json response = {
        {"error", error_message}
    };
    return response.dump();
}

std::pair<int, std::string> FibonacciHandler::handleRequest(const std::string& request_body) const {
    // Validate input
    auto validation = validateInput(request_body);
    if (!validation.valid) {
        return {400, createErrorResponse(validation.error_message)};
    }

    // Compute fibonacci
    auto computation = computeFibonacci(validation.number);
    if (!computation.success) {
        return {500, createErrorResponse(computation.error_message)};
    }

    // Create success response
    std::string response = createSuccessResponse(validation.number, computation.fibonacci_value);
    return {200, response};
}