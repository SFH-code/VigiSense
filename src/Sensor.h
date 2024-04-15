#pragma once
#include <cstdint>
#include <chrono>
#include "MAX30102.h"

// struct symptomRange{
//     float min;
//     float max;
//     std::string symptom;
// };

//Code refactored from HeartRate.h

class sensor{
	public:
		
		sensor(MAX30102 *sensor);
		~sensor();
		//Check which functions are fine as is and which need editing/removing
		void begin();
		void stop();
		
		float getLatestTemperatureF();
		void HRcalc();
		void stopHRcalc();

		// getter for SPO2 and HR
		int getSpO2();
		int getHR();

	protected:
		MAX30102* _sensor;
		bool running = false;
		bool runningHR = false;

        //Check which functions are fine as is and which need editing/removing
		
		const int static BPM_BUFFER_SIZE = 4; //changed from being 100
		int32_t bpmBuffer[BPM_BUFFER_SIZE];
		int nextBPMBufferIndex = 0;
		
		const int static SPO2_BUFFER_SIZE = 4; //changed from being 100
		int32_t spo2Buffer[SPO2_BUFFER_SIZE];
		int nextSPO2BufferIndex = 0;

		std::chrono::time_point<std::chrono::system_clock> timeLastLoopRan;
		// IR Data
		std::chrono::time_point<std::chrono::system_clock> timeLastIRHeartBeat;
		int32_t irLastValue; 
		int latestIRBPM;
		int averageIRBPM;
		// Red Data
		std::chrono::time_point<std::chrono::system_clock> timeLastRedHeartBeat;
		uint64_t redLastValue; 
		int latestRedBPM;
		// Temperature Data
		float latestTemperature = -999;

		// For Peak Detection
		
		int32_t localMaximaIR;
		int32_t localMinimaIR;
		int32_t localMaximaRed;
		int32_t localMinimaRed;
		const static int8_t PAST_PEAKS_SIZE = 2;
		int32_t pastMaximasIR[PAST_PEAKS_SIZE];
		int32_t pastMinimasIR[PAST_PEAKS_SIZE];
		int32_t pastMaximasRed[PAST_PEAKS_SIZE];
		int32_t pastMinimasRed[PAST_PEAKS_SIZE];
		// SpO2 data
		//int R;
		float latestSpO2;


		void loopThread();
		void runHRCalculationLoop();
		void updateTemperature();
		void resetCalculations();
		int32_t Derivative(int32_t data);
		int32_t getPeakThreshold();
		bool peakDetect(int32_t data);
};

// class spO2Measure : public sensor{
// 	public:
// 		std::vector<symptomRange> symptomRanges {
// 			{0,88,"Critically Low Oxygen concentration"},
// 			{88,92,"Concerningly Low Oxygen Concentration"},
// 			{92,100,"Healthy Oxygen Concentration"}};
// 		float critLow = 88;
// 		int getSpO2();
// 		std::string determineSymptom(float baseline);
// };

// class heartRateMeasure : public sensor{
// 	public:
// 		std::vector<symptomRange> symptomRanges {
// 			{0,60,"Bradycardia"},
// 			{60,100,"Normal resting heart rate"},
// 			{100,200,"Tachyacardia"}};
// 		float critHigh = 120;
// 		float critLow = 40;
// 		int getSafeIRHeartRate();
// 		int getLatestIRHeartRate();
// 		int getLatestRedHeartRate();
// 		std::string determineSymptom(float baseline);
// };
