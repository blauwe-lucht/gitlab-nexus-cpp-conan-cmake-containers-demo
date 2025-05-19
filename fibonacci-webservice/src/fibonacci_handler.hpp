#pragma once

#include <nlohmann/json.hpp>
#include <fibonacci.hpp>
#include <stdexcept>
#include <string>

using json = nlohmann::json;

class FibonacciHandler {
public:
    struct ValidationResult {
        bool valid;
        std::string error_message;
        int number;
    };

    struct ComputationResult {
        bool success;
        std::string error_message;
        long fibonacci_value;
    };

    // Validate and parse input JSON
    ValidationResult validateInput(const std::string& request_body) const;
    
    // Compute fibonacci number
    ComputationResult computeFibonacci(int n) const;
    
    // Create JSON response
    std::string createSuccessResponse(int number, long fibonacci_value) const;
    std::string createErrorResponse(const std::string& error_message) const;
    
    // Main handler that orchestrates everything
    std::pair<int, std::string> handleRequest(const std::string& request_body) const;

private:
    Fibonacci fibonacci_;
};
