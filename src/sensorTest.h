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
		void setData();
        int spo2 =0;
		bool peakDetect(int32_t testdata);
		const static int8_t PAST_PEAKS_SIZE = 2;

		
		


};