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

