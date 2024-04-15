//Unit tests for the SPO2 symptom determination function in the SPO2Tracker class

#define BOOST_TEST_MODULE HrSympCheck
#include <boost/test/unit_test.hpp>

#include "sensorTest.h"
#include "HRTracker.h"
#include "DiagnosisInterface.h"


BOOST_AUTO_TEST_CASE(SuccessTestRangeLow) {
    sensorTest s;
    HRTracker hr(&s);
    hr.start();
    s.setHr(59);
    BOOST_CHECK_EQUAL("Bradycardia", diagnosisInterface::determineSymptom(hr.symptomRanges,hr.getHr()));
}

BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    HRTracker hr(&s);
    hr.start();
    s.setHr(90);
    BOOST_CHECK_EQUAL("Normal resting heart rate", diagnosisInterface::determineSymptom(spo2.symptomRanges,hr.getHr()));
}

BOOST_AUTO_TEST_CASE(SuccessTestRangeTop) {
    sensorTest s;
    HRTracker hr(&s);
    hr.start();
    s.setHr(105);
    BOOST_CHECK_EQUAL("Tachyacardia", diagnosisInterface::determineSymptom(hr.symptomRanges,hr.getHr()));

}

BOOST_AUTO_TEST_CASE(FailTestRange) {
    sensorTest s;
    HRTracker hr(&s);
    hr.start();
    s.setHr(80);
    BOOST_CHECK_EQUAL("Tachyacardia", diagnosisInterface::determineSymptom(hr.symptomRanges,hr.getHr()));

}

BOOST_AUTO_TEST_CASE(SuccessTestCritical) {
    sensorTest s;
    HRTracker hr(&s);
    hr.start();
    s.setHr(80);
    BOOST_CHECK_EQUAL(false, diagnosisInterface::isCritical(hr.getHr()));

}

BOOST_AUTO_TEST_CASE(SuccessTestCritical) {
    sensorTest s;
    HRTracker hr(&s);
    hr.start();
    s.setHr(102);
    BOOST_CHECK_EQUAL(false, diagnosisInterface::isCritical(hr.getHr()));

}