/****************
 * COVID-19ABMGuelphS20
 * 04/08/20
 * ver 0.05
 * 
 * This is the header file for the SIR totals class
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
    SIRtotals();
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
