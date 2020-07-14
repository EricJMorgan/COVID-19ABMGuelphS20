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
#include "agent.hh"

using namespace std;

enum SIRSeverity { SUSCEPTIBLE, INFECTED, ISOLATED, HOSPITALIZED, ICU, RECOVERED, DECEASED };

//Declare SIR class
class SIR {
    private:
    SIRSeverity currentSeverity;
    bool fatalCase;
    bool showsSymptoms;
    bool needHospital;
    bool needIcu;
    bool isIncubating;
    double incubationPeriod;
    double timeTilHospital;
    double timeTilICU;
    double timeTilDeath;
    double timeTilRecovery;

    void DecideSIRCase(double infectedNumb, double infectedChance);
    void QuarantineAgent();
    void HospitalAgent();
    void PlaceAgentInICU();
    void RecoverAgent();
    void AgentDeceased();

    public:
    SIR();
    void AgentInfected(AgentInfo info);
    void SIRTimeStep(double timeStep);
    SIRSeverity DetermineSeverity()
};


#endif