/****************
 * COVID-19ABMGuelphS20
 * 30/09/20
 * ver 1.01
 * 
 * This is the class file for the isolation compartment class. This is used
 * for when an agent has visable symptoms and isolates. 
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

    //releases agent at a given index
    Agent *toBeReleased = isolated.at(index);
    isolated.erase(isolated.begin() + index);
    return toBeReleased;
}

void IsolationCompartment::AddMildlyInfectedAgents(Agent *toIsolate) {
    if(toIsolate == NULL) return;
    isolated.push_back(toIsolate);
}

void IsolationCompartment::SimulateIsoTimeStep (double timeStep) {
    //loops through the isolated agent list
    for (int i = 0; i < (int)isolated.size(); i++) {
        string sirResponse  = isolated[i]->SIRTimeStep(timeStep);

        //check if the agent is in need of the hospital or good too leave isolation
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