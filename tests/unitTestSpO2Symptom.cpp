//Unit tests for the SPO2 symptom determination function in the SPO2Tracker class

#define BOOST_TEST_MODULE SpO2SympCheck
#include <boost/test/unit_test.hpp>

#include "sensorTest.h"
#include "SPO2Tracker.h"
#include "DiagnosisInterface.h"





BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(90);
    BOOST_CHECK_EQUAL("Hypoxemia", diagnosisInterface::determineSymptom(spo2.symptomRanges,spo2.getSpO2()));

}

BOOST_AUTO_TEST_CASE(SuccessTestRangeTop) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(94);
    BOOST_CHECK_EQUAL("Concerning Oxygen Concentration", diagnosisInterface::determineSymptom(spo2.symptomRanges,spo2.getSpO2()));

}

BOOST_AUTO_TEST_CASE(FailTestRange) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(80);
    BOOST_CHECK_EQUAL("Normal", diagnosisInterface::determineSymptom(spo2.symptomRanges,spo2.getSpO2()));

}

BOOST_AUTO_TEST_CASE(SuccessTestCritical) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(80);
    BOOST_CHECK_EQUAL(true, diagnosisInterface::isCritical(spo2.getSpO2()));

}

BOOST_AUTO_TEST_CASE(FailTestCritical) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(102);
    BOOST_CHECK_EQUAL(false, diagnosisInterface::isCritical(spo2.getSpO2()));

}