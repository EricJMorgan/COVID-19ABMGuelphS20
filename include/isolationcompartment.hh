 /****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the isolation compartment class
 ***************/


#ifndef ISOLATIONCOMPARTMENT_H_
#define ISOLATIONCOMPARTMENT_H_

#include <string>
#include <iostream>

using namespace std;

//Forward declarations
class Agent;

//Declare simulation class
class IsolationCompartment {
    private:
    Agent* agents;

    public:
    IsolationCompartment();
    void ReleaseRecoveredAgents();
    void AddMildlyInfectedAgents();
};

#endif
