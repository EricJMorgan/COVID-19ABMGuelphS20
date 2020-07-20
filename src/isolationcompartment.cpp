/****************
 * COVID-19ABMGuelphS20
 * 20/07/20
 * ver 0.02
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

void IsolationCompartment::ReleaseRecoveredAgents(int index) {
    if(index < 0 || index >= (int)isolated.size());
    isolated.erase(isolated.begin(), isolated.begin() + index);
    //Should this function return the agent to be removed from the isolated vector?
}

void IsolationCompartment::AddMildlyInfectedAgents(Agent *toIsolate) {
    if(toIsolate == NULL) return;
    isolated.push_back(toIsolate);
}