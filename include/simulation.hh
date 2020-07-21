/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.04
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

enum DayOfWeek{MON, TUE, WED, THU, FRI, SAT, SUN};

class Agent;
class Location;
//Declare simulation class
class Simulation {
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

    private:
    Agent** simAgents;
    Location** guelphMap; //map

    // user inputs
    int timeStep;
    int currTime;
    DayOfWeek currDay;
    int incubationPeriod;
    int socialDistancingSeverity;
    bool socialDistancing;
    int timeQuarantined;
    int initiallyInfected;
    bool fluSeason;
    int agentCount;
    int population;

    /**
     * addNewAgent
     * 
     * This function takes in the agents info and the amount of said
     * agent and adds that amount to the array of people
     * 
     * @param personInfo, this is a string in the fomat GENDER N-N where N is the age range
     * @param amountToAdd, this is a int of how many of that agent there are for the area i.e there are 3875 males 0-4 in guelph
     */
    void addNewAgent(string personInfo, int amountToAdd);

    /**
     * setUpAgents
     * 
     * This function takes in the file name of the demographic file
     * of an area in the format typeOfData,DataInfo,AmountOfPeople
     * 
     * @param filename, must be in the above format
     */
    void setUpAgents(string filename);

    /**
     * stepTime
     * 
     * This function is a helper function to push the time and day
     * forward on every iteration of the timesetp
     */
    void stepTime();

    /**
     * getNextDay
     * 
     * This is a helper function to increment the currDay counter
     * int the program
     */
    DayOfWeek getNextDay(DayOfWeek currDay);
};


#endif