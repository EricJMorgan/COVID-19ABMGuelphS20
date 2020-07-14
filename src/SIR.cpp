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

// check all references
// can all be changed to user inputs
// 45% asymptomatic if not srs (check)
// 25% icu death rate
// approx 20% need hospital
// 6% need ICU
// case peak around 10 days
// around 14 days to death (check)
// around 26 days to srs recovery via icu
// icu 1 to 3 days after hospitilization
// icu recovery 14 days
// icu death after 5 days
// days til icu reocvery 14 days

void SIR::SIRTimeStep(double timeStep) {
    // incubating stage
    if (isIncubating) {
        incubationPeriod -= timeStep;

        if (incubationPeriod == 0 && showsSymptoms) {
            QuarantineAgent();
        }
        return;
    }
    
    // move agents between stages, check stages in order
    if (needHospital && timeTilHospital > 0) {
        timeTilHospital -= timeStep;
        if (timeTilHospital == 0) {
            HospitalAgent();
        }
    } else if (needIcu && timeTilICU > 0) {
        timeTilICU -= timeStep;
        if (timeTilICU == 0) {
            PlaceAgentInICU();
        }
    } else if (fatalCase && timeTilDeath > 0) {
        timeTilDeath -= timeStep;
        if (timeTilDeath == 0) {
            AgentDeceased();
        }
    } else {
        timeTilRecovery -= timeStep;
        if (timeTilRecovery == 0) {
            RecoverAgent();
        }
    }
}

void SIR::DecideSIRCase(double infectedNumb, double infectedChance) {
    // decide if the case is fatal
    if (infectedNumb <  infectedChance) {
        fatalCase = true;
        timeTilHospital = 7; // (make user input)
        needIcu = true;
        needHospital = true;
        timeTilICU = 3; // Days from general hospital ward to ICU (user input)
        timeTilDeath = 5; // Days from ICU to death (make user input)
        showsSymptoms = true;
      // if the case is not fatal decide path to recovery
    } else {
        double hospitalAsymptomRisk = (double) rand()/RAND_MAX;
        fatalCase = false;
        // case is asymptomatic
        if (hospitalAsymptomRisk < 0.45) { // asymptomatic probability if non fatal (user input)
            showsSymptoms = false;
            needHospital = false;
            needIcu = false;
            timeTilRecovery = 14; // asymptomatic recovery (user input)
        } else if (0.45 <= hospitalAsymptomRisk <= 0.65) { //hospitilization chance per case (user input)
            needHospital = true;
            showsSymptoms = true;
            timeTilHospital = 7; //time needed to get srs enough for hospital (make user input)
            double icuNeeded = (double) rand()/RAND_MAX;
            if (icuNeeded < 0.06) { //chance of u needing icu if hospitalized (look this up)
                timeTilICU = 3; //time needed from hospital to ICU (make user input)
                timeTilRecovery = 26; //recovery from ICU on average (make user input)
                needIcu = true;
            } else {
                needIcu = false;
                timeTilRecovery = 12; //Time til Hospital recovery (make user input)
            }
        } else {
            showsSymptoms = true;
            needHospital = false;
            needIcu = false;
            timeTilRecovery = 14; //Time til non ICU and non Hospital recovery (make user input)
        }
    }
}

// Infect the agent and decide their path through the SIR model
void SIR::AgentInfected(AgentInfo info) {
    currentSeverity = INFECTED;
    isIncubating = true;
    incubationPeriod = std::rand()%7 + std::rand()%7;

    double randomNumber = (double) rand()/RAND_MAX;

    // based on worldometer death rates
    if(MALE0TO4 == info || MALE5TO9 == info || FEMALE0TO4 == info || FEMALE5TO9 == info) {
        DecideSIRCase(randomNumber, 0.0);
    } else if (MALE10TO14 == info || MALE15TO19 == info || FEMALE10TO14 == info || FEMALE15TO19 == info) {
        DecideSIRCase(randomNumber, 0.002);
    } else if (MALE20TO24 == info || MALE25TO29 == info || FEMALE20TO24 == info || FEMALE25TO29 == info) {
        DecideSIRCase(randomNumber, 0.002);
    } else if (MALE30TO34 == info || MALE35TO39 == info || FEMALE30TO34 == info || FEMALE35TO39 == info) {
        DecideSIRCase(randomNumber, 0.002);
    } else if (MALE40TO44 == info || MALE45TO49 == info || FEMALE40TO44 == info || FEMALE45TO49 == info) {
        DecideSIRCase(randomNumber, 0.004);
    } else if (MALE50TO54 == info || MALE55TO59 == info || FEMALE50TO54 == info || FEMALE55TO59 == info) {
        DecideSIRCase(randomNumber, 0.013);
    } else if (MALE60TO64 == info || MALE65TO69 == info || FEMALE60TO64 == info || FEMALE65TO69 == info) {
        DecideSIRCase(randomNumber, 0.036);
    } else if (MALE70TO74 == info || MALE75TO79 == info || FEMALE70TO74 == info || FEMALE75TO79 == info) {
        DecideSIRCase(randomNumber, 0.08);
    } else {
        DecideSIRCase(randomNumber, 0.148);
    }
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
SIRSeverity SIR::DetermineSeverity() {
    return currentSeverity;
}
