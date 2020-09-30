/****************
 * COVID-19ABMGuelphS20
 * 30/09/20
 * ver 1.01
 * 
 * This is the header file for the SIR totals class. This just keeps track of agents behavious such as
 * wearing masks, hygiene, ect.
 ***************/


#ifndef SIRTOTALS_H_
#define SIRTOTALS_H_

#include <string>
#include <iostream>
#include <vector>
#include "agent.hh"

using namespace std;

//Declare simulation class
class SIRtotals {
    private:
    // for general SIR 
    int susceptible;
    int infected;

    // for geographic risk
    int maskWearer;
    int hygiene;
    int maleCount;
    int showsSymptoms;

    public:

    /**
     * SIRtotals
     * 
     * This is the contstructor of the object.
     * It is empty as it does not need to call anything
     * on initilzation
     */
    SIRtotals();

    /**
     * updateTotals
     * 
     * This is the method that updates the counters for each agents
     * status.
     * 
     * @param the list of susceptibale agents
     * @param the list of infected agents
     */
    void updateTotals(vector<Agent *> susAgents, vector<Agent *> infAgents);

    /**
     * getSusceptible
     * 
     * getter for the amount of susceptible agents
     * 
     * @return a int of the susceptible count
     */
    int getSusceptible();

    /**
     * getInfected
     * 
     * getter for the amount of infected agents
     * 
     * @return a int of the infected count
     */
    int getInfected();

    /**
     * getMaskWearer
     * 
     * getter for the amount of people wearing masks
     * 
     * @return a int of the mask wearing count
     */
    int getMaskWearer();

    /**
     * getHygiene
     * 
     * getter for the amount of people practicing good hygiene
     * 
     * @return a int of the good hygiene count
     */
    int getHygiene();

    /**
     * getMaleCount
     * 
     * getter for the amount of males in the simultion
     * 
     * @return a int of male count
     */
    int getMaleCount();

    /**
     * getShowsSymptoms
     * 
     * getter for the amount of agents showing symptoms
     * 
     * @return a int of the amount of people showing symptoms
     */
    int getShowsSymptoms();
};


#endif
