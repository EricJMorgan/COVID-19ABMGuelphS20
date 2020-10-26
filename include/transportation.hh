/****************
 * COVID-19ABMGuelphS20
 * 13/10/20
 * ver 1.03
 * 
 * This is the header file for the transportation class. It is used to decide where each agent will move at any given point.
 * The factors that affect this range from time, day, and age. It also initilizes the array of locations and places agents in inital starting areas
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

//The way to identify the day of the week
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
     * @param **arr and array of agent pointers
     * @param arrSize the size of the array
     */
    Transportation(Agent **arr, int arrSize);

    /**
     * ~Transportation
     * 
     * This is the de-constructor for the class. 
     * This delets the postalCode object
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
     * @param index the index of the wanted data must be in range 0 <= index < listLength
     * @return the location object
     */
    Location *getLocationAt(int index);

    /**
     * moveSusceptibleAgent
     * 
     * This will move a susceptible agent from one location to another
     * by removing it from one vector into another based on the given index
     * 
     * @param locationOne the locations index from which to remove the sus agent
     * @param locationTwo the locations index from which to add the sus agent
     * @param agentIndex the agents index from location ones susceptible vector
     * @return the pointer to the moved agent NULL if error occured
     */
    Agent *moveSusceptibleAgent(int locationOne, int locationTwo, int agentIndex);

    /**
     * moveInfectedAgent
     * 
     * This will move a infected agent from one location to another
     * by removing it from one vector into another based on the given index
     * 
     * @param locationOne the locations index from which to remove the infected agent
     * @param locationTwo the locations index from which to add the infected agent
     * @param agentIndex the agents index from location ones infected vector
     * @return the pointer to the moved agent NULL if error occured
     */
    Agent *moveInfectedAgent(int locationOne, int locationTwo, int agentIndex);

    /**
     * moveSusceptibleToInfected
     * 
     * This will move a susceptible agent to infected in a given location
     * and will update the agents internal SIR data
     * 
     * @param locationIndex the index of the wanted location to shift the agent
     * @param agentIndex the index of the agent from the locations sus vector
     * @return a pointer to the shifted agent NULL if error occurs
     */
    Agent *moveSusceptibleToInfected(int locationIndex, int agentIndex);

    /**
     * simulateAgentMovment
     * 
     * When called this method will simulate the movment of the entire population of
     * the given location
     */
    int simulateAgentMovment(int timeOfDay, DayOfWeek currDay);

    /**
     * updateLocationRisks
     * 
     * When called this method will update coronavirus risk factors
     * @param socialDistancingSeverity amount of social distancing
     * @param associatedLocRisks coronavirus risk dependant on type of business
     */
    void updateLocationRisks(int socialDistancingSeverity, double associatedLocRisks[]);

    

    private:
    PostalCodeHash *postalCodes;
    std::vector<Location*> locationList;
    std::vector<Location*> hasGenStore;
    std::vector<Location*> hasTransport;
    std::vector<Location*> hasSchool;
    std::vector<Location*> hasParksAndRec;
    std::vector<Location*> hasServices;
    std::vector<Location*> hasEntertainment;
    std::vector<Location*> hasHealth;
    std::vector<Location*> hasPlaceOfWorship;
    std::vector<Location*> hasResidential;

    /**
     * randomInRange
     * 
     * Takes in the inclusive floor and ceiling
     * and finds a random number in the range
     * 
     * @param floor the inclusive floor of the range
     * @param ceiling the inclusive ceiling of the range
     * @return the random number generated
     */
    int randomInRange(int floor, int ceiling);

    /**
     * agentMovingTo
     * 
     * This is a helper function that will look at the given data for
     * an agent and will decide if and where it will move
     * 
     * @param toMove the agent data it will look at to decide if it will move
     * @param timeOfDay the current time of day
     * @param currDay the day of the week
     * @return the index that the agent will move to -1 if it will stay in place
     */
    int agentMovingTo(Agent *agent, AgentInfo agentInfo, int timeOfDay, DayOfWeek currDay);

    /**
     * InfectAgentsPostMovement
     * 
     * After movment happens infects people at
     * each location in the simulation
     * 
     * @return a int of the amount of the newly infected
     */
    int InfectAgentsPostMovement();


    /**
     * isWeekDay
     * 
     * takes in a DayOfWeek enum and checks if it is a weekday
     * 
     * @param currDay the day to check
     * @return true if is weekday false if not weekday
     */
    bool isWeekDay(DayOfWeek currDay);

    /**
     * willMove
     * 
     * This is a helper function to take in a % chance
     * that an agent will move the higher the percentChance
     * the more likley to return true
     * 
     * @param percentChance in range 1-100
     * @return a bool of if the chances came up true or false
     */
    bool willMove(int percentChance);


    /**
     * findIndexToMove
     * 
     * this function will take in any given location list
     * to find what location the agent will be moving to index wise
     * The whole idea of this is more agents are more likley to go somewhere
     * with more locations so this is mroe likley to return a higher number as the
     * list of locations is sorted lower to higher
     * 
     * @param toMoveList a vector of location pointers of the given type of place the agent will move to
     * @return the index in the location vector that the agent will move to
     */
    int findIndexToMove(vector<Location*> toMoveList);

    /**
     * findResidentialIndex
     * 
     * this function will take in a residential location list
     * to find what location the agent will be moving to index wise.
     * 
     * @param toMoveList a vector of location pointers to residential places
     * @return the index in the location vector that the agent will move to
     */
    int findResidentialIndex(vector<Location*> toMoveList);

    /**
     * inTimeRange
     * 
     * this function will take the current time and then
     * the floor and roof of the time range that is acceptable 
     * 
     * @param timeOfDay the current time of day
     * @param min the inclusive floor of the range
     * @param max the inclusive roof of the range
     * @return a bool of if it is range
     */
    bool inTimeRange(int timeOfDay, int min, int max);

    /**
     * willGoToSchool
     * 
     * this function looks at the day and time to see if a student will
     * be at school for a paticular timestep ie 10am on a thursday they would
     * vs a sunday at 5pm
     * 
     * @param currDay an enum of the currDay
     * @param timeOfDay the current time
     * @return true if school is open false if not
     */
    bool willGoToSchool(DayOfWeek currDay, int timeOfDay);

    /**
     * willGoToWork
     * 
     * this function looks at the day and time to see if an adult
     * will be at work for a paticular timestep ie 10am on a thursday they
     * would be vs a sunday at 7pm
     * 
     * @param currDay an enum of the currDay
     * @param timeOfDay the current time
     * @return true if work is open false if not
     */
    bool willGoToWork(DayOfWeek currDay, int timeOfDay);

    /**
     * adultChanceOfMoving
     * 
     * this is a helper function for agent moving to
     * that allows a % chance of each agent moving to a given place given their age
     * 
     * @param currrDay the current day of the week
     * @param currTime the current time of the day
     * @param genWork the chance of someone going to a genreal store either for work or shopping
     * @param servWork the chance of someone going to a service store either for work or shopping
     * @param goOut the chance of someone going out for entertainment
     * @param needServ the chance of someone needing service
     * @param goPark the chance of someone going to parks and rec
     * @return the index that the agent will be moving to
     */
    int adultChanceOfMoving(Agent *agent, DayOfWeek currDay, int currTime, int genWork, int servWork, int goOut, int needServ, int goPark, int health, int worship);

    /**
     * getAgentEducationIndex
     * 
     * This is a helper function to get the agents
     * education index. If the agent does not have one yet
     * it will be assigned a random one, for the rest of the
     * simulation that agent will always go to that school
     * 
     * @param agent to get education index from
     * @return the index the agent will use
     */
    int getAgentEducationIndex(Agent *agent);

    /**
     * getAgentResidentialIndex
     * 
     * This is a helper function to get the agents 
     * residentialIndex. If the agent does not have one yet,
     * it will be assigned a random one, for the rest of the simulation
     * that agent will always go to that residential area
     * 
     * @param agent to get residential index from
     * @return the index the agent will use
     */
    int getAgentResidentialIndex(Agent *agent);

    /**
     * moteCarloRandom
     * 
     * this is the monteCarlo random number generation
     * it is more likley to output a higher number in the range 
     * of 0 - (roof - 1)
     * 
     * @param roof the max number to generate (exlusive)
     * @return the random number generated
     */
    int monteCarloRandom(int roof);

};

#endif
