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

    int getSusceptible();
    int getInfected();
    int getMaskWearer();
    int getHygiene();
    int getMaleCount();
    int getShowsSymptoms();
};


#endif
