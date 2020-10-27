/****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
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

void IsolationCompartment::SimulateIsoTimeStep (double timeStep, short agentRecoveryTime[18], double agentNeedsHospital[18]) {
    //loops through the isolated agent list
    Agent* currAgent;
    int agentAgeGroup;
    for (int i = 0; i < (int)isolated.size(); i++) {
        currAgent =  isolated[i];
        agentAgeGroup = currAgent->getAgentAgeGroup();
        //check if the agent is in need of the hospital or good too leave isolation
        if (agentNeedsHospital[agentAgeGroup] >= ((double) rand() / (RAND_MAX))) {
            currAgent->timeInfected++;
            isolated.erase(isolated.begin() + i);
            newlyHospitalized.push_back(currAgent);
        } else if (currAgent->timeInfected > agentRecoveryTime[agentAgeGroup]) {
            currAgent->timeInfected = 0;
            currAgent->recoverAgent();
            isolated.erase(isolated.begin() + i);
            newlyRecovered.push_back(currAgent);
        }
    }
}