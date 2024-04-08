#pragma once
#include "DiagnosisInterface.h"
#include "Sensor.h"
#include <thread>

class HRTracker:public diagnosisInterface {
    public:
        HRTracker(sensor *s);
        ~HRTracker();
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
			{0,60,"Bradycardia","HRB"},
			{60,100,"Normal resting heart rate","HRN"},
			{100,200,"Tachyacardia","HRT"}};

};