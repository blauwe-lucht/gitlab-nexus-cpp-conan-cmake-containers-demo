cmake_minimum_required(VERSION 3.15)
project(fibonacci-webservice CXX)

set(SHARED_SOURCES
    src/fibonacci_handler.cpp
)

set(UNIT_TEST_SOURCES
    test/fibonacci_handler_tests.cpp
)

set(LIBRARIES
    nlohmann_json::nlohmann_json
    oatpp::oatpp
    oatpp::oatpp-swagger
    fibonacci::fibonacci
)

find_package(nlohmann_json REQUIRED)
find_package(fibonacci CONFIG REQUIRED)
find_package(oatpp REQUIRED)
find_package(oatpp-swagger REQUIRED)

# Pass the version from Conan
if(DEFINED __APP_VERSION__)
    target_compile_definitions(fibonacci-webservice PRIVATE __APP_VERSION__="${__APP_VERSION__}")
endif()

add_executable(fibonacci-webservice src/main.cpp ${SHARED_SOURCES})

target_link_libraries(fibonacci-webservice PRIVATE ${LIBRARIES})

install(TARGETS fibonacci-webservice DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)

# Unit tests
enable_testing()
find_package(GTest REQUIRED)
add_executable(unit_tests ${UNIT_TEST_SOURCES} ${SHARED_SOURCES})
target_link_libraries(unit_tests PRIVATE GTest::gtest_main ${LIBRARIES})
add_test(NAME unit_tests COMMAND unit_tests)
