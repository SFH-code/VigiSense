//Unit tests for the SPO2 symptom determination function in the SPO2Tracker class

#define BOOST_TEST_MODULE HrSympCheck
#include <boost/test/unit_test.hpp>

#include "sensorTest.cpp"
#include "HRTracker.cpp"
#include "DiagnosisInterface.h"


BOOST_AUTO_TEST_CASE(SuccessTestRangeLow) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(59);
    BOOST_CHECK_EQUAL("Bradycardia", hr.determineSymptom(hr.symptomRanges,59));
}

BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(90);
    BOOST_CHECK_EQUAL("Normal resting heart rate", hr.determineSymptom(hr.symptomRanges,90));
}

BOOST_AUTO_TEST_CASE(SuccessTestRangeTop) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(105);
    BOOST_CHECK_EQUAL("Tachyacardia", hr.determineSymptom(hr.symptomRanges,105));

}

BOOST_AUTO_TEST_CASE(FailTestRangemid) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(80);
    BOOST_CHECK_NE("Tachyacardia", hr.determineSymptom(hr.symptomRanges,80));

}

BOOST_AUTO_TEST_CASE(SuccessTestCriticalLow) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(80);
    BOOST_CHECK_EQUAL("critLow", hr.determineSymptom(hr.symptomRanges,10));

}

BOOST_AUTO_TEST_CASE(SuccessTestCriticalHigh) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(102);
    BOOST_CHECK_EQUAL("critHigh", hr.determineSymptom(hr.symptomRanges,1000));

}

BOOST_AUTO_TEST_CASE(SuccessTestNegative) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(102);
    BOOST_CHECK_EQUAL("critLow", hr.determineSymptom(hr.symptomRanges,-1));

}

BOOST_AUTO_TEST_CASE(SuccessBoundaryLow) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(102);
    BOOST_CHECK_EQUAL("Bradycardia", hr.determineSymptom(hr.symptomRanges,40));

}

BOOST_AUTO_TEST_CASE(SuccessBoundaryMid) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(102);
    BOOST_CHECK_EQUAL("Normal resting heart rate", hr.determineSymptom(hr.symptomRanges,60));

}

BOOST_AUTO_TEST_CASE(SuccessBoundaryTop) {
    sensorTest s;
    HRTracker hr(&s);
    //hr.start();
    //s.setHr(102);
    BOOST_CHECK_EQUAL("Tachyacardia", hr.determineSymptom(hr.symptomRanges,100));

}
