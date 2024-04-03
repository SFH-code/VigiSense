//Unit test for the peak detection function in the Sensor class

////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <string>
#include <cmath> // For sine wave generation
#include "MAX30102.h"
#include "Sensor.h"
#include "DigitalFilters.h"
#include <boost/test/unit_test.hpp> // Include Boost.Test

// ... your existing code ...

BOOST_AUTO_TEST_SUITE(PeakDetectTests)

BOOST_AUTO_TEST_CASE(SineWavePeakDetection) 
{
    



    // Simulate feeding data to peak detection
    for (int32_t data : testData) 
    {
        bool isPeak = sensor::peakDetect(data);

        

        if (isPeak) 
        {
            // Count peaks, implement verification logic here
            int numPeaksDetected++;  
            
        }
         
    }
}BOOST_CHECK_EQUAL(numPeaksDetected, 3); //3 beats only since it counts two peaks as a single beat of the heart

BOOST_AUTO_TEST_SUITE_END()
