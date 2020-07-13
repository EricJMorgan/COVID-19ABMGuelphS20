/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the class file for the SIR totals class
 ***************/


#include "SIRtotals.hh"
#include <iostream>

// Constructor
SIRtotals::SIRtotals() {
    //
}

void SIRtotals::updateTotals() {
    susceptible = 0;
    infected = 0;
    for(int i = 0; i < 131805; i++){
        if(simAgents[i].getStatus().compare("SUSCEPTIBLE") == 0){
            susceptible++;
        } else if(simAgents[i].getStatus().compare("INFECTED") == 0){
            infected++;
        }
    }
}