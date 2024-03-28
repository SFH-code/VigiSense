#define BOOST_TEST_MODULE SqrTests
#include <boost/test/unit_test.hpp>

#include "sensorTest.h"
#include "SPO2Tracker.h"



BOOST_AUTO_TEST_CASE(FailTest) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    spo2.start();
    s.setSpO2(60);
    BOOST_CHECK_EQUAL(0, spo2.determineSymptom(spo2.getVal()));

}