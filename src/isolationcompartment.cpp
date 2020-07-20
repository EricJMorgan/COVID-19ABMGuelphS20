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

Agent *IsolationCompartment::ReleaseRecoveredAgents(int index) {
    if(index < 0 || index >= (int)isolated.size()) return NULL;
    Agent *toBeReleased = isolated.at(index);
    isolated.erase(isolated.begin(), isolated.begin() + index);
    return toBeReleased;
}

void IsolationCompartment::AddMildlyInfectedAgents(Agent *toIsolate) {
    if(toIsolate == NULL) return;
    isolated.push_back(toIsolate);
}