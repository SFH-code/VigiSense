#include <cmath> // For sine wave generation
#include "sensorTest.h"
#include <iostream>

sensorTest::sensorTest() {

}

sensorTest::~sensorTest() {

}

int sensorTest::getSpO2() {
    return spo2;
}

int sensorTest::getHR() {
    return -1;
}

void sensorTest::setSpO2(int i ) {
    spo2 = i;
}

void sensorTest::setHr(int i ) {
    hr = i;
}

void sensorTest::setData(double testFrequency, bool flat) {
	// Test Parameters
	flat = false;
	testFrequency = 1.2;  // Hz (Approximate normal heart rate) 
	double samplingRate = 50.0;  // Hz (Adjust based on sensor)
	double testDuration = 5.0;   // Seconds
	int numSamples = testDuration * samplingRate;

	// Generate sine wave data
	std::vector<int32_t> testData;
	// include the -999 to indicate the beginning of peak detection calling
	testData.push_back(static_cast<int32_t>(-999));
	
	for (int i = 0; i < numSamples; ++i) 
	{ 
		if (flat) {
			double time = i / samplingRate;
			double amplitude = 1000;  // Adjust amplitude as needed
			double sineValue = amplitude * std::sin(2 * M_PI * testFrequency * time);
			testData.push_back(static_cast<int32_t>(sineValue));
		}
		else if (!flat) {
			testData.push_back(0);
		}
	}
}

std::vector<int32_t> sensorTest::getData(){
	return testData;
}

//Peak Detection
		bool crest = false;
		bool trough = false;
		uint8_t dataBeenIncreasing = 0;
		uint8_t nextPastPeaksIndex = 0;
		int32_t TestDataLastValue;
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

bool sensorTest::peakDetect(int32_t testdata) {
	//No longer IRlastvalue to eliminate the filtering and getIR()
	if (testdata == -999) {
		// This is first time peakDetect is called.
		TestDataLastValue = testdata; //For emulating the IRlastValue
		return false;
	}
	//Eliminated the IRlastvalue to eliminate the filtering and getIR()
	if (crest && trough && testdata > TestDataLastValue) { //beat sequence is crest then trough as current IR has to be higher than the value of the trough
		dataBeenIncreasing++;
		if (dataBeenIncreasing >= 2) {
			// This is a beat.
			// Add local maxima & minima to past
			pastMaximasIR[nextPastPeaksIndex] = localMaximaIR; // this is the actual crest value
			pastMinimasIR[nextPastPeaksIndex] = localMinimaIR; // this is the actual trough value
			pastMaximasRed[nextPastPeaksIndex] = localMaximaRed; // this is the actual crest value
			pastMinimasRed[nextPastPeaksIndex] = localMinimaRed; // this is the actual trough value
			

			nextPastPeaksIndex++;
			if (nextPastPeaksIndex >= sensorTest::PAST_PEAKS_SIZE) {
				nextPastPeaksIndex = 0;
			}
			// Reset values
			crest = trough = false;
			dataBeenIncreasing = 0;
			localMaximaIR = -9999;
			localMinimaIR = 9999;
			TestDataLastValue = testdata; //For emulating the IRlastValue
			return true;
		}
	}

	//int32_t threshold = getPeakThreshold();
	//std::cout << "Threshold: " << threshold << ", max: " << localMaxima << ", min: " << localMinima << std::endl;
	if (testdata > localMaximaIR) {
		localMaximaIR = testdata;
		if (testdata > 950) { //Sine wave amplitude is 1000
			crest = true;
		}
	}

	if (crest && testdata < localMinimaIR) {
		localMinimaIR = testdata;
		if (crest && testdata < -950) { ///Sine wave amplitude is -1000
			trough = true;
		}
	}
	TestDataLastValue = testdata; //For emulating the IRlastValue
	return false;

	
}



int32_t sensorTest::SpO2Calc(int32_t MaximaIR, int32_t MinimaIR, int32_t MaximaRed, int32_t MinimaRed){
		if (MinimaIR != 0 && MinimaRed != 0) {
			R = ((MaximaRed - MinimaRed) / MinimaRed) / ((MaximaIR - MinimaIR) / MinimaIR);
			latestSpO2 = 104 - 17 * R;
			return latestSpO2;
		} else {
			// Division by zero alert
			std::cout << "Division by zero error for R calculation!" << std::endl;
			return EXIT_FAILURE;
		}
		
}
