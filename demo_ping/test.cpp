#include <iostream>
#include <unistd.h>
#include "SPO2Tracker.h"

using namespace std;


int main(void) {
	SPO2Tracker spo2;
	spo2.start();
	getchar();
	spo2.stop();
	// at end of block destructor of sensor class is called which shutsdown max30102 instance s.
	return 0;
}
