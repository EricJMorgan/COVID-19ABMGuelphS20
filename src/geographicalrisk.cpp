/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.04
 * 
 * This is the class file for the geographical risk class
 ***************/


#include "geographicalrisk.hh"
#include <iostream>

// Constructor
GeographicalRisk::GeographicalRisk() {
    //
}

void GeographicalRisk::updateAvgCountsAndRisk() {
    sirTotalLocation.updateTotals(population, currentAgents);

    // calculate averages in compartment during current timestep
    avgSymptomaticCarriers = (double)sirTotalLocation.getShowsSymptoms() / (double)population;
    avgAsymptomatic = 1 - avgSymptomaticCarriers;
    avgMaskWearer = (double)sirTotalLocation.getMaskWearer() / (double)population;
    avgHygiene = (double)sirTotalLocation.getHygiene() / (double)population;

    double totalAvgWeighted = avgSymptomaticCarriers + avgAsymptomatic + avgMaskWearer + avgHygiene;

    //symptomatic carries have 100% chance of spreading relatively
    //social distancing of about 6m greatly decreases chances of risk 
    double socialDistancing = (10.0 - (double)socialDistancingSeverity) / 10.0;

    // mask cuts risk by 65%, therefore 45% overall risk transmission
    double avgMaskWearerRisk = 0.45 * avgMaskWearer;

    //asympomatic spread "very rare" WHO (now they saying its not lol gonna jus assume 5%)
    double avgAsymptomaticRisk = 0.05 * avgAsymptomatic;

    // assume hygiene reduces contact transmission by 20% (need more info)
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

    double locationRiskTotal = 0.0;
    double locationRisks[9] = {0.6, 0.8, 0.9, 0.2, 0.2, 0.8, 0.9, 0.8, 0.5};
    int totalBusiness = 0;

    // loop through various business and add to risk
    for(int k = 0; k < 9; k++){
        totalBusiness += getLocationCountAt(k);
        locationRiskTotal += getLocationCountAt(k)*locationRisks[k];
    }

    locationRiskTotal = locationRiskTotal / (double)totalBusiness;

    // update chance of infection based on all factors
    chanceOfInfection = (avgSymptomaticCarriers + avgMaskWearerRisk + avgAsymptomaticRisk + avgHygieneRisk) * socialDistancing * locationRiskTotal / totalAvgWeighted ;
}

void GeographicalRisk::infectPeople() {
    updateAvgCountsAndRisk();

    for (int i = 0; i < population; i++) {
        double agentInfectionChance = (double) rand()/RAND_MAX;

        if (currentAgents[i].DetermineSeverity() == SUSCEPTIBLE && agentInfectionChance < chanceOfInfection) {
            currentAgents[i].AgentInfected();
        }
    }
}

int GeographicalRisk::getLocationCountAt(int index){
    if(index < 0 || index > LOCATIONTYPESIZE) return -1;
    return locationCount[index];
}

int GeographicalRisk::getLocationCountAt(condenseLocationType index){
    return getLocationCountAt((int)index);
}
