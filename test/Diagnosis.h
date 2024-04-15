#include <iostream>
#include <vector>
#include <list>
#include <string>
#include "MAX30102.h"
#include "Sensor.h"

//This is going to be an abstract class that will be inherited by the diagnosis classes for each biosignal

class diagnosis {
public:
    // Public member functions and variables
    
    //Struct for the individual diagnosis range
    typedef struct DiagnosisRange{
    float min;
    float max;
    std::string diagnosis;
    } Diagnosis_Range;

    Diagnosis_Range stdDiagnosis; // Creates a standard symptom range for the diagnosis
    Diagnosis_Range CustomDiagnosis; //Creates a custom symptom range for the diagnosis

    //Struct for the diagnoses table
    typedef struct DiagnosesTable {
        std::vector<DiagnosisRange> Diagnoses; //Contains all the possible diagnoses for the biosignal
    } _Diagnoses;

    _Diagnoses stdDiagnoses; //Creates a standard diagnoses table for the biosignal
    _Diagnoses CustomDiagnoses; //Creates a custom diagnoses table for the biosignal
    
    //Function to set customized symptom ranges for the biosignal
    void SetdiagnosisRanges(float minimum, float maximum, std::string diagnosis);//Sets the symptom ranges for the biosignal

    //Function to determine the symptom based on the biosignal value
    std::string determineDiagnosis() { return ""; } 

    void critCheck() {} //Checks if the biosignal value crosses the critical value and initiates an immediate alert

    void findMinMax() {} //Finds the minimum and maximum values in the diagnoses table

    float CriticalLow; //Variable to store the critical low value
    float CriticalHigh; //Variable to store the critical high value

    //function to display the diagnosis
    virtual void displayDiagnosis(); //Pure virtual function to display the diagnosis

    //function for critical value crossing
    virtual void critRangeAlert(); //Pure virtual function for critical value crossing alert
private:
    // Private member functions and variables

};