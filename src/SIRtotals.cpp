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

void SIRtotals::updateTotals(int population) {
    susceptible = 0;
    infected = 0;
    // TODO: James make this static
    for(int i = 0; i < population; i++){
        switch(simAgents[i].DetermineSeverity()){
            case SUSCEPTIBLE: susceptible++; break;
            case INFECTED: infected++; break;
            default: break;
        }
    }
}