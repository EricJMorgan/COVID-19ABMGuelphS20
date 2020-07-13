/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the SIR class
 ***************/


#ifndef SIR_H_
#define SIR_H_

#include <string>
#include <iostream>

using namespace std;

enum SIRSeverity { SUSCEPTIBLE, INFECTED, ICU, RECOVERED, DECEASED };

//Declare SIR class
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
<<<<<<< HEAD
    SIRSeverity DetermineSeverity();
    void DetermineRecoveryTime();
=======
    void DetermineSeverity();
    void DetermineRecoveryTime();
    SIRSeverity getSeverity();

>>>>>>> dcf37f5c77f67f686059c391c305952dd35f788c
};


#endif