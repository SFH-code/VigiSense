#include <vector>
#include <list>
#include <string>
#include "MAX30102.h"
#include "Sensor.h"
#include "Diagnosis.h"


//Add implementation of the functions declared in the header file

//Constructor which initiates critical value check
diagnosis::diagnosis() {
    critCheck();
};

//Considers the standard critical values for safety
void diagnosis::critCheck() {
        // Virtual variables for critical values
        float CriticalLow;
        float CriticalHigh;
        findMinMax(); // Find the minimum and maximum values in the diagnoses table
        // Check if the biosignal value crosses the critical value and initiate an immediate alert
        //Need to update this to take the actual sensor output in its final form
        if (biosignalValue > CriticalHigh || biosignalValue < CriticalLow) {
            // Perform alert action
        }
    }

//Considers the standard critical values for safety
void diagnosis::findMinMax() {
    if (stdDiagnoses.Diagnoses.empty()) { //check of the vector "stdDiagnoses.Diagnoses" is empty
        // Handle empty vector case
        std::cout << "Standard diagnosis table is empty" << std::endl;
    }

    CriticalLow = stdDiagnoses.Diagnoses[0].min;
    CriticalHigh = stdDiagnoses.Diagnoses[0].max;

    for (size_t i = 1; i < stdDiagnoses.Diagnoses.size(); ++i) {
        if (stdDiagnoses.Diagnoses[i].min < CriticalLow) {
            CriticalLow = stdDiagnoses.Diagnoses[i].min;
        }
        if (stdDiagnoses.Diagnoses[i].max > CriticalHigh) {
            CriticalHigh = stdDiagnoses.Diagnoses[i].max;
        }
    }
}

//Determines the diagnosis based on the biosignal value
std::string diagnosis::determineDiagnosis() {
//Need to update this to take the actual sensor output in its final form
    for (auto it = stdDiagnoses.Diagnoses.begin(); it != stdDiagnoses.Diagnoses.end(); ++it) {
        if (biosignalValue > it->min && biosignalValue < it->max) {
            return it->diagnosis;
        }
    }
    return "undefined range";
}

//sets the custom diagnosis ranges for the biosignal one diagnosis at a time
void diagnosis::SetdiagnosisRanges(float minimum, float maximum, std::string diagnosis) {
    CustomDiagnosis.min = minimum;
    CustomDiagnosis.max = maximum;
    CustomDiagnosis.diagnosis = diagnosis;

    CustomDiagnoses.Diagnoses.push_back(CustomDiagnosis);
} // Sets the symptom ranges for the biosignal
