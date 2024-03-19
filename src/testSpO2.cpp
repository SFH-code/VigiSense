#include <iostream>
#include <unistd.h>
#include "Sensor.h"

using namespace std;


int main() {

	cout << "Starting..." << endl;
    MAX30102 s;
    sensor sensortest(&s);
    sensortest.begin();
	sensor sensortest;
    getchar();
}