/****************
 * COVID-19ABMGuelphS20
 * 13/07/20
 * ver 0.02
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
        switch(simAgents[i].getStatus){
            case SUSCEPTIBLE: susceptible++; break;
            case INFECTED: infected++; break;
            default: break;
        }
    }
}