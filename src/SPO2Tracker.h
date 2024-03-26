#include "DiagnosisInterface.h"
#include <thread>

class SPO2Tracker:public diagnosisInterface {
    public:
        SPO2Tracker(sensor *s);
        ~SPO2Tracker();
        void start();
        void stop();
        void alert();
        int getVal();
        void tracker();
    protected:
        sensor* _s; 
        bool threadRunning = false;
        // define symptom table here

};