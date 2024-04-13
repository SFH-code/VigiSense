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
        int lastVal = 0;
    protected:
        sensor* _s; 
        bool threadRunning = false;
        void pingThread();
        // define symptom table here
		std::vector<symptomRange> symptomRanges {
			{88,92,"Hypoxemia"},
            {93,94,"Concerning Oxygen Concentration"},
			{95,100,"Healthy Oxygen Concentration"}};

};