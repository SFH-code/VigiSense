cmake_minimum_required(VERSION 3.7.0)
project(VigiSenseLibs VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_library(max30102 MAX30102.cpp)
target_link_libraries(max30102 pigpio)

add_library(sensor Sensor.cpp)
target_link_libraries(sensor max30102)

add_executable(test
  test.cpp
)
target_link_libraries(test max30102)


add_executable(testSpO2 
  testSpO2.cpp
)
target_link_libraries(testSpO2 sensor)

