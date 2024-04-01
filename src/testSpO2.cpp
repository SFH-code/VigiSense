#include <iostream>
#include <unistd.h>
#include "Sensor.h"
#include "SPO2Tracker.h"
#include "HRTracker.h"

using namespace std;


int main() {

	cout << "Starting..." << endl;

    // initialise MAX30102 class for getting red and infrared intensity values using interrupts
    // setsup I2C connection and ISRs
    MAX30102 s;

    // initialise code for calculating SPO2 and HR from red and infrared intensity values, using a pointer to the MAX30102 instance
	sensor MAX30102_sensor(&s);
	MAX30102_sensor.HRcalc();

    // constructor for functionality of sensor
    // Eg: SPO2_tracker and HR_tracker
    SPO2Tracker spo2(&MAX30102_sensor);
    HRTracker hr(&MAX30102_sensor);
    spo2.start();
    hr.start();
    getchar();

    // terminate all thread and stop ISR routine sequence
    spo2.stop();
    hr.stop();
    MAX30102_sensor.stopHRcalc();
    s.shutDown();
}