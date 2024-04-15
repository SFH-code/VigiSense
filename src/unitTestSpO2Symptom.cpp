//Unit tests for the SPO2 symptom determination function in the SPO2Tracker class

#define BOOST_TEST_MODULE SpO2SympCheck
#include <boost/test/unit_test.hpp>

#include "sensorTest.cpp"
#include "SPO2Tracker.cpp"
#include "DiagnosisInterface.h"



//Unit test module for the SPO2 symptom determination function in the SPO2Tracker class

//Test case for hypoxemia

BOOST_AUTO_TEST_CASE(SuccessTestRangeMid) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(90);
    BOOST_CHECK_EQUAL("Hypoxemia", spo2.determineSymptom(spo2.symptomRanges,90));

}

//test case for concerning oxygen concentration

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

//test case for critically low oxygen concentration

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

//test case for negative oxygen concentration

BOOST_AUTO_TEST_CASE(SuccessTestNegative) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("critLow", spo2.determineSymptom(spo2.symptomRanges,-1));
}

//Test case to check if the function works as expected at the boundaries between ranges

BOOST_AUTO_TEST_CASE(SuccessBoundarylow) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("Hypoxemia", spo2.determineSymptom(spo2.symptomRanges,88));
}

//Test case to check if the function works as expected at the boundaries between ranges

BOOST_AUTO_TEST_CASE(SuccessBoundaryMid) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("Concerning Oxygen Concentration", spo2.determineSymptom(spo2.symptomRanges,92));
}

//Test case to check if the function works as expected at the boundaries between ranges

BOOST_AUTO_TEST_CASE(SuccessBoundaryTop) {
    sensorTest s;
    SPO2Tracker spo2(&s);
    //spo2.start();
    //s.setSpO2(102);
    BOOST_CHECK_EQUAL("Healthy Oxygen Concentration", spo2.determineSymptom(spo2.symptomRanges,95));
}
