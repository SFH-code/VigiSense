#include "Sensor.h"
#include <string>
#include "DevicePublisher.cpp"

struct symptomRange{
    float min;
    float max;
    std::string symptom;
};

class diagnosisInterface {
    public:
        virtual void start() = 0;
        virtual void stop() = 0;
        virtual void ping() = 0;
        virtual int getVal() = 0;

        std::string determineSymptom(){
        	int val = this->getVal();
        	for (int i = 0; i < symptomRanges.size(); ++i){
                if (val>symptomRanges[i].min && val<symptomRanges[i].max){
                    return symptomRanges[i].symptom;
                }
            }    
            return NULL;
        }


    protected:
        std::vector<symptomRange> symptomRanges;
        int critHigh;
        int critLow;
};