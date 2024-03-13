cmake_minimum_required(VERSION 3.1.3)
project(testExample VERSION 1.0 LANGUAGES CXX)


add_executable(testExample test.cpp)
target_link_directories(testExample PRIVATE ${CMAKE_SOURCE_DIR}/../src/build)
target_link_libraries(testExample libmax30102)