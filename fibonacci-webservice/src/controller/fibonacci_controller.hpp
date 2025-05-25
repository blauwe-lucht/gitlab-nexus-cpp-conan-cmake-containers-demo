#pragma once

#include "../dto/dtos.hpp"
#include "../fibonacci_handler.hpp"

#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController)

#ifndef __APP_VERSION__
#define __APP_VERSION__ "unknown"
#endif

/**
 * Fibonacci REST controller.
 */
class FibonacciController : public oatpp::web::server::api::ApiController {
public:
    FibonacciController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
    : oatpp::web::server::api::ApiController(objectMapper) {}

private:
    FibonacciHandler handler;

public:
    
    static std::shared_ptr<FibonacciController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper) // Inject objectMapper component here as default parameter
    ){
        return std::make_shared<FibonacciController>(objectMapper);
    }
    
    ENDPOINT_INFO(calculateFibonacci) {
        info->summary = "Calculate Fibonacci number";
        info->description = "Calculate the nth Fibonacci number";
        info->addConsumes<Object<FibonacciRequestDto>>("application/json");
        info->addResponse<Object<FibonacciResponseDto>>(Status::CODE_200, "application/json", "Fibonacci calculation result");
        info->addResponse<Object<ErrorResponseDto>>(Status::CODE_400, "application/json", "Invalid input");
        info->addResponse<Object<ErrorResponseDto>>(Status::CODE_500, "application/json", "Internal server error");
        info->addTag("Fibonacci");
    }
    ADD_CORS(calculateFibonacci)
    ENDPOINT("POST", "/fibonacci", calculateFibonacci,
             BODY_DTO(Object<FibonacciRequestDto>, dto)) {
        
        // Convert DTO to JSON string for the handler
        auto jsonObjectMapper = std::static_pointer_cast<oatpp::parser::json::mapping::ObjectMapper>(getDefaultObjectMapper());
        auto requestJson = jsonObjectMapper->writeToString(dto);
        
        // Use the existing handler
        auto [statusCode, responseBody] = handler.handleRequest(requestJson->c_str());
        
        // Parse response
        if (statusCode == 200) {
            // Parse the JSON response to extract values
            auto responseDto = jsonObjectMapper->readFromString<oatpp::Object<FibonacciResponseDto>>(responseBody.c_str());
            return createDtoResponse(Status::CODE_200, responseDto);
        } else {
            // Create error response
            auto errorDto = ErrorResponseDto::createShared();
            errorDto->code = statusCode;
            
            // Try to parse error message from JSON, fallback to raw response
            try {
                auto errorResponse = jsonObjectMapper->readFromString<oatpp::Object<ErrorResponseDto>>(responseBody.c_str());
                if (errorResponse && errorResponse->message) {
                    errorDto->message = errorResponse->message;
                } else {
                    errorDto->message = responseBody.c_str();
                }
            } catch (...) {
                errorDto->message = responseBody.c_str();
            }
            
            return createDtoResponse(Status::CODE_400, errorDto);
        }
    }
    
    ENDPOINT_INFO(getVersion) {
        info->summary = "Get application version";
        info->description = "Returns the current version of the Fibonacci service";
        info->addResponse<Object<VersionResponseDto>>(Status::CODE_200, "application/json", "Version information");
        info->addTag("System");
    }
    ENDPOINT("GET", "/version", getVersion) {
        auto dto = VersionResponseDto::createShared();
        dto->version = __APP_VERSION__;
        return createDtoResponse(Status::CODE_200, dto);
    }
    
    ENDPOINT_INFO(healthCheck) {
        info->summary = "Health check";
        info->description = "Returns the health status of the service";
        info->addResponse<Object<HealthResponseDto>>(Status::CODE_200, "application/json", "Health status");
        info->addTag("System");
    }
    ENDPOINT("GET", "/health", healthCheck) {
        auto dto = HealthResponseDto::createShared();
        dto->status = "ok";
        return createDtoResponse(Status::CODE_200, dto);
    }
    
};

#include OATPP_CODEGEN_END(ApiController)
