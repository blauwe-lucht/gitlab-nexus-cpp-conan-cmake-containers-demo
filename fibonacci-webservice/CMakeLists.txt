cmake_minimum_required(VERSION 3.15)
project(fibonacci-webservice CXX)

find_package(nlohmann_json REQUIRED)
find_package(httplib REQUIRED)
find_package(fibonacci CONFIG REQUIRED)

add_executable(fibonacci-webservice src/main.cpp)

target_link_libraries(fibonacci-webservice PRIVATE
        httplib::httplib
        nlohmann_json::nlohmann_json
        fibonacci::fibonacci
)

install(TARGETS fibonacci-webservice DESTINATION "."
        RUNTIME DESTINATION bin
        ARCHIVE DESTINATION lib
        LIBRARY DESTINATION lib
)
