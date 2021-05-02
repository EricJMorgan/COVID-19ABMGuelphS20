 /****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
 * 
 * This is the header file for the isolation compartment class. This is used
 * for when an agent has visable symptoms and isolates. 
 ***************/


#ifndef ISOLATIONCOMPARTMENT_H_
#define ISOLATIONCOMPARTMENT_H_

#include <string>
#include <iostream>
#include <vector>
#include "agent.hh"

using namespace std;

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
     * 
     * @param the index of the agent to be released
     * @return the pointer to the agent to be released
     */
    Agent *ReleaseRecoveredAgents(int index);

    /**
     * AddMildlyInfectedAgents
     * 
     * This function quarantines/isolates agents that have mild symptoms
     * 
     * @param the pointer to the agent to isolate
     */
    void AddMildlyInfectedAgents(Agent *toIsolate);

    /**
     * SimulateIsoTimeStep
     * 
     * This function simulates the time step for the isolation compartment
     * 
     * @param the size of the timeStep
     */
    void SimulateIsoTimeStep (double timeStep, int agentRecoveryTime[18], double agentNeedsHospital[18]);

    // returns to be read and cleared
    std::vector<Agent *> newlyRecovered;
    std::vector<Agent *> newlyHospitalized;
};

#endif
