#pragma once
#include <string>
#include <vector>

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

        static std::string determineSymptom(std::vector<symptomRange> symptomRanges, int val){
        	for (int i = 0; i < symptomRanges.size(); ++i){
                if (val>symptomRanges[i].min && val<symptomRanges[i].max){
                    return symptomRanges[i].symptom;
                }
            }    
            if (val < symptomRanges[0].min) {
                return "critLow";
            } else if (val > symptomRanges[symptomRanges.size() -1].max)
            {
                return "critHigh";
            } else {
                return "Out of range";
            }
        };


    protected:
        std::vector<symptomRange> symptomRanges;
};