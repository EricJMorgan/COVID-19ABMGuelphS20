/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the class file for the geographical risk class
 ***************/


#include "geographicalrisk.hh"
#include <iostream>

// Constructor
GeographicalRisk::GeographicalRisk() {
    // x agent is infected AgentInfected()
}

void GeographicalRisk::updateAvgCountsAndRisk() {
    sirTotalLocation.updateTotals(population, currentAgents);

    // calculate averages in compartment during current timestep
    avgSymptomaticCarriers = (double)sirTotalLocation.getShowsSymptoms() / (double)population;
    avgMaskWearer = (double)sirTotalLocation.getMaskWearer() / (double)population;
    avgHygiene = (double)sirTotalLocation.getMaskWearer() / (double)population;

    //symptomatic carries have 100% chance of spreading

    // mask cuts risk by 65%


    // assume hygiene reduces contact by 65%


    // loop through various business and add to risk
    for(int k = 0; k < 9; k++){
        cout << getLocationCountAt(k) << " ";
    }

    //
    chanceOfInfection = avgSymptomaticCarriers;



}

void GeographicalRisk::infectPeople() {
    updateAvgCountsAndRisk();

    for (size_t i = 0; i < population; i++) {
        double agentInfectionChance = (double) rand()/RAND_MAX;

        if (agentInfectionChance < chanceOfInfection) {
            currentAgents[i].AgentInfected(currentAgents[i].getAgentInfo());
        }
    }
}

int GeographicalRisk::getLocationCountAt(int index){
    if(index < 0 || index > 8) return -1;
    return locationCount[index];
}
