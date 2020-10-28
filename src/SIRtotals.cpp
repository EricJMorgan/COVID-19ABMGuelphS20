/****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
 * 
 * This is the class file for the SIR totals class. This just keeps track of agents behavious such as
 * wearing masks, hygiene, ect.
 ***************/


#include "SIRtotals.hh"
#include <iostream>

// Constructor
SIRtotals::SIRtotals() {
    //
}

//TODO need to account for recoverd agents
//TODO is this even needed?
void SIRtotals::updateTotals(vector<Agent *> susAgents, vector<Agent *> infAgents) {
    susceptible = (int)susAgents.size();
    infected = (int)infAgents.size();

    maskWearer = 0;
    hygiene = 0;
    maleCount = 0;
    showsSymptoms = 0;

    
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

        // if (infAgents[i]->getSymptoms()) {
        //    showsSymptoms++;
        // }
    }

    return;
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