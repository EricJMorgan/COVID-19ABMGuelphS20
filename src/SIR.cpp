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

// can all be changed to user inputs
// 45% asymptomatic if not srs (check)
// 25% icu death rate
// 6% need hospital
// case peak around 10 days
// around 14 days to death (check)
// around 26 days to srs recovery via icu

void SIR::SIRTimeStep() {
    
}

void SIR::DecideFatalCase(double infectedNumb, double infectedChance) {
    if (infectedNumb <  infectedChance) {
        fatalCase = true;
        infectDuration = 14; // make user input
        showsSymptoms = true;
    } else {
        double randomNumber = (double) rand()/RAND_MAX;
        if (randomNumber < 0.45) {
            showsSymptoms = false;
            infectDuration = 14;
            fatalCase = false;
        }
        
    }
}

void SIR::AgentInfected(AgentInfo info) {
    currentSeverity = INFECTED;
    incubationPeriod = std::rand()%7 + std::rand()%7;

    double randomNumber = (double) rand()/RAND_MAX;

    // based on worldometer death rates
    if(MALE0TO4 == info || MALE5TO9 == info || FEMALE0TO4 == info || FEMALE5TO9 == info) {
        DecideFatalCase(randomNumber, 0.0);
    } else if (MALE10TO14 == info || MALE15TO19 == info || FEMALE10TO14 == info || FEMALE15TO19 == info) {
        DecideFatalCase(randomNumber, 0.002);
    } else if (MALE20TO24 == info || MALE25TO29 == info || FEMALE20TO24 == info || FEMALE25TO29 == info) {
        DecideFatalCase(randomNumber, 0.002);
    } else if (MALE30TO34 == info || MALE35TO39 == info || FEMALE30TO34 == info || FEMALE35TO39 == info) {
        DecideFatalCase(randomNumber, 0.002);
    } else if (MALE40TO44 == info || MALE45TO49 == info || FEMALE40TO44 == info || FEMALE45TO49 == info) {
        DecideFatalCase(randomNumber, 0.004);
    } else if (MALE50TO54 == info || MALE55TO59 == info || FEMALE50TO54 == info || FEMALE55TO59 == info) {
        DecideFatalCase(randomNumber, 0.013);
    } else if (MALE60TO64 == info || MALE65TO69 == info || FEMALE60TO64 == info || FEMALE65TO69 == info) {
        DecideFatalCase(randomNumber, 0.036);
    } else if (MALE70TO74 == info || MALE75TO79 == info || FEMALE70TO74 == info || FEMALE75TO79 == info) {
        DecideFatalCase(randomNumber, 0.08);
    } else {
        DecideFatalCase(randomNumber, 0.148);
    }
}

void SIR::AgentSymptoms() {
    
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
    currentSeverity = RECOVERED;
} 

void SIR::AgentDeceased() {
    currentSeverity = DECEASED;
} 

