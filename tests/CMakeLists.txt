find_package (Boost COMPONENTS system filesystem unit_test_framework REQUIRED)
include_directories (${DEMO_SOURCE_DIR}/src
 ${Boost_INCLUDE_DIRS}
 )
add_definitions (-DBOOST_TEST_DYN_LINK)
add_executable (UnitTestHRSymptom unitTestHrSymptom.cpp) 
target_link_libraries (UnitTestHRSymptom
sensortest
hr
spo2
sensor
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME TestHrSymptom COMMAND Test)

add_executable ( UnitTestSpO2Symptom unitTestSpO2Symptom.cpp ) 
target_link_libraries (UnitTestSpO2Symptom
sensortest
hr
spo2
sensor
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME TestSpO2Symptom COMMAND Test)

add_executable (UnitTestSpO2Calc unitTest_SPO2Calc.cpp ) 
target_link_libraries (UnitTestSpO2Calc
sensortest
hr
spo2
sensor
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME TestSpO2Calc COMMAND Test)

add_executable (UnitTestPeakDetect unitTest_PeakDetect.cpp) 
target_link_libraries (UnitTestPeakDetect
sensortest
hr
spo2
sensor
 ${Boost_FILESYSTEM_LIBRARY}
${Boost_SYSTEM_LIBRARY}
${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
 )
add_test (NAME TestPeakDetect COMMAND Test)

