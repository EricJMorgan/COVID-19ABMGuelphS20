/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the header file for the SIR class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>

using namespace std;

enum SIRSeverity { SUSCEPTIBLE, INFECTED, ICU, RECOVERED, DECEASED };

//Declare simulation class
class SIR {
    private:
    SIRSeverity currentSeverity;
    int incubationPeriod;
    int infectDuration;
    bool recovered;
    bool quarantineCase;
    bool isolateCase;
    bool hospitalCase;
    bool icuCase;
    int fatalRisk;

    public:
    SIR();
    void QuarantineAgent();
    void AgentSymptoms();
    void HospitalAgent();
    void PlaceAgentInICU();
    void RecoverAgent();
    void AgentDeceased();
    void AgentInfected();
    void DetermineSeverity();
    void DetermineRecoveryTime();

};


#endif