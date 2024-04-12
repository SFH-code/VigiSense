#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <string>
#include "MAX30102.h"
#include "Sensor.h"
#include "DigitalFilters.h"

//Some code refactored from HeartRate.cpp
        
LowPassFilter lpf(0.08, M_PI);
HighPassFilter hpf(0.08, M_PI);

//R value calculation from sensor input
float R;
//SpO2 value calculation from R value
float SpO2;
bool crest = false;
bool trough = false;
uint8_t dataBeenIncreasing = 0;
uint8_t nextPastPeaksIndex = 0;


/**
 * Constructor to initialize the MAX30102 sensor with the default I2C address and start communication
 * Could also change the class name to "MAX30102Sensor" OR have "MAX30102Sensor" inherit from "sensor".  
*/
sensor::sensor(MAX30102 *s) {
	sensor::_sensor = s;
	if (_sensor->begin() < 0) { //begins I2C communication with the sensor
	std::cout << "Failed i2c." << std::endl;
	// Failed i2c.
	throw;
	}
	//	sensor->setup(0x2F);
	_sensor->setup(); // Configures the sensor with default settings & setup the interrupt to fire when new buffer is almost full
}

	// Destructor
sensor::~sensor() {
	running = false;
	_sensor->shutDown();
}

void sensor::HRcalc() {
	if (runningHR) return;
	runningHR = true;

	// Init last values.
	irLastValue = -999;
	redLastValue = -999;
	// Init local maxima/minima for peak detection
	localMaximaIR = -9999;
	localMinimaIR = 9999;
	// Get current time.
	auto timeCurrent = std::chrono::system_clock::now();
	// Init last heartbeat times.
	timeLastIRHeartBeat = timeCurrent;
	timeLastRedHeartBeat = timeCurrent;

	std::thread t1(&sensor::loopThread, this);
	t1.detach();
}

void sensor::loopThread() {
	while (runningHR) {
		runHRCalculationLoop();
	}
}
    
/**
 * Stops the calculation loop.
 * You may no longer get heart rate data after calling this function.
 */
void sensor::stopHRcalc() {
	runningHR = false;
	resetCalculations();
}

//Heart rate calculation loop in detached thread
//Original check() function is removed as getIR/Red access the storage which is updated by the interrupt which is activated by the constructor of the sensor class
void sensor::runHRCalculationLoop() {
// Get data from sensor->and store in global variables
	auto timeCurrent = std::chrono::system_clock::now();
	uint32_t irValue =  _sensor->getIR();
	

	// get the number of miliseconds passed since we last ran the loop.
	int loopDelta = std::chrono::duration_cast<std::chrono::milliseconds>(timeCurrent - timeLastLoopRan).count();
	// We're finished with timeLastLoopRan, so let's update it's value for next time.
	timeLastLoopRan = timeCurrent;

	// Check whether finger is on sensor->
	if (irValue < 100000) {
		// Finger is not on sensor->
		// Clear all calculations and exit out of loop.
		resetCalculations();
		return;
	}

	// Calculate the IR heart rate //
	
	int32_t filteredIRValue = static_cast<int32_t>(irValue);
	filteredIRValue = lpf.update(filteredIRValue);
	filteredIRValue = hpf.update(filteredIRValue);

	int timeSinceLastIRHeartBeat = std::chrono::duration_cast<std::chrono::milliseconds>(timeCurrent - timeLastIRHeartBeat).count();

	if (peakDetect(filteredIRValue)) {
		int _irBPM = 60000/timeSinceLastIRHeartBeat;
		latestIRBPM = _irBPM;
		bpmBuffer[nextBPMBufferIndex++] = _irBPM;
		if (nextBPMBufferIndex >= BPM_BUFFER_SIZE) nextBPMBufferIndex = 0;
		if (localMinimaIR != 0 && localMinimaRed != 0) { //Avoid division by zero
			// Calculate R value
			// See https://github.com/2468513H/VigiSense/files/14432156/max3010x-ev-kits-recommended-configurations-and-operating-profiles.pdf
			// Page 6
			// Before division, parameters should be transferred into float to avoid rounding to 0
			float MaxR = localMaximaRed;
			float MinR = localMinimaRed;
			float MaxIR = localMaximaIR;
			float MinIR = localMinimaIR;
			R = ((MaxR-MinR)/MinR)/((MaxIR-MinIR)/MinIR); //converted to float because intermediate decimal value is being rounded to 0
			//R = ((localMaximaRed - localMinimaRed) / localMinimaRed) / ((localMaximaIR - localMinimaIR) / localMinimaIR);
			latestSpO2 = 104 - 17 * R; //  best-fit straight-line approximation of SpO2 vs. R data.
		} else {
			// Division by zero alert
			std::cout << "Division by zero error for R calculation!" << std::endl;
		}
		spo2Buffer[nextSPO2BufferIndex++] = latestSpO2;
		if (nextSPO2BufferIndex >= SPO2_BUFFER_SIZE) nextSPO2BufferIndex = 0;

		// Update timeLastIRHeartBeat for next time.
		timeLastIRHeartBeat = timeCurrent;
	}
	// We're finished with irLastValue, so let's update their value for next time.
	irLastValue = filteredIRValue;
	
}

/**
 * Updates the temperature variable.
 */
void sensor::updateTemperature() {
	latestTemperature = _sensor->readTemperatureF();
}

/**
 * Detects peaks in heart data.
 * Returns true when input data is a peak.
 */


int32_t sensor::getPeakThreshold() {
	int32_t avgMaximas = 0;
	int32_t avgMinimas = 0;
	for (int i = 0; i < sensor::PAST_PEAKS_SIZE; i++) {
		avgMaximas += pastMaximasIR[i];
		avgMinimas += pastMinimasIR[i];
	}
	avgMaximas /= sensor::PAST_PEAKS_SIZE;
	avgMinimas /= sensor::PAST_PEAKS_SIZE;
	int32_t threshold = (avgMaximas+avgMinimas)/1.5;
	if (threshold > 0 || threshold < -500) {
		return -20;
	}
	return threshold;
}


bool sensor::peakDetect(int32_t data) {
	if (irLastValue == -999) {
		// This is first time peakDetect is called.
		return false;
	}
	if (crest && trough && data > irLastValue) { //beat sequence is crest then trough as current IR has to be higher than the value of the trough
		dataBeenIncreasing++;
		if (dataBeenIncreasing >= 2) {
			// This is a beat.
			// Add local maxima & minima to past
			pastMaximasIR[nextPastPeaksIndex] = localMaximaIR; // this is the actual crest value
			pastMinimasIR[nextPastPeaksIndex] = localMinimaIR; // this is the actual trough value
			pastMaximasRed[nextPastPeaksIndex] = localMaximaRed; // this is the actual crest value
			pastMinimasRed[nextPastPeaksIndex] = localMinimaRed; // this is the actual trough value
			

			nextPastPeaksIndex++;
			if (nextPastPeaksIndex >= sensor::PAST_PEAKS_SIZE) {
				nextPastPeaksIndex = 0;
			}
			// Reset values
			crest = trough = false;
			dataBeenIncreasing = 0;
			localMaximaIR = -9999;
			localMinimaIR = 9999;
			
			return true;
		}
	}

	//int32_t threshold = getPeakThreshold();
	//std::cout << "Threshold: " << threshold << ", max: " << localMaxima << ", min: " << localMinima << std::endl;
	if (data > localMaximaIR) {
		localMaximaIR = data;
		if (data > 100) { //might want to calibrate this everytime sensor is used
			crest = true;
			//filter red value only at crest and trough for efficiency
			uint32_t localMaximaRedUnfilt = _sensor->getRed(); //Only needed when crest and trough are detected
			int32_t filteredRedValue = static_cast<int32_t>(localMaximaRedUnfilt);
			localMaximaRed = lpf.update(filteredRedValue);
			localMaximaRed = hpf.update(filteredRedValue);
		}
	}

	if (crest && data < localMinimaIR) {
		localMinimaIR = data;
		if (crest && data < -100) { //might want to calibrate this everytime sensor is used
			trough = true;
			//filter red value only at crest and trough for efficiency
			uint32_t localMinimaRedUnfilt = _sensor->getRed(); //Only needed when crest and trough are detected
			int32_t filteredRedValue = static_cast<int32_t>(localMinimaRedUnfilt);
			localMinimaRed = lpf.update(filteredRedValue);
			localMinimaRed = hpf.update(filteredRedValue);
		}
	}

	return false;
}


/**
 * Clears all calculations.
 */
void sensor::resetCalculations() {
	// Clear stored heart rates.
	latestIRBPM = 0;
	latestRedBPM = 0;

	// Reset peak detection.
	crest = trough = false;
	nextPastPeaksIndex = 0;
	dataBeenIncreasing = 0;
	localMaximaIR = -9999;
	localMinimaIR = 9999;

	// Reset bpm buffer
	for (int i = 0; i < BPM_BUFFER_SIZE; i++) {
		bpmBuffer[i] = 0;
	}

	// Reset ACDC values buffer
	for (int i = 0; i < SPO2_BUFFER_SIZE; i++) {
		spo2Buffer[i] = 0;
	}

	// Reset last values.
	irLastValue = -999;
	redLastValue = -999;

	// Get current time.
	auto timeCurrent = std::chrono::system_clock::now();
	// Reset last heartbeat times.
	timeLastIRHeartBeat = timeCurrent;
	timeLastRedHeartBeat = timeCurrent;
}

/**
 * Returns the latest calculated IR heart rate. (unchecked!)
 */
// int heartRateMeasure::getLatestIRHeartRate() {
// 	if (latestIRBPM == 0) {
// 		return -1;
// 	}
// 	return latestIRBPM;
// }


/**
 * Returns the average measured heart rate.
 * This method ignores heart rate values greater than 150 or lower than 45.
 */
int sensor::getHR() {
	int avgBPM = 0;
	int bpmCount = 0;
	for (int i = 0; i < BPM_BUFFER_SIZE; i++) {
		int _bpm = bpmBuffer[i];
		if (_bpm > 45 && _bpm < 150) {
			avgBPM += _bpm;
			bpmCount++;
		}
	}
	if (bpmCount > 0) avgBPM /= bpmCount;
	// if (avgBPM<critLow||avgBPM>critHigh){
	// 	//insert critical response interrupt
	// }
	return (avgBPM == 0) ? -1 : avgBPM;
}


int sensor::getSpO2() {
	int avgSPO2 = 0;
	int SPO2Count = 0;
	for (int i = 0; i < SPO2_BUFFER_SIZE; i++) {
		avgSPO2 += spo2Buffer[i];
		SPO2Count++;
		
	}
	if (SPO2Count > 0) avgSPO2 /= SPO2Count;
	// if(avgSPO2<critLow){
	// 	//insert critical response interrupt
	// }
	return (avgSPO2 == 0) ? -1 : avgSPO2;
}


// std::string spO2Measure::determineSymptom(float baseline){
// 	int spO2 = this->getSpO2();
// 	for (int i = 0; i < symptomRanges.size(); ++i){
//             if (spO2>symptomRanges[i].min && spO2<symptomRanges[i].max){
//                 return symptomRanges[i].symptom;
//             }
//         }    
//     return "undefined range";

// }


/**
 * Returns the latest calculated Red heart rate. (unchecked!)
 */
// int heartRateMeasure::getLatestRedHeartRate() {
// 	if (latestRedBPM == 0) {
// 		return -1;
// 	}
// 	return latestRedBPM;
// }


float sensor::getLatestTemperatureF() {
	return latestTemperature;
}


// std::string heartRateMeasure::determineSymptom(float baseline){
// 	int spO2 = this->getSafeIRHeartRate();
// 	for (int i = 0; i < symptomRanges.size(); ++i){
//             if (spO2>symptomRanges[i].min && spO2<symptomRanges[i].max){
//                 return symptomRanges[i].symptom;
//             }
//         }    
//     return "undefined range";

// }


   
