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
		void setHr(int i);
		void setData(double testFrequency, bool flat); //Creates a pseudo data set for testing the peak detection algorithm
		std::vector<int32_t> getData(); //returns data set for testing the peak detection algorithm
        int spo2 =0;
		int hr =0;
		bool peakDetect(int32_t testdata);
		const static int8_t PAST_PEAKS_SIZE = 2;
		int SpO2Calc(int32_t localMaximaRed,int32_t localMinimaRed,int32_t localMaximaIR,int32_t localMinimaIR);
		int R;
		int latestSpO2;
		std::vector<int32_t> testData;

		
		


};