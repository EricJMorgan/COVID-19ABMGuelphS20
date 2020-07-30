/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.04
 * 
 * This is the class file for the SIR totals class
 ***************/


#include "SIRtotals.hh"
#include <iostream>

// Constructor
SIRtotals::SIRtotals() {
    //
}

void SIRtotals::updateTotals(vector<Agent *> susAgents, vector<Agent *> infAgents) {
    susceptible = (int)susAgents.size();
    infected = (int)infAgents.size();
    
    for(int i = 0; i < susceptible; i++){
        if (susAgents[i]->wearingMask) {
            maskWearer++;
        }

        if (susAgents[i]->agentHygiene) {
            hygiene++;
        }

        if (susAgents[i]->getAgentInfo() < 18) {
           maleCount++;
        }

        if (susAgents[i]->getSymptoms()) {
           showsSymptoms++;
        }
    }

    for(int i = 0; i < infected; i++){
        if (infAgents[i]->wearingMask) {
            maskWearer++;
        }

        if (infAgents[i]->agentHygiene) {
            hygiene++;
        }

        if (infAgents[i]->getAgentInfo() < 18) {
           maleCount++;
        }

        if (infAgents[i]->getSymptoms()) {
           showsSymptoms++;
        }
    }
}

int SIRtotals::getSusceptible() {
    return susceptible;
}

int SIRtotals::getInfected() {
    return infected;
}

int SIRtotals::getMaskWearer() {
    return maskWearer;
}

int SIRtotals::getHygiene() {
    return hygiene;
}

int SIRtotals::getMaleCount() {
    return maleCount;
}

int SIRtotals::getShowsSymptoms() {
    return showsSymptoms;   
}