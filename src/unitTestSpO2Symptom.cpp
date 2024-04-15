//Unit tests for the SPO2 symptom determination function in the SPO2Tracker class

#define BOOST_TEST_MODULE SpO2SympCheck
#include <boost/test/unit_test.hpp>

#include "sensorTest.cpp"
#include "SPO2Tracker.cpp"
#include "DiagnosisInterface.h"





BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(90);
    BOOST_CHECK_EQUAL("Hypoxemia", spo2.determineSymptom(spo2.symptomRanges,90));

}

BOOST_AUTO_TEST_CASE(SuccessTestRangeTop) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(94);
    BOOST_CHECK_EQUAL("Concerning Oxygen Concentration", spo2.determineSymptom(spo2.symptomRanges,94));

}

BOOST_AUTO_TEST_CASE(FailTestRange) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(80);
    BOOST_CHECK_NE("Normal", spo2.determineSymptom(spo2.symptomRanges,80));

}

BOOST_AUTO_TEST_CASE(SuccessTestCritical) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(80);
    BOOST_CHECK_EQUAL("critLow", spo2.determineSymptom(spo2.symptomRanges,80));

}

BOOST_AUTO_TEST_CASE(FailTestCritical) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_NE("critLow", spo2.determineSymptom(spo2.symptomRanges,10000));

}

BOOST_AUTO_TEST_CASE(SuccessTestNegative) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("critLow", spo2.determineSymptom(spo2.symptomRanges,-1));
}

BOOST_AUTO_TEST_CASE(SuccessBoundarylow) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("Hypoxemia", spo2.determineSymptom(spo2.symptomRanges,88));
}

BOOST_AUTO_TEST_CASE(SuccessBoundaryMid) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("Concerning Oxygen Concentration", spo2.determineSymptom(spo2.symptomRanges,92));
}

BOOST_AUTO_TEST_CASE(SuccessBoundaryTop) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("Healthy Oxygen Concentration", spo2.determineSymptom(spo2.symptomRanges,95));
}
