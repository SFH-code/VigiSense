Unit tests can be found on the [Unit-Tests](https://github.com/2468513H/VigiSense/tree/Unit-Tests) branch.

To add a new unit test, you would need to figure out what function to test and which file the function resides in. This backhanded way uses derived and related classes to test is because classes rely on sensor values that come in intervals based on the interrupts. This means that functions are encapsulated in a process that separates the conversion of raw infrared and red intensity values to oxygen level and heart rate values. 

## An example implementation:

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
