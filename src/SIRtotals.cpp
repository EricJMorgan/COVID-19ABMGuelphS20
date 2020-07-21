/****************
 * COVID-19ABMGuelphS20
 * 15/07/20
 * ver 0.03
 * 
 * This is the class file for the SIR totals class
 ***************/


#include "SIRtotals.hh"
#include <iostream>

// Constructor
SIRtotals::SIRtotals() {
    //
}

void SIRtotals::updateTotals(int population, Agent* simAgents) {
    susceptible = 0;
    infected = 0;
    maskWearer = 0;
    hygiene = 0;
    // TODO: James make this static
    for(int i = 0; i < population; i++){
        if (simAgents[i].wearingMask) {
            maskWearer++;
        }

        if (simAgents[i].agentHygiene) {
            hygiene++;
        }

        if (simAgents[i].getAgentInfo() < 18) {
           maleCount++;
        }

        if (simAgents[i].getSymptoms()) {
           showsSymptoms++;
        }
        
        switch(simAgents[i].DetermineSeverity()){
            case SUSCEPTIBLE: susceptible++; break;
            case INFECTED: infected++; break;
            case RECOVERED: recovered++; break;
            case DECEASED: deceased++; break;
            default: break;
        }
    }
}

int SIRtotals::getSusceptible() {
    return susceptible;
}

int SIRtotals::getInfected() {
    return infected;
}

int SIRtotals::getRecovered() {
    return recovered;
}

int SIRtotals::getDeceased() {
    return deceased;
}

int SIRtotals::getMaskWearer() {
    return maskWearer;
}

int SIRtotals::getHygiene() {
    return hygiene;
}

int SIRtotals::getSocialDistance() {
    return socialDistance;
}

int SIRtotals::getMaleCount() {
    return maleCount;
}

int SIRtotals::getShowsSymptoms() {
    return showsSymptoms;   
}