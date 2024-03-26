#include <iostream>
#include <unistd.h>
#include "Sensor.h"

using namespace std;


int main() {

	cout << "Starting..." << endl;
    MAX30102 s;
	sensor MAX30102_sensor(&s);
    // initialise sensor with calculation for HR and SPO2
	MAX30102_sensor.HRcalc();
    // constructor for functionality of sensor
    // Eg: SPO2_tracker and HR_tracker
}