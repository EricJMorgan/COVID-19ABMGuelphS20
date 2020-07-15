/****************
 * COVID-19ABMGuelphS20
 * 15/07/20
 * ver 0.04
 * 
 * This is the header file for the SIR totals class
 ***************/


#ifndef SIRTOTALS_H_
#define SIRTOTALS_H_

#include <string>
#include <iostream>
#include "agent.hh"

using namespace std;

//Declare simulation class
class SIRtotals {
    private:
    int susceptible;
    int infected;
    Agent* simAgents;

    public:
    SIRtotals();
    void updateTotals(int population);
};


#endif
