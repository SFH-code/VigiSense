//Unit test for the peak detection function in the Sensor class

////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define BOOST_TEST_MODULE PeakDetect

#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <string>
#include <cmath> // For sine wave generation
#include "MAX30102.cpp"
#include "sensorTest.cpp"
#include "DigitalFilters.h"
#include <boost/test/unit_test.hpp> // Include Boost.Test



BOOST_AUTO_TEST_CASE(SuccessSineWavePeakDetection) 
{
    sensorTest s
    s.setData(1.2, false) // creates a sine wave with amplitude 1000
    sensorTest::getData() //returns test data
    int numPeaksDetected = 0; // Counter for detected peaks

    // Simulate feeding data to peak detection
    for (int32_t data : testData) 
    {
        bool isPeak = sensorTest::peakDetect(data);
        
        

        if (isPeak) 
        {
            // Count peaks, implement verification logic here
            numPeaksDetected++;  
            
        }
         
    }
    return numPeaksDetected;
}BOOST_CHECK_EQUAL(numPeaksDetected, 3); //3 beats only since it counts two peaks as a single beat of the heart

BOOST_AUTO_TEST_CASE(SuccessflatwavePeakDetection) 
{

    // Simulate feeding data to peak detection
    sensorTest::setData(1.2, true) // creates a flat wave with amplitude 0
    sensorTest::getData() //returns test data
    int numPeaksDetected = 0; // Counter for detected peaks
    
    for (int32_t data : testData) 
    {
        bool isPeak = sensorTest::::peakDetect(data);

        

        if (isPeak) 
        {
            // Count peaks, implement verification logic here
            int numPeaksDetected++;  
            
        }
         
    }
    return numPeaksDetected;
}BOOST_CHECK_EQUAL(numPeaksDetected, 0); //3 beats only since it counts two peaks as a single beat of the heart


