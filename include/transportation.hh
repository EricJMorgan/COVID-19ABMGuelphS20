/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.04
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
     * @return a copy of the location object
     */
    Location getLocationAt(int index);

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


    private:
    PostalCodeHash *postalCodes;
    std::vector<Location> locationList;

    int randomInRange(int floor, int ceiling);

};


#endif
