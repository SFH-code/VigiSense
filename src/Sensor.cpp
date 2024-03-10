#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "MAX30102.h"

struct symptomRange{
    float min;
    float max;
    std::string symptom;
};

class sensor{ //Should this be specific to a sensor or should it be a general class that can be inherited by specific sensors?
    private:
        virtual float input() { return 0; } //Sets up the sensors and starts communication to obtain input

        virtual float processInput() { return 0; } //Processes input from sensor

    public:
        // Constructor to initialize the MAX30102 sensor with the default I2C address and start communication
        // Could also change the class name to "MAX30102Sensor" OR have "MAX30102Sensor" inherit from "sensor".  
        sensor() {
	    if (_sensor->begin() < 0) { //begins I2C communication with the sensor
		std::cout << "Failed i2c." << std::endl;
		// Failed i2c.
		throw;
	}
//	sensor->setup(0x2F);
	_sensor->setup(); // Configures the sensor with default settings & setup the interrupt to fire when new buffer is almost full
}

        MAX30102* _sensor; // Pointer to the MAX30102 sensor object

        virtual std::vector<symptomRange> symptomRanges() { return {}; } //Contains the ranges of the biosignal and the symptoms associated with it.

        virtual float critHigh() { return 0; } //Sets the critical high value of the biosignal

        virtual float critLow() { return 0; } //Sets the critical low value of the biosignal

        virtual std::string determineSymptom(float BiosignalVal) { return ""; } // Compares the biosignal value and returns the symptom

        virtual void critCheck(float BiosignalVal) {} //Checks if the biosignal value crosses the critical value and initiates an immediate alert
    };

    class oxyCon : public sensor {
        float input;
        float processInput() {
            //update to take when we have sensor input
            //input = sensor.read();
            //return input;
            //For now we will use a random number generator
            //input = rand() % 100 + 1;
            //return input;

            input = 0;
            return input;
        }
        float critHigh() {
            return 100;
        }

        float critLow() {
            return 88;
        }
        std::vector<symptomRange> symptomRange {{0, 88, "Critically Low Oxygen concentration"}, {88, 92, "Concerningly Low Oxygen Concentration"}, {92, 98, "Healthy Oxygen Concentration"}, {100, 130, "Sensor not working properly"}}; //This is a placeholder, we need to get the actual values from the sensor
        

        //R value calculation from sensor input
        float R;
        //SpO2 value calculation from R value
        float SpO2;

        std::string determineSymptom(float SpO2) {
            for (auto it = symptomRange.begin(); it != symptomRange.end(); ++it) {
                if (SpO2 > it->min && SpO2 < it->max) {
                    return it->symptom;
                }
            }
            return "undefined range";
        }
        void critCheck(float SpO2) {
            if (critLow() > SpO2 || critHigh() < SpO2) {

            }
            else {
                //Sends Immediate Alert!
            }
        }
    };