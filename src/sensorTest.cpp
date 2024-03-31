#include "sensorTest.h"

sensorTest::sensorTest() {

}

sensorTest::~sensorTest() {

}

int sensorTest::getSpO2() {
    return spo2;
}

int sensorTest::getHR() {
    return -1;
}


void sensorTest::setSpO2(int i ) {
    spo2 = i;
}