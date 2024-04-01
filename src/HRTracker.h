#include "DiagnosisInterface.h"
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

};