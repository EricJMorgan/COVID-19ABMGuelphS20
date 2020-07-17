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
    avgAsymptomatic = 1 - avgSymptomaticCarriers;
    avgMaskWearer = (double)sirTotalLocation.getMaskWearer() / (double)population;
    avgHygiene = (double)sirTotalLocation.getMaskWearer() / (double)population;

    //symptomatic carries have 100% chance of spreading relatively
    //social distancing of about 6m greatly decreases chances of risk 
    double socialDistancing;

    if (socialDistancingSeverity == 10) {
        socialDistancing = 0;
    } else {
        socialDistancing = (10.0 - (double)socialDistancingSeverity) / 10.0;
    }

    // mask cuts risk by 65%
    double avgMaskWearerRisk = 0.45 * avgMaskWearer;

    //asympomatic spread "very rare" WHO
    double avgAsymptomaticRisk = 0.01 * avgAsymptomatic;

    // assume hygiene reduces contact transmission by 20%
    double avgHygieneRisk = 0.8 * avgHygiene;

    // assumed increased chances of covid on a scale of 0 - 1.0 based on business(may be changed at a later date)
    // GENSTORE 0.6
    // TRANSPORT 0.8
    // SCHOOL 0.9
    // PARKSANDREC 0.2
    // SERVICES 0.2
    // ENTERTAINMENT 0.8
    // HEALTH 0.9
    // PLACEOFWORSHIP 0.8
    // RESIDENTIAL 0.5

    double locationRiskTotal;
    double locationRisks[9];

    // loop through various business and add to risk
    for(int k = 0; k < 9; k++){
        cout << getLocationCountAt(k) << " ";

    }

    //
    chanceOfInfection = (avgSymptomaticCarriers + avgMaskWearerRisk + avgAsymptomaticRisk + avgHygieneRisk) / 5 ;
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
