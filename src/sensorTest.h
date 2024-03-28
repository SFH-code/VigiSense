#include <cstdint>
#include <chrono>
#include "Sensor.h"

class sensorTest{
	public:
		
		sensorTest();
		~sensorTest();
		int getSpO2();
        void setSpO2(int i);
        int spo2 =0;


};