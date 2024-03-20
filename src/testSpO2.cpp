#include <iostream>
#include <unistd.h>
#include "Sensor.h"
#include "MAX30102.h"

using namespace std;


int main() {

    cout << "Starting..." << endl;
    MAX30102 s;
    sensor sensortest(&s);
    sensortest.begin();
    getchar();
    sensortest.stopHRcalc();
}
