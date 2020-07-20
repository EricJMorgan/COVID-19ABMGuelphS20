 /****************
 * COVID-19ABMGuelphS20
 * 20/07/20
 * ver 0.03
 * 
 * This is the header file for the isolation compartment class
 ***************/


#ifndef ISOLATIONCOMPARTMENT_H_
#define ISOLATIONCOMPARTMENT_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

//Forward declarations
class Agent;

//Declare simulation class
class IsolationCompartment {
    private:
    std::vector<Agent *> isolated;

    public:
    /**
     * IsolationCompartment
     * 
     * This is the default constructor for the isolation object
     */
    IsolationCompartment();

    /**
     * isolatedAgents
     * 
     * This function gets the array of agents to be isolated
     * 
     * @return the array of agents to be isolated from the simulation
     */
    std::vector<Agent *> isolatedAgents();

    /**
     * ReleaseRecoveredAgents
     * 
     * This function releases agents when they have recovered
     */
    Agent *ReleaseRecoveredAgents(int index);

    /**
     * AddMildlyInfectedAgents
     * 
     * This function quarantines/isolates agents that have mild symptoms
     */
    void AddMildlyInfectedAgents(Agent *toIsolate);
};

#endif
