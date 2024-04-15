//Unit tests for the SPO2 symptom determination function in the SPO2Tracker class

#define BOOST_TEST_MODULE HrSympCheck
#include <boost/test/unit_test.hpp>

#include "sensorTest.cpp"
#include "HRTracker.cpp"
#include "DiagnosisInterface.h"

//Unit tests for the determineSymptom function in the HRTracker class


//Test case to check if the function can detect Bradycardia

BOOST_AUTO_TEST_CASE(SuccessTestRangeLow) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("Bradycardia", hr.determineSymptom(hr.symptomRanges,59));
}

//Test case to check if the function can detect a normal heart rate

BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("Normal resting heart rate", hr.determineSymptom(hr.symptomRanges,90));
}

//Test case to check if the function can detect Tachyacardia

BOOST_AUTO_TEST_CASE(SuccessTestRangeTop) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("Tachyacardia", hr.determineSymptom(hr.symptomRanges,105));

}


BOOST_AUTO_TEST_CASE(FailTestRangemid) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_NE("Tachyacardia", hr.determineSymptom(hr.symptomRanges,80));

}

//Test case to check if the function can detect a critical low heart rate

BOOST_AUTO_TEST_CASE(SuccessTestCriticalLow) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("critLow", hr.determineSymptom(hr.symptomRanges,10));

}

//Test case to check if the function can detect a critical high heart rate

BOOST_AUTO_TEST_CASE(SuccessTestCriticalHigh) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("critHigh", hr.determineSymptom(hr.symptomRanges,1000));

}

//Test case to check if the function can respond to a negative input

BOOST_AUTO_TEST_CASE(SuccessTestNegative) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("critLow", hr.determineSymptom(hr.symptomRanges,-1));

}

//Test case to check if the function works as expected at the boundaries between ranges

BOOST_AUTO_TEST_CASE(SuccessBoundaryLow) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("Bradycardia", hr.determineSymptom(hr.symptomRanges,40));

}

//Test case to check if the function works as expected at the boundaries between ranges

BOOST_AUTO_TEST_CASE(SuccessBoundaryMid) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("Normal resting heart rate", hr.determineSymptom(hr.symptomRanges,60));

}

//Test case to check if the function works as expected at the boundaries between ranges

BOOST_AUTO_TEST_CASE(SuccessBoundaryTop) {
    sensorTest s;
    HRTracker hr(&s);
    BOOST_CHECK_EQUAL("Tachyacardia", hr.determineSymptom(hr.symptomRanges,100));

}
