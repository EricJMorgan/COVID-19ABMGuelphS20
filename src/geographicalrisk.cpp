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

    // do this tmrrw
}

void GeographicalRisk::infectPeople() {
    for (size_t i = 0; i < population; i++) {
        double infectionChance = (double) rand()/RAND_MAX;

        if (infectionChance < chanceOfInfection) {
            currentAgents[i].AgentInfected(currentAgents[i].getAgentInfo());
        }
    }
}
