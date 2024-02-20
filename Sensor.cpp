#include <map>
#include <list>

class sensor{
    private:
    virtual float input;
    virtual float processInput();

    public:
    virtual std::map<map<float,float>, string> symptomRanges;
    virtual float critHigh;
    virtual float critLow;
    virtual string determineSymptom(float baseline);
    virtual void critCheck(float baseline);
}

void diagnosis(tuple symptoms){
    switch(symptoms){
        case NULL: ;
    }
} 