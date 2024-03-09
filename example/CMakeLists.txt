cmake_minimum_required(VERSION 3.1.0)
project(testExample VERSION 1.0 LANGUAGES CXX)

include_directories("../src")
add_subdirectory("../src")
add_executable($(PROJECT_NAME) test.cpp)
target_link_libraries($(PROJECT_NAME) max30102)