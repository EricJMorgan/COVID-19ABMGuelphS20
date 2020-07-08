/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the simulation class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Agent;
class Location;
//Declare simulation class
class Simulation {
    private:
    Agent** simAgents;
    Location* guelphMap; //map

    // user inputs
    int timeStep;
    int incubationPeriod;
    int socialDistancingSeverity;
    bool socialDistancing;
    int timeQuarantined;
    int initiallyInfected;
    bool fluSeason;
    int agentCount;

    void addNewAgent(string personInfo, int amountToAdd);


    public:
    Simulation();
    ~Simulation();//Destructor
    void runSim();
    void simulateTimeStep();
    void updateOutput();
    void removeAgentsResolved();
    void updateSIRGraphic();
    void setUpAgents(string fileName);
    Agent getAgentAt(int index);
    
};


#endif