#include "SPO2Tracker.h"
#include "DevicePublisher.cpp"

SPO2Tracker::SPO2Tracker(sensor *s) {
    SPO2Tracker::_s = s;
}

SPO2Tracker::~SPO2Tracker() {
    stop();
}

void SPO2Tracker::start() {
    // start threads
    threadRunning = true;
    std::thread t1(&SPO2Tracker::tracker, this);
    t1.detach();
}

// set false for thread and terminates it
void SPO2Tracker::stop() {
    threadRunning = false;
}


void SPO2Tracker::ping() {
	std::thread t2(&SPO2Tracker::pingThread, this);
	t2.detach();
}

// thread for pinging SPO2 critical values, 
void SPO2Tracker::pingThread() {
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

void SPO2Tracker::tracker(){
    // thread that checks using determineSymptom() and calls alert if conditions are met
    // use threadRunning to stop the thread
    int count= 0;
    while (threadRunning) {
        int val = getVal();
        if(val!=this->lastVal||count>5){
            std::cout<<"SPO2 value: "<< val << " ";
            std::string symptom = determineSymptom(symptomRanges, val);
            std::cout<<symptom<<std::endl;
            this->lastVal = val;
            count = 0;
        }
        count++;
        // if (false) {
        //     // define out of range behaviour (check if crit low)
        //     // alert();
        // }
    }
}

int SPO2Tracker::getVal() {
    // start threads
    return _s->getSpO2();
}