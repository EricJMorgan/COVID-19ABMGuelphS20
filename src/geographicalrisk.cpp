/****************
 * COVID-19ABMGuelphS20
 * 24/07/20
 * ver 0.06
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
    sirTotalLocation.updateTotals(susceptible, infected);
    double population = (double)susceptible.size() + (double)infected.size();

    if (population == 0) {
        return;
    }

    // calculate averages in compartment during current timestep
    
    avgSymptomaticCarriers = (double)sirTotalLocation.getShowsSymptoms() / population;
    avgAsymptomatic = ((double)sirTotalLocation.getInfected() - (double)sirTotalLocation.getShowsSymptoms()) / population;
    avgMaskWearer = (double)sirTotalLocation.getMaskWearer() / population;
    avgHygiene = (double)sirTotalLocation.getHygiene() / population;

    double totalAvgWeighted = (avgSymptomaticCarriers + avgAsymptomatic + avgMaskWearer + avgHygiene) * 100.0;

    //symptomatic carries have 100% chance of spreading relatively
    //social distancing of about 6m greatly decreases chances of risk 
    double socialDistancing = (10.0 - (double)socialDistancingSeverity) / 10.0;

    // mask cuts risk by 65%, therefore 45% overall risk transmission
    double avgMaskWearerRisk = 0.45 * avgMaskWearer;

    //asympomatic spread "very rare" WHO (now they saying its not lol gonna jus assume 5%)
    double avgAsymptomaticRisk = 0.05 * avgAsymptomatic;

    // assume hygiene reduces contact transmission by 20% (need more info)
    double avgHygieneRisk = 0.2 * avgHygiene;

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

    if (totalBusiness != 0) {
        locationRiskTotal = locationRiskTotal / (double)totalBusiness;
    }
    
    // cout << avgSymptomaticCarriers << " " << avgMaskWearerRisk<< " " << avgAsymptomaticRisk << " " << avgHygieneRisk << " " << locationRiskTotal << endl;

    // update chance of infection based on all factors, importance of factors
    chanceOfInfection = (avgSymptomaticCarriers * 0.3 + avgMaskWearerRisk * 0.3 + avgAsymptomaticRisk * 0.05 + avgHygieneRisk * 0.05 + locationRiskTotal * 0.3) * socialDistancing / totalAvgWeighted;

    // cout << chanceOfInfection << endl;
}

int GeographicalRisk::infectPeople() {
    updateAvgCountsAndRisk();
    int infectedCount = 0;

    for (int i = 0; i < (int)susceptible.size(); i++) {
        double agentInfectionChance = (double) rand()/RAND_MAX;

        if (agentInfectionChance < chanceOfInfection) {
            susceptible.at(i)->AgentInfected();
            infected.push_back(susceptible.at(i));
            susceptible.erase(susceptible.begin() + i);
            i--;
            infectedCount++;
        }
    }

    return infectedCount;
}

int GeographicalRisk::getLocationCountAt(int index){
    if(index < 0 || index > LOCATIONTYPESIZE) return -1;
    return locationCount[index];
}

int GeographicalRisk::getLocationCountAt(condenseLocationType index){
    return getLocationCountAt((int)index);
}
