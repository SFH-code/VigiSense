#include <iostream>
#include <unistd.h>
#include "MAX30102.h"
#include "Sensor.h"
#include "SPO2Tracker.h"

using namespace std;

MAX30102 heartSensor;

int main(void) {
	MAX30102 s;
	sensor MAX30102_sensor(&s);
	MAX30102_sensor.HRcalc();
	SPO2Tracker spo2(&MAX30102_sensor);
	spo2.start();
	getchar();
	spo2.stop();
	// at end of block destructor of sensor class is called which shutsdown max30102 instance s.
	return 0;
}
