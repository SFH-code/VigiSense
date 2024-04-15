//Unit tests for the SPO2 calculation
#define BOOST_TEST_MODULE SpO2Calc
#include <boost/test/unit_test.hpp>

#include "sensorTest.cpp"




BOOST_AUTO_TEST_CASE(SuccessTestSPO2Calc) {
    sensorTest s;
    //SPO2Tracker spo2(&s); testing the modified function in sensorTest
    BOOST_CHECK_EQUAL(4, s.SpO2Calc(120,100,100,95)); //correct answer is 3.8 which is rounded to 4

}
/*
BOOST_AUTO_TEST_CASE(FailedTestSPO2CalcDivBy0) {
    sensorTest s;
    //SPO2Tracker spo2(&s); testing the modified function in sensorTest
    BOOST_CHECK_EQUAL(EXIT_FAILURE, s.SpO2Calc(120,0,100,95)); 

}
*/
