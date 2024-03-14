#include <iostream>
#include <unistd.h>
#include "Sensor.h"

using namespace std;


int main() {

	cout << "Starting..." << endl;
	sensor sensortest;
	sensortest.HRcalc();
    while (1) {
    sensortest.getSpO2();
    cout << "Began SpO2 calculation..." << endl;
    usleep(1000000);
    }
}