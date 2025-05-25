#pragma once

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 * Request DTO for Fibonacci calculation
 */
class FibonacciRequestDto : public oatpp::DTO {
    
    DTO_INIT(FibonacciRequestDto, DTO)
    
    DTO_FIELD_INFO(number) {
        info->description = "The position in the Fibonacci sequence to calculate";
        info->required = true;
    }
    DTO_FIELD(Int32, number);
    
};

/**
 * Response DTO for Fibonacci calculation
 */
class FibonacciResponseDto : public oatpp::DTO {
    
    DTO_INIT(FibonacciResponseDto, DTO)
    
    DTO_FIELD_INFO(number) {
        info->description = "The position in the Fibonacci sequence";
    }
    DTO_FIELD(Int32, number);
    
    DTO_FIELD_INFO(fibonacci) {
        info->description = "The Fibonacci number at position n";
    }
    DTO_FIELD(Int64, fibonacci);
    
};

/**
 * Version response DTO
 */
class VersionResponseDto : public oatpp::DTO {
    
    DTO_INIT(VersionResponseDto, DTO)
    
    DTO_FIELD_INFO(version) {
        info->description = "Application version";
    }
    DTO_FIELD(String, version);
    
};

/**
 * Health check response DTO
 */
class HealthResponseDto : public oatpp::DTO {
    
    DTO_INIT(HealthResponseDto, DTO)
    
    DTO_FIELD_INFO(status) {
        info->description = "Health status of the service";
    }
    DTO_FIELD(String, status);
    
};

/**
 * Error response DTO
 */
class ErrorResponseDto : public oatpp::DTO {
    
    DTO_INIT(ErrorResponseDto, DTO)
    
    DTO_FIELD_INFO(code) {
        info->description = "Error code";
    }
    DTO_FIELD(Int32, code);
    
    DTO_FIELD_INFO(message) {
        info->description = "Error message";
    }
    DTO_FIELD(String, message);
    
};

#include OATPP_CODEGEN_END(DTO)
