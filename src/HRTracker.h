#pragma once
#include "DiagnosisInterface.h"
#include "Sensor.h"
#include <thread>

class HRTracker:public diagnosisInterface {
    public:
        HRTracker(testParent *s);
        ~HRTracker();
        void start();
        void stop();
        void ping();
        int getVal();

	      testParent* _s;

        int lastVal=0;
    protected:
        sensor* _s; 
        bool threadRunning = false;
        void pingThread();
        // define symptom table here
		std::vector<symptomRange> symptomRanges {
			{40,60,"Bradycardia"},
			{60,100,"Normal resting heart rate"},
			{100,120,"Tachyacardia"}};


};
