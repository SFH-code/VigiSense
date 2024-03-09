cmake_minimum_required(VERSION 3.1.0)
project(VigiSenseLibs VERSION 1.0 LANGUAGES CXX)

add_library(max30102 MAX30102.cpp)

target_link_libraries(max30102 pigpio)


