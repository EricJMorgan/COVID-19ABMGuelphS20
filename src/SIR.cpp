/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the class file for the SIR class
 ***************/


#include "SIR.hh"
#include <iostream>

// Constructor
SIR::SIR() {
    currentSeverity = SUSCEPTIBLE;
}

// 45% asymptomatic if not srs
// 25% icu death rate
// 6% need hospital

void SIR::AgentInfected() {
    currentSeverity = INFECTED;
    incubationPeriod = std::rand()%7 + std::rand()%7;

    // if()
}

void SIR::AgentSymptoms() {
    // if (infectDuration >= ) {
    //     /* code */
    // }
    
}



void SIR::HospitalAgent() {
    currentSeverity = HOSPITALIZED;
}

void SIR::QuarantineAgent() {
    currentSeverity = ISOLATED;
}

void SIR::PlaceAgentInICU() {
    currentSeverity = ICU;
}

void SIR::RecoverAgent() {
    fatalRisk = 0;
    currentSeverity = RECOVERED;
} 

void SIR::AgentDeceased() {
    fatalRisk = 100;
    currentSeverity = DECEASED;
} 

