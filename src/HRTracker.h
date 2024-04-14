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
        void tracker();
	testParent* _s;
	
	// define symptom table here
		std::vector<symptomRange> symptomRanges {
			{40,60,"Bradycardia"},
			{60,100,"Normal resting heart rate"},
			{100,200,"Tachyacardia"}};
			
    protected:
         
        bool threadRunning = false;
        void pingThread();
        

};
