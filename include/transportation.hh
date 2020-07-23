/****************
 * COVID-19ABMGuelphS20
 * 23/07/20
 * ver 0.05
 * 
 * This is the header file for the transportation class
 ***************/


#ifndef TRANSPORTATION_H_
#define TRANSPORTATION_H_

#include <string>
#include <iostream>
#include <vector>
#include <random>

#include "postalCodeHash.hh"
#include "agent.hh"

using namespace std;

enum DayOfWeek{MON, TUE, WED, THU, FRI, SAT, SUN};

//Declare simulation class
class Transportation {
    public:
    /**
     * Transportation
     * 
     * This is the constructor for the Transportation class
     * it takes in an array of agent pointers and the size of said array
     * 
     * 
     * @param **arr, and array of agent pointers
     * @param arrSize, the size of the array
     */
    Transportation(Agent **arr, int arrSize);

    /**
     * ~Transportation
     * 
     * This is the de-constructor for the class
     */
    ~Transportation();

    /**
     * getLocationListLength
     * 
     * This gets the length of the location list
     * that is generated what the object is made
     * 
     * @return the length of the internal List
     */
    int getLocationListLength();

    /**
     * getLocationAt
     * 
     * This gets the location data from a given index
     * due to the location never changing it only returns
     * a copy of the object
     * 
     * @param index, the index of the wanted data must be in range 0 <= index < listLength
     * @return the location object
     */
    Location *getLocationAt(int index);

    /**
     * moveSusceptibleAgent
     * 
     * This will move a susceptible agent from one location to another
     * by removing it from one vector into another based on the given index
     * 
     * @param locationOne, the locations index from which to remove the sus agent
     * @param locationTwo, the locations index from which to add the sus agent
     * @param agentIndex, the agents index from location ones susceptible vector
     * @return the pointer to the moved agent, NULL if error occured
     */
    Agent *moveSusceptibleAgent(int locationOne, int locationTwo, int agentIndex);

    /**
     * moveInfectedAgent
     * 
     * This will move a infected agent from one location to another
     * by removing it from one vector into another based on the given index
     * 
     * @param locationOne, the locations index from which to remove the infected agent
     * @param locationTwo, the locations index from which to add the infected agent
     * @param agentIndex, the agents index from location ones infected vector
     * @return the pointer to the moved agent, NULL if error occured
     */
    Agent *moveInfectedAgent(int locationOne, int locationTwo, int agentIndex);

    /**
     * moveSusceptibleToInfected
     * 
     * This will move a susceptible agent to infected in a given location
     * and will update the agents internal SIR data
     * 
     * @param locationIndex, the index of the wanted location to shift the agent
     * @param agentIndex, the index of the agent from the locations sus vector
     * @return a pointer to the shifted agent, NULL if error occurs
     */
    Agent *moveSusceptibleToInfected(int locationIndex, int agentIndex);

    /**
     * simulateAgentMovment
     * 
     * When called this method will simulate the movment of the entire population of
     * the given location
     */
    void simulateAgentMovment();

    private:
    PostalCodeHash *postalCodes;
    std::vector<Location> locationList;
    std::vector<Location*> hasGenStore;
    std::vector<Location*> hasTransport;
    std::vector<Location*> hasSchool;
    std::vector<Location*> hasParksAndRec;
    std::vector<Location*> hasServices;
    std::vector<Location*> hasEntertainment;
    std::vector<Location*> hasHealth;
    std::vector<Location*> hasPlaceOfWorship;
    std::vector<Location*> hasResidential;

    int randomInRange(int floor, int ceiling);

    /**
     * agentMovingTo
     * 
     * This is a helper function that will look at the given data for
     * an agent and will decide if and where it will move
     * 
     * @param toMove, the agent data it will look at to decide if it will move
     * @param timeOfDay, the current time of day
     * @param currDay, the day of the week
     * @return the index that the agent will move to, -1 if it will stay in place
     */
    int agentMovingTo(Agent *toMove, int timeOfDay, DayOfWeek currDay);

    void InfectAgentsPostMovement();

};


#endif
