#include "HRTracker.h"
#include "DevicePublisher.cpp"

HRTracker::HRTracker(sensor *s) {
    HRTracker::_s = s;
}

HRTracker::~HRTracker() {
    stop();
}

void HRTracker::start() {
    // start threads
    threadRunning = true;
    std::thread t1(&HRTracker::tracker, this);
    t1.detach();
}

// set false for thread and terminates it
void HRTracker::stop() {
    threadRunning = false;
}


void HRTracker::ping() {
	std::thread t2(&HRTracker::pingThread, this);
	t2.detach();
}

// thread for pinging SPO2 critical values, 
void HRTracker::pingThread() {
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
    alertMessage.message();
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

void HRTracker::tracker(){
    // thread that checks using determineSymptom() and calls alert if conditions are met
    // use threadRunning to stop the thread
    std::cout<<"Started HR tracker"<<std::endl;
    while (threadRunning) {
        int val = getVal();
        std::cout<<"HR value: "<< val << " ";
        std::string symptom = determineSymptom(symptomRanges, val);
        std::cout<<symptom<<std::endl;
        // if (false) {
        //     // define out of range behaviour (check if crit low)
        //     // alert();
        // }
    }
}

int HRTracker::getVal() {
    // start threads
    return _s->getHR();
}