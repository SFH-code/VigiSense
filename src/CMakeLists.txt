cmake_minimum_required(VERSION 3.7.0)
project(UNITTESTING)

set(CMAKE_CXX_STANDARD 17)


find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


# alert section
add_custom_target(
    messages
    COMMAND fastddsgen ../alert.idl
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
target_link_libraries(spo2 sensor fastcdr fastrtps alert)

add_library(hr HRTracker.cpp)
target_link_libraries(hr sensor fastcdr fastrtps alert)

add_library(sensortest sensorTest.cpp sensorTest.h)
target_link_libraries(sensortest spo2 hr sensor)

add_executable(test
  test.cpp
)
target_link_libraries(test max30102 sensor spo2 fastcdr fastrtps alert)


add_executable(testSpO2 
  testSpO2.cpp
)
target_link_libraries(testSpO2 max30102 sensor spo2 hr fastcdr fastrtps alert)

