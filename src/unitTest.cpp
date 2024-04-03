#define BOOST_TEST_MODULE SqrTests
#include <boost/test/unit_test.hpp>

#include "sensorTest.h"
#include "SPO2Tracker.h"



BOOST_AUTO_TEST_CASE(SuccessTestRangeLow) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(60);
    BOOST_CHECK_EQUAL("Hypoxia", spo2.determineSymptom(spo2.getVal()));

}

BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(90);
    BOOST_CHECK_EQUAL("Hypoxemia", spo2.determineSymptom(spo2.getVal()));

}

BOOST_AUTO_TEST_CASE(SuccessTestRangeTop) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(95);
    BOOST_CHECK_EQUAL("Normal", spo2.determineSymptom(spo2.getVal()));

}

BOOST_AUTO_TEST_CASE(FailTestRange) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(80);
    BOOST_CHECK_EQUAL("Normal", spo2.determineSymptom(spo2.getVal()));

}

BOOST_AUTO_TEST_CASE(SuccessTestCritical) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(80);
    BOOST_CHECK_EQUAL(true, spo2.isCritical(spo2.getVal()));

}

BOOST_AUTO_TEST_CASE(FailTestCritical) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(102);
    BOOST_CHECK_EQUAL(false, spo2.isCritical(spo2.getVal()));

}