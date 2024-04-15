Unit tests can be found on the [Unit-Tests](https://github.com/2468513H/VigiSense/tree/Unit-Tests) branch.

To add a new unit test, you would need to figure out what function to test and which file the function resides in. This backhanded way uses derived and related classes to test is because classes rely on sensor values that come in intervals based on the interrupts. This means that functions are encapsulated in a process that separates the conversion of raw infrared and red intensity values to oxygen level and heart rate values. 


## An example implementation:

Check out our website: https://2468513h.github.io/VigiSense/

Visit us on socials:

Instagram: @VigiSense1 (https://www.instagram.com/vigisense1/)
Linkedin: https://www.linkedin.com/company/vigisense11/

Sensor used: MAX30102 for SP02 and Heart rate tracking.


Assuming you want to test the functionality of alerting another user using fastdds. Looking at the source code, this function resides in any implementation of the virtual class `DiagnosisInterface.h` as the function `ping()`. `ping` relies on `getSPO2` or `getHR` which is a function of both the `SPO2Tracker` class. To add a unit test:

1. Make a header file specifically for unit test in this case: `testParent.h`, 

2. Make a new class called `sensorTest` as a related class to `sensor` to override certain values. Make the `testParent.h` class defined as a virtual parent class of `sensorTest` and `sensor` class. Include the functions that are to be tested.

![image](https://github.com/2468513H/VigiSense/assets/77401199/eb7b14dc-a864-4fef-b581-2f0720c5db58)


![image](https://github.com/2468513H/VigiSense/assets/77401199/c7ed8618-1474-4968-b653-bee35b103eae)

3. Define functions to control values that come in through raw sensor values. 

![image](https://github.com/2468513H/VigiSense/assets/77401199/2db06daa-d6f6-46e8-a870-a7592c0d4d35)

4. In the unit test implementation file (`unitTest.cpp`) define test cases using functions in [2]. Where the pointer pass into the `SPO2Tracker` constructor is an instance of `sensorTest` instead of `sensor`. 

![image](https://github.com/2468513H/VigiSense/assets/77401199/a773dd88-9672-476a-aa2c-2ff2a21013c8)

_**Check out the source code for how diagnosisInterface derived classes (such as `SPO2 Tracker`) are called for a better understanding of code architecture. It uses threads to call functions such as `getSPO2()` that are defined in either `sensor` or `sensorTest`.**_

## Prerequisites

CMake
```
apt-get install cmake
```

PIGPIO
```
apt-get install pigpio
```

Fast CDR
```
apt install libfastcdr-dev
```

Fast RTPS
```
apt install libfastrtps-dev
```

Fast DDS tools
```
apt install fastddsgen fastdds-tools
```


To run:
```
git clone https://github.com/2468513H/VigiSense.git
cd VigiSense/src
mkdir build
cd build
cmake ..
make
sudo ./test
```



The repo contains refactored code for:

MAX30102 library (edited from: https://github.com/garrettluu/max30102-rpi/tree/08b8e2aa917817f8e57aca7f04da4b7b1180f17a)


## Functionality of each C++/H file:

### UML Class Diagram

![finalised class VigiSense drawio](https://github.com/2468513H/VigiSense/assets/77401199/7f21bd00-3ee8-4322-aa86-fb7be6036402)


### 1. MAX30102.h/MAX30102.cpp

Datasheet: https://www.analog.com/media/en/technical-documentation/data-sheets/MAX30102.pdf

This file is the low-level library for reading raw data of red light intensity and infrared intensity values from the MAX30102 sensor. The code is refactored from the repo mentioned above. Changes are made to have data be extracted when an interrupt is called, instead of polling (use case before refactored). Interrupts are done by toggling the Interrupt Status Register for A_FULL, which sets the sensor to only send an interrupt when the internal buffer of raw red and IR data is almost full. The ISR is defined as gpioISR() under the header file. 

_Design reasoning: encapsulate the extraction of raw data (IR and red intensity values) from the calculation of meaningful data (heart rate, SPO2)_

Some important functions are:

> 1. begin() - starts I2C connection using address 0x57 (address for MAX3010x)
> 2. setup() - setup sensor based on parameters that are given, also starts the ISR on GPIO pin 0
> 3. shutDown() - terminate the gpioISR, and i2c connection
> 4. getRed() - returns an uint32_t of the current raw data for red intensity value
> 5. getIR() - returns an uint32_t of the current raw data for IR intensity value

### 2. Sensor.cpp/Sensor.h

This file contains the calculation needed for obtaining the heart rate and SPO2 values. This class has a constructor that takes in a pointer to an instance of MAX30102 class. A thread is used to obtain the red and IR intensity values using getRed() and getIR() from the MAX30102 instance passed in. Value is filtered using a bandpass filter, and the raw IR value is passed into the peakDetect() function. This function keeps tracks of previous and current IR values to determine if it is a trough or peak. This is essential as AC/DC values for raw red and IR values are collected to be used in the calculation for SPO2 (Issue #30: https://github.com/2468513H/VigiSense/issues/30). Further explanation can be found on the wiki: https://github.com/2468513H/VigiSense/wiki/Oximeter-&-Data-Significance. 

_Design reasoning: encapsulate the calculation of heart rate and SPO2 from triggered actions due to sudden drop in either value, or detection of critical value._

Some important functions are:

> 1. sensor(MAX30102 *s) constructor - calls begin() and setup() on the MAX30102 instance
> 2. ~sensor() destructorl - calls stopHRCalc() and s->shutdown()
> 4. HRcalc() - starts the thread used to calculate SPO2 and HR
> 5. stopHRCalc() - sets the boolean that keeps the thread running to be false, and hence terminate the thread
> 6. getHR() - returns an integer of the current safe heart rate value
> 7. getSPO2() - returns an integer of the current safe SPO2 value

### 3. DiagnosisInterface.h

Children class: SPO2Tracker.cpp/h, HRTracker.cpp/h

_Design reasoning: ease of extension by adding more sensors._

This is an abstract parent class that is required to implement for further extension of functionality using more sensors. Assuming the library and calculation of functionality of the sensor is provided, this class places a strict rule on how alerts are to be implemented. The class uses the following pure virtual functions:
```
virtual void start() = 0;    // called to start the instance of a derived class, instances will only trigger alerts (pings) after start() is called
virtual void stop() = 0;     // called to stop the instance of a derived class, instances will stop triggering alerts even if the conditional is met after stop() is called
virtual void ping() = 0;     // alert function using FastDDS
virtual int getVal() = 0;    // overriden function should be sensor specific 
```

DiagnosisInterface.h also requires derived classes to implement a vector of symptomRange struct. 
```
struct symptomRange{
    float min;
    float max;
    std::string symptom;
};
```

The symptomRanges which is a vector of symptomRange should correspond to critically low to acceptable (but tiered symptoms) to critically high values. For example: the symptomRanges of HRTracker would look like:
```
std::vector<symptomRange> symptomRanges {
  {0,60,"Bradycardia"},
  {60,100,"Normal resting heart rate"},
  {100,200,"Tachyacardia"}};
```
Where the minimum, and maximum values are defined for each symptom. The values implemented in SymptomRanges is used in the static function determineSymptom(symptomRanges, value):
```
static std::string determineSymptom(std::vector<symptomRange> symptomRanges, int val){
  for (int i = 0; i < symptomRanges.size(); ++i){
        if (val>symptomRanges[i].min && val<symptomRanges[i].max){
            return symptomRanges[i].symptom;
        }
    }    
    if (val < symptomRanges[0].min) {
        return "critLow";
    } else if (val > symptomRanges[symptomRanges.size() -1].max)
    {
        return "critHigh";
    } else {
        return "Out of range";
    }
};
```
That returns a symptom based on the current value and the defined symptom ranges. 

This abstract parent class simplifies the diagnosis into ranges of values that corresponds to a symptom or critically high/low values. This design is intuitive as it is applicable for things such as using body temperature to detect different level of fever, or blood sugar level that corresponds to different levels and tiers where the current value is passed in as an integer. 

#### Description of ping() using FastDDS

FastDDS is used to alert other machines sharing the same network. Inside inherited children implementation files, it is required to include "DevicePublisher.cpp".

The topic can be found in alert.idl, which has parameters for an integer (index) and a string (message). Code implemented in DevicePublisher allows for a message to be published using the publish() function. An example of this can be seen on the implementation of pingThread in the SPO2tracker.cpp file.
```
void SPO2Tracker::ping() {
	std::thread t2(&SPO2Tracker::pingThread, this);
	t2.detach();
}

// thread for pinging SPO2 critical values, 
void SPO2Tracker::pingThread() {
    // start threads for FastDDS
    std::cout<<"Starting alert message"<<std::endl;
    // sends the same message 3 times
    uint32_t tries = 3;

    DevicePublisher alertPub;
    if (!alertPub.init()) {
        std::cerr << "Pub not init'd." << std::endl;
        return;
    }

    alert alertMessage;
    // add more specific message
    alertMessage.message("message");
    uint32_t pingTries = 0;
    // tries to send a message every 1 second for 3 times
    while (pingTries < tries) {
        if (alertPub.publish(alertMessage)) {
            pingTries++;
        } else {
            std::cout << "Waiting for listener" << std::endl;
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
```
In this implementation, it waits for a listener/subscriber to listen to any incoming signals; if a listener is detected, it tries to send "message" 3 times with a 1 second interval. This is done inside a thread in case there are no listeners in the same network, causing potential blocking.

Devices having DeviceSubscriber running in the same network would be a listener and will receive a message.

## Example of how the project runs:
```
#include <iostream>
#include <unistd.h>
#include "Sensor.h"
#include "SPO2Tracker.h"
#include "HRTracker.h"

using namespace std;


int main() {

	cout << "Starting..." << endl;

    	// initialise MAX30102 class for getting red and infrared intensity values using interrupts
    	// setsup I2C connection and ISRs
	MAX30102 s;

    	// initialise code for calculating SPO2 and HR from red and infrared intensity values, using a pointer to the MAX30102 instance
	sensor MAX30102_sensor(&s);
	MAX30102_sensor.HRcalc();

    	// constructor for functionality of sensor
    	// Eg: SPO2_tracker and HR_tracker
    	SPO2Tracker spo2(&MAX30102_sensor);
    	HRTracker hr(&MAX30102_sensor);
    	spo2.start();
    	hr.start();
    	getchar();

    	// terminate all thread and stop ISR routine sequence
    	spo2.stop();
    	hr.stop();
    	MAX30102_sensor.stopHRcalc();
}
```

The sequence diagram of the workflow can be found below:

![SequenceDiagram](https://github.com/2468513H/VigiSense/assets/77401199/fca81127-5f7a-4f9d-97d2-264023954ff4)

## Performance Tests:

Performance tests are done by evaluating high-priority and long functions that run in the program, 2 functions are used in this testing. The MAX30102.cpp/h file uses an interrupt service routine that has a pointer to a function that reads a buffer of raw data values on a buffer and retrieves the red and infrared intensity values when an interrupt is called. Since this is called in an interrupt service routine that is called when a falling edge is detected on GPIO 0 (physical pin 11) on a Raspberry Pi Model 3B, the ISR runs on a high priority which if it has a long runtime, it would affect the performance of other parts of the code. Another example would be the calculation for heart rate and SPO2 in the Sensor.cpp/h file, the calculation is done by passing in an infrared value, and the infrared value is then compared with a buffer of previous values to determine if it is a local maxima peak or a local minima trough. The values of infrared and red intensity values at those points then contribute to AC/DC component of the SPO2 calculation, or the period between peaks is used to calculate the heart rate. Even though the function is called periodically inside a thread, the latency is tested as it is one of the longer functions.

When considering the context, having a latency of less than 50ms would be more than sufficient as the system is made for quick response to bodily conditions where 50ms is a short enough period for a person to respond to a change in someone else's bodily function.  

The test is done by using ```chrono``` and ```fstream``` to log values into a csv file and then data is plotted to a histogram to show distribution of data in ```matplotlib``` using Python. 

![image](https://github.com/2468513H/VigiSense/assets/77401199/82d36c4e-5f26-4d93-9f88-da21260e2bd6)

The diagram above shows the time taken for ISR to run. It shows a bimodal distribution with local means at approximately 1.79ms and 2.35ms, which is well below the threshold.

![image](https://github.com/2468513H/VigiSense/assets/77401199/a8d71751-7150-419b-8e09-17028af5620c)


