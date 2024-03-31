#include <cstdint>
#include <chrono>
#include "Sensor.h"
#include "testParent.h"


class sensorTest:public testParent{
	public:
		
		sensorTest();
		~sensorTest();
		int getSpO2() override;
		int getHR() override;
        void setSpO2(int i);
        int spo2 =0;


};