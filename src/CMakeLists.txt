cmake_minimum_required(VERSION 3.7.0)
project(VigiSenseLibs VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(max30102 MAX30102.cpp)
target_link_libraries(max30102 pigpio)

add_executable(test
  test.cpp
)
target_link_libraries(test max30102)



