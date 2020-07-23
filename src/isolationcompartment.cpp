/****************
 * COVID-19ABMGuelphS20
 * 23/07/20
 * ver 0.03
 * 
 * This is the class file for the isolation compartment class
 ***************/


#include "isolationcompartment.hh"
#include <iostream>

// Constructor
IsolationCompartment::IsolationCompartment() {
    //Nothing to construct...
}

vector<Agent *> IsolationCompartment::isolatedAgents() {
    return isolated;
}

Agent *IsolationCompartment::ReleaseRecoveredAgents(int index) {
    if(index < 0 || index >= (int)isolated.size()) return NULL;
    Agent *toBeReleased = isolated.at(index);
    isolated.erase(isolated.begin() + index);
    return toBeReleased;
}

void IsolationCompartment::AddMildlyInfectedAgents(Agent *toIsolate) {
    if(toIsolate == NULL) return;
    isolated.push_back(toIsolate);
}

void IsolationCompartment::SimulateIsoTimeStep (double timeStep) {
    for (int i = 0; i < (int)isolated.size(); i++) {
        string sirResponse  = isolated[i]->SIRTimeStep(timeStep);
        if (sirResponse == "HOSPITALAGENT") {
            Agent *recoveredAgent = isolated.at(i);
            isolated.erase(isolated.begin() + i);
            newlyHospitalized.push_back(recoveredAgent);
        } else if (sirResponse == "RECOVERAGENT") {
            Agent *recoveredAgent = isolated.at(i);
            isolated.erase(isolated.begin() + i);
            newlyRecovered.push_back(recoveredAgent);
        }
    }
}