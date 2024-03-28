cmake_minimum_required(VERSION 3.7.0)
project(VigiSenseLibs VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)


find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)

# alert section
add_custom_target(
    messages
    COMMAND fastddsgen alert.idl
)
add_library(alert STATIC alert.cxx alertPubSubTypes.cxx)
add_dependencies(alert messages)

# example on how to call
# add_executable(publisher publisher.cpp)
# target_link_libraries(publisher fastcdr fastrtps alert)

add_library(max30102 MAX30102.cpp)
target_link_libraries(max30102 pigpio)

add_library(sensor Sensor.cpp)
target_link_libraries(sensor max30102)

add_library(spo2 SPO2Tracker.cpp)


add_executable(test
  test.cpp
)
target_link_libraries(test max30102)


add_executable(testSpO2 
  testSpO2.cpp
)
target_link_libraries(testSpO2 sensor)

