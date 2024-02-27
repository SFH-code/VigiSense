#include <vector>
#include <list>

struct symptomRange{
    float min;
    float max;
    string symptom;
}

class sensor{
    private:
    virtual float input;
    virtual float processInput();

    public:
    virtual std::vector<symptomRange> symptomRanges;
    virtual float critHigh;
    virtual float critLow;
    virtual string determineSymptom(float baseline);
    virtual void critCheck(float baseline);
}

class oxyCon: public sensor{
    float input;
    float processInput(){
        //update to take when we have sensor input
        input = 0;
    }
    critHigh = 120;
    critLow = 88;
    static std::vector<symptomRange> symptomRanges {{0,88,"Critically Low Oxygen concentration"},{88,92,"Concerningly Low Oxygen Concentration"},{92,100,"Healthy Oxygen Concentration"}};
    string determineSymptom(float baseline){
        float percent = input/baseline * 100;
        for (auto it = symptomRanges.begin(); it 1=symptomRanges.end(); ++it){
            if (percent>*it.min && percent<*it.max){
                return *it.symptom;
            }
        }    
        return "undefined range";
    }
    void critCheck(float baseline){
        float percent = input/baseline * 100;
        if(critLow> percent || critHigh< percent){

        }
    }
}

void diagnosis(tuple symptoms){
    switch(symptoms){
        case NULL: ;
    }
} 