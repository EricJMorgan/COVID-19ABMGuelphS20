/****************
 * COVID-19ABMGuelphS20
 * 06/10/20
 * ver 1.03
 * 
 * This is the class file for the geographical risk class. The main
 * use for this class is to do the math for each area and decide how many 
 * people to infect in a given area.
 ***************/


#include "geographicalrisk.hh"
#include <iostream>

// Constructor
GeographicalRisk::GeographicalRisk() {
    socialDistancingSeverity = 8;

    //set all agent chances of mitagation too 0
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 4; j++){
            setAgentMitagationChance(i, j, 0);
        }
    }

    for(int i = 0; i < 4; i++){
        setMitagationEffectivness(i, 0);
    }
}

void GeographicalRisk::updateAvgCountsAndRisk() {
    //updates the total counts of the population
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

    //symptomatic carries have 100% chance of spreading relatively
    //social distancing of about 6m greatly decreases chances of risk 
    double socialDistancing = (10.0 - (double)socialDistancingSeverity) / 100.0;

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
    int totalBusiness = 0;

    // loop through various business and add to risk
    for(int k = 0; k < 9; k++){
        totalBusiness += getLocationCountAt(k);
        locationRiskTotal += getLocationCountAt(k)*locationRisks[k];
    }

    if (totalBusiness != 0) {
        locationRiskTotal = locationRiskTotal / (double)totalBusiness;
    }

    // weight location based migitation by importance 70% mask, 20% location risk, 10% hygiene
    double weightedMigitation = avgMaskWearerRisk * 0.7 + avgHygieneRisk * 0.1 + locationRiskTotal * 0.2;

    // update chance of infection based on all factors, importance of factors
    chanceOfInfection = weightedMigitation * socialDistancing * (avgSymptomaticCarriers + avgAsymptomaticRisk);
}

int GeographicalRisk::infectPeople() {
    updateAvgCountsAndRisk();
    int infectedCount = 0;

    //This loop goes throught and infects people based off of their % chance in a certin area
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

void GeographicalRisk::setAgentMitagationChance(int ageGroup, int strategy, double value){
    if(ageGroup < 0 || ageGroup > 17) return;
    if(strategy < 0 || strategy > 3) return;
    if(value < 0 || value > 1) return;

    agentMitagationChance[ageGroup][strategy] = value;
} 

void GeographicalRisk::setMitagationEffectivness(int strategy, double value){
    if(strategy < 0 || strategy > 3) return;
    if(value < 0 || value > 1) return;

    mitagationEffectivness[strategy] = value;
}
