/****************
 * COVID-19ABMGuelphS20
 * 15/07/20
 * ver 0.03
 * 
 * This is the header file for the simulation class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include <vector>
#include "SIRtotals.hh"
#include "transportation.hh"

using namespace std;

class Agent;
class Location;
//Declare simulation class
class Simulation {
    private:
    Agent** simAgents;
    Location** guelphMap; //map

    // user inputs
    int timeStep;
    int incubationPeriod;
    int socialDistancingSeverity;
    bool socialDistancing;
    int timeQuarantined;
    int initiallyInfected;
    bool fluSeason;
    int agentCount;
    int population;

    void addNewAgent(string personInfo, int amountToAdd);
    void setUpAgents(string filename);


    public:
    Simulation(string fileName);
    ~Simulation();//Destructor
    void runSim();
    void simulateTimeStep();
    void updateOutput();
    void removeAgentsResolved();
    void updateSIRGraphic();
    Agent getAgentAt(int index);
    SIRtotals totalSimSIRStats;
    int getPopulation();
    Transportation *locationInfo = NULL;
};


#endif