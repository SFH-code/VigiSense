cmake_minimum_required(VERSION 3.7.0)
project(VigiSenseLibs VERSION 1.0 LANGUAGES CXX)

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
add_executable(subscriber subscriber.cpp)
target_link_libraries(subscriber fastcdr fastrtps alert)


add_library(spo2 SPO2Tracker.cpp)
target_link_libraries(spo2 fastcdr fastrtps alert)


add_executable(test
  test.cpp
)
target_link_libraries(test spo2 fastcdr fastrtps alert)


