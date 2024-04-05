//Unit test for the peak detection function in the Sensor class

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <string>
#include <cmath> // For sine wave generation
#include "MAX30102.h"
#include "sensorTest.h"
#include "DigitalFilters.h"
#include <boost/test/unit_test.hpp> // Include Boost.Test



BOOST_AUTO_TEST_SUITE(PeakDetectTests)

BOOST_AUTO_TEST_CASE(SuccessSineWavePeakDetection) 
{
    
    sensorTest::setData(1.2, false) // creates a sine wave with amplitude 1000
    sensorTest::getData() //returns test data

    // Simulate feeding data to peak detection
    for (int32_t data : testData) 
    {
        bool isPeak = sensorTest::peakDetect(data);

        

        if (isPeak) 
        {
            // Count peaks, implement verification logic here
            int numPeaksDetected++;  
            
        }
         
    }
    return numPeaksDetected;
}BOOST_CHECK_EQUAL(numPeaksDetected, 3); //3 beats only since it counts two peaks as a single beat of the heart

BOOST_AUTO_TEST_CASE(FailedflatwavePeakDetection) 
{

    // Simulate feeding data to peak detection
    sensorTest::setData(1.2, true) // creates a flat wave with amplitude 0
    sensorTest::getData() //returns test data
    
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
}BOOST_CHECK_EQUAL(numPeaksDetected, 3); //3 beats only since it counts two peaks as a single beat of the heart

BOOST_AUTO_TEST_SUITE_END()
