/****************
 * COVID-19ABMGuelphS20
 * 05/08/20
 * ver 1.00
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
#include "agent.hh"
#include "location.hh"
#include "hospital.hh"
#include "isolationcompartment.hh"

using namespace std;

//Declare simulation class
class Simulation {
    public:
    /**
     * Simulation
     * 
     * This is the constructor for the simulation class it takes
     * in a file name of the csv file of the demographic data and creates
     * all the needed data to start the simulation
     * 
     * @param fileName, the file name of the census data
     */
    Simulation(string fileName);

    /**
     * ~Simulation
     * 
     * This is the deconstructor for the simlation class
     */
    ~Simulation();//Destructor

    /**
     * simulateTimeStep
     * 
     * when called this will simulate one time step in the simulation
     * it will do everything for agent movement, infection spread, and time
     * and date.
     */
    void simulateTimeStep();

    /**
     * getAgentAt
     * 
     * This function gets a specific agent from the internal data for 
     * what ever reason. It returns a copy of the agent instead of the original pointer
     * 
     * @param index, the index in the internal array must be in range of 0 <= index < population
     */
    Agent *getAgentAt(int index);

    /**
     * getPopulation
     * 
     * This gets the population of the simulation based on
     * the amount of agents in the simulation
     * 
     * @return the amount of agents in the internal array
     */
    int getPopulation();

    void runSim();

    /**
     * getInfectedCurrent
     * 
     * This get the current number of infected agents
     */
    int getInfectedCurrent();

    /**
     * getInfectedTotal
     * 
     * This get the current number of infected agents
     */
    int getInfectedTotal();

    /**
     * getDeceasedTotal
     * 
     * This get the current number of deceased agents
     */
    int getDeceasedTotal();

    /**
     * getRecoveredTotal
     * 
     * This get the current number of recovered agents
     */
    int getRecoveredTotal();

    /**
     * getHospitalTotal
     * 
     * This get the current number of total agents ever hospitilized
     */
    int getHospitalTotal();

    /**
     * getHospitalCurrent
     * 
     * This get the current number of current hospital agents
     */
    int getHospitalCurrent();

    /**
     * getICUtotal
     * 
     * This get the current number of total ICU agents
     */
    int getICUtotal();

    /**
     * getICUCurrent
     * 
     * This get the current number of current ICU agents
     */
    int getICUCurrent();

    /**
     * setInputs
     * 
     * Takes inputs from front end sends them to the associated classes
     */
    //int getRecoveredTotal(ask joyce for inputs after getting works);
    
    SIRtotals totalSimSIRStats;
    
    Transportation *locationInfo = NULL;

    std::vector<Agent *> recoveredAgents;
    std::vector<Agent *> deceasedAgents;

    private:
    Agent** simAgents;
    Hospital guelphHospital;
    IsolationCompartment isoCompartment;

    // user inputs
    int timeStep;
    int currTime;
    DayOfWeek currDay;
    int incubationPeriod;
    int socialDistancingSeverity;
    bool socialDistancing;
    int timeQuarantined;
    bool fluSeason;
    int agentCount;
    int population;
    double sirTimeStep;

    //outputs for Front End graph
    int infectedCurrent = 100;
    int infectedTotal = 100;
    int deceasedTotal = 50;
    int recoveredTotal = 50;
    int hospitalCurrent;
    int hospitalTotal;
    int icuCurrent;
    int icuTotal;
    int timeElapsed;

    double initiallyInfectedChance;
    int initiallyInfected;


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


//for python binding
extern "C" {
    Simulation* Simulation_new(){ return new Simulation("demographicGuelph.csv"); }
    void simTimeStep(Simulation* sim){ sim->simulateTimeStep(); }
    int infectedCurrent(Simulation* sim){ return sim->getInfectedCurrent(); }
    int infectedTotal(Simulation* sim){ return sim->getInfectedTotal(); }
    int deceasedTotal(Simulation* sim){ return sim->getDeceasedTotal(); }
    int recoveredTotal(Simulation* sim){ return sim->getRecoveredTotal(); }
    int hospitalTotal(Simulation* sim){ return sim->getHospitalTotal(); }
    int hospitalCurrent(Simulation* sim){ return sim->getHospitalCurrent(); }
    int ICUtotal(Simulation* sim){ return sim->getICUtotal(); }
    int ICUCurrent(Simulation* sim){ return sim->getICUCurrent(); }
}

#endif