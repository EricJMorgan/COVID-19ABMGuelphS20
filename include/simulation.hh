/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the header file for the simulation class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>

using namespace std;

class Agent;
class Location;
//Declare simulation class
class Simulation {
    private:
    Agent* simAgents;
    Location* guelphMap;

    // user inputs
    int timeStep;
    int incubationPeriod;
    int socialDistancingSeverity;
    bool socialDistaning;
    int timeQuarantined;
    //TYPE map;
    int initiallyInfected;
    bool fluSeason;

    public:
    Simulation();
    void runSim();
    void simulateTimeStep();
    void updateOutput();
    void removeAgentsResolved();
    void updateSIRGraphic();
};


#endif