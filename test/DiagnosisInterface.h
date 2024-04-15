#pragma once
#include <string>
#include <vector>

//Structure made to contain a specific symptom diagnosis and the range of values it is associated with
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

        int lastVal;

        /*Function that will be utilised by multiple inheriting classees to compare a value to group of symptom ranges
        when it is found to be within a suitable range the associated symptom will be returned otherwise it will be considered
        a critcial diagnosis and return either a critical high or low*/
        static std::string determineSymptom(std::vector<symptomRange> symptomRanges, int val){
            //first check if condition is critical for immediate response
            if (val < symptomRanges[0].min) {
                return "critLow";
            } else if (val >= symptomRanges[symptomRanges.size() -1].max)
            {
                return "critHigh";
            } else {
                
            }
             //search through the ranges to see if it is within any specified range
            for (int i = 0; i < symptomRanges.size(); ++i){
                if (val>=symptomRanges[i].min && val<symptomRanges[i].max){
                    return symptomRanges[i].symptom;
                }
            }
            //Should be unreachable but indicates an error in the systems
            return "Out of range";
        };


    protected:
        std::vector<symptomRange> symptomRanges;
};
