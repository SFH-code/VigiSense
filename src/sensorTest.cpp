#include <cmath> // For sine wave generation
#include "sensorTest.h"

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

void sensorTest::setData(){
// Test Parameters
    double testFrequency = 1.2;  // Hz (Approximate normal heart rate) 
    double samplingRate = 50.0;  // Hz (Adjust based on sensor)
    double testDuration = 5.0;   // Seconds
    int numSamples = testDuration * samplingRate;

    // Generate sine wave data
    std::vector<int32_t> testData;
    // include the -999 to indicate the beginning of peak detection calling
    testData.push_back(static_cast<int32_t>(-999));
    
    for (int i = 0; i < numSamples; ++i) 
    {
        double time = i / samplingRate;
        double amplitude = 1000;  // Adjust amplitude as needed
        double sineValue = amplitude * std::sin(2 * M_PI * testFrequency * time);
        testData.push_back(static_cast<int32_t>(sineValue));
    }
    
}