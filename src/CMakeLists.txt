cmake_minimum_required(VERSION 3.7.0)
find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${DEMO_SOURCE_DIR}/src
 ${Boost_INCLUDE_DIRS}
 )
add_definitions (-DBOOST_TEST_DYN_LINK)



find_package(fastcdr REQUIRED)
find_package(fastrtps REQUIRED)


# alert section
add_custom_target(
    messages
    COMMAND fastddsgen ../tests/alert.idl
)
add_library(alert STATIC alert.cxx alertPubSubTypes.cxx)
add_dependencies(alert messages)


add_library(max30102 MAX30102.cpp)
target_link_libraries(max30102 pigpio)

add_library(sensor Sensor.cpp)
target_link_libraries(sensor max30102)

add_library(spo2 SPO2Tracker.cpp)
target_link_libraries(spo2 sensor fastcdr fastrtps alert) 

add_library(hr HRTracker.cpp)
target_link_libraries(hr sensor fastcdr fastrtps alert)

add_library(sensortest sensorTest.cpp ../src/sensorTest.h)
target_link_libraries(sensortest spo2 hr sensor)


add_executable (unitTestHrSymptom unitTestHrSymptom.cpp) 
target_link_libraries (unitTestHrSymptom
sensortest
hr
spo2
sensor
fastcdr 
fastrtps 
alert
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME TestHrSymptom COMMAND Test)

add_executable (unitTestSpO2Symptom unitTestSpO2Symptom.cpp) 
target_link_libraries (unitTestSpO2Symptom
sensortest
hr
spo2
sensor
fastcdr 
fastrtps 
alert
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME TestSpO2Symptom COMMAND Test)




