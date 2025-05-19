#include <gtest/gtest.h>
#include "../src/fibonacci_handler.hpp"

class FibonacciHandlerTest : public ::testing::Test {
protected:
    FibonacciHandler handler;
};

TEST_F(FibonacciHandlerTest, ValidInput) {
    // Arrange
    std::string input_json = R"({"number": 5})";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(input_json);
    
    // Assert
    EXPECT_TRUE(result.valid);
    EXPECT_EQ(result.number, 5);
    EXPECT_TRUE(result.error_message.empty());
}

TEST_F(FibonacciHandlerTest, EmptyRequestBody) {
    // Arrange
    std::string empty_input = "";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(empty_input);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.error_message, "Empty request body");
}

TEST_F(FibonacciHandlerTest, InvalidJson) {
    // Arrange
    std::string invalid_json = "invalid json";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(invalid_json);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_TRUE(result.error_message.find("Invalid JSON") != std::string::npos);
}

TEST_F(FibonacciHandlerTest, MissingNumberField) {
    // Arrange
    std::string json_without_number = R"({"foo": "bar"})";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(json_without_number);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.error_message, "Missing 'number' field");
}

TEST_F(FibonacciHandlerTest, NonIntegerNumber) {
    // Arrange
    std::string json_with_string_number = R"({"number": "five"})";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(json_with_string_number);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.error_message, "Field 'number' must be an integer");
}

TEST_F(FibonacciHandlerTest, NegativeNumber) {
    // Arrange
    std::string json_with_negative = R"({"number": -5})";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(json_with_negative);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.error_message, "Number must be non-negative");
}

TEST_F(FibonacciHandlerTest, TooLargeNumber) {
    // Arrange
    std::string json_with_large_number = R"({"number": 100})";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(json_with_large_number);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.error_message, "Number too large (maximum 90)");
}

TEST_F(FibonacciHandlerTest, FloatingPointNumber) {
    // Arrange
    std::string json_with_float = R"({"number": 5.5})";
    
    // Act
    FibonacciHandler::ValidationResult result = handler.validateInput(json_with_float);
    
    // Assert
    EXPECT_FALSE(result.valid);
    EXPECT_EQ(result.error_message, "Field 'number' must be an integer");
}

TEST_F(FibonacciHandlerTest, ValidComputation) {
    // Arrange
    int fibonacci_input = 10;
    
    // Act
    FibonacciHandler::ComputationResult result = handler.computeFibonacci(fibonacci_input);
    
    // Assert
    EXPECT_TRUE(result.success);
    EXPECT_EQ(result.fibonacci_value, 55);
}

TEST_F(FibonacciHandlerTest, CreateSuccessResponse) {
    // Arrange
    int input_number = 10;
    long fibonacci_value = 55;
    
    // Act
    std::string response = handler.createSuccessResponse(input_number, fibonacci_value);
    
    // Assert
    json parsed = json::parse(response);
    EXPECT_EQ(parsed["number"], 10);
    EXPECT_EQ(parsed["fibonacci"], 55);
}

TEST_F(FibonacciHandlerTest, CreateErrorResponse) {
    // Arrange
    std::string error_message = "Test error";
    
    // Act
    std::string response = handler.createErrorResponse(error_message);
    
    // Assert
    json parsed = json::parse(response);
    EXPECT_EQ(parsed["error"], "Test error");
}

// Integration Tests
TEST_F(FibonacciHandlerTest, EndToEndSuccess) {
    // Arrange
    std::string request_body = R"({"number": 6})";
    
    // Act
    auto [status_code, response] = handler.handleRequest(request_body);
    
    // Assert
    EXPECT_EQ(status_code, 200);
    json parsed = json::parse(response);
    EXPECT_EQ(parsed["number"], 6);
    EXPECT_EQ(parsed["fibonacci"], 8);  // Assuming fibonacci(6) = 8
}

TEST_F(FibonacciHandlerTest, EndToEndValidationError) {
    // Arrange
    std::string request_body = R"({"number": -1})";
    
    // Act
    auto [status_code, response] = handler.handleRequest(request_body);
    
    // Assert
    EXPECT_EQ(status_code, 400);
    json parsed = json::parse(response);
    EXPECT_EQ(parsed["error"], "Number must be non-negative");
}

TEST_F(FibonacciHandlerTest, EndToEndInvalidJson) {
    // Arrange
    std::string invalid_request = "invalid";
    
    // Act
    auto [status_code, response] = handler.handleRequest(invalid_request);
    
    // Assert
    EXPECT_EQ(status_code, 400);
    json parsed = json::parse(response);
    EXPECT_TRUE(parsed["error"].get<std::string>().find("Invalid JSON") != std::string::npos);
}