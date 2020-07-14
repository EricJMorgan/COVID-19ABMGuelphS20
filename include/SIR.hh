/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the SIR class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include "agent.hh"

using namespace std;

enum SIRSeverity { SUSCEPTIBLE, INFECTED, ISOLATED, HOSPITALIZED, ICU, RECOVERED, DECEASED };

//Declare simulation class
class SIR {
    private:
    SIRSeverity currentSeverity;
    int incubationPeriod;
    int infectDuration;
    bool fatalCase;
    bool showsSymptoms;

    public:
    SIR();
    void QuarantineAgent();
    void AgentSymptoms();
    void HospitalAgent();
    void PlaceAgentInICU();
    void RecoverAgent();
    void AgentDeceased();
    void AgentInfected(AgentInfo info);
    void SIRTimeStep();
    void DecideFatalCase(double infectedNumb, double infectedChance);
};


#endif