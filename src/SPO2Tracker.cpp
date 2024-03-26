#include "SPO2Tracker.h"

SPO2Tracker::SPO2Tracker(sensor *s) {
    SPO2Tracker::_s = s;
}

void SPO2Tracker::start() {
    // start threads
    threadRunning = true;
    std::thread t1(&SPO2Tracker::tracker, this);
    t1.detach();
}

void SPO2Tracker::stop() {
    threadRunning = false;
}


void SPO2Tracker::alert() {
    // start threads for FastDDS
}

void SPO2Tracker::tracker(){
    // thread that checks using determineSymptom() and calls alert if conditions are met
    // use threadRunning to stop the thread
    while (threadRunning) {
        std::string symptom = determineSymptom();
        if (false) {
            // define out of range behaviour (check if crit low)
            alert();
        }
    }
}

int SPO2Tracker::getVal() {
    // start threads
    return _s->getSpO2();
}