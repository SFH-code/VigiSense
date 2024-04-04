#pragma once
#include "DiagnosisInterface.h"
#include "Sensor.h"
#include <thread>

class SPO2Tracker:public diagnosisInterface {
    public:
        SPO2Tracker(sensor *s);
        ~SPO2Tracker();
        void start();
        void stop();
        void ping();
        int getVal();
        void tracker();
    protected:
        sensor* _s; 
        bool threadRunning = false;
        void pingThread();
        // define symptom table here
		std::vector<symptomRange> symptomRanges {
			{0,88,"Critically Low Oxygen concentration"},
			{88,92,"Concerningly Low Oxygen Concentration"},
			{92,100,"Healthy Oxygen Concentration"}};

};