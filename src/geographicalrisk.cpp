/****************
 * COVID-19ABMGuelphS20
 * 27/11/20
 * ver 2.01
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
}

void GeographicalRisk::updateAvgCountsAndRisk(double agentChanceOfMitigation[18][5], double mitigationEffect[5], double locationRisk[10]) {
    //give each age group a infection chance based on chanceOfMitigation[ageGroup] * mitigationEffect. Add all of those together to get a single age groups chance of infection
    for(int i = 0; i < 18; i++){
        agentChanceOfInfection[i] = 0;
        for(int j = 0; j < 5; j++){
            agentChanceOfInfection[i] += ((agentChanceOfMitigation[i][j] * mitigationEffect[j]) * 0.20);  // we multiply by 0.20 to keep value under 1
        }
    }

    //TODO figure out location priority to add that to risk
}

int GeographicalRisk::infectPeople(double agentChanceOfMitigation[18][5], double mitigationEffect[5], double locationRisk[10]) {//TODO this does not take into account each ageGroups chance of using mitigation strategys
    updateAvgCountsAndRisk(agentChanceOfMitigation, mitigationEffect, locationRisk);
    double randomNum;
    int amountOfInfected = 0;
    for(int i = 0; i < (int)susceptible.size(); i++){
        randomNum = ((double) rand() / (RAND_MAX));
        cout << randomNum << "    " << agentChanceOfInfection[susceptible.at(i)->getAgentAgeGroup()] << "\n";

        if(randomNum < agentChanceOfInfection[susceptible.at(i)->getAgentAgeGroup()]){
            susceptible.at(i)->incubateAgent();
            infected.push_back(susceptible.at(i));
            susceptible.erase(susceptible.begin() + i);
            i--;
            amountOfInfected++;
        }
    }

    if(amountOfInfected > 0){
        cout << "Amount Infected: " << amountOfInfected << "\n";
    }
    
    return amountOfInfected;
    
}

int GeographicalRisk::getLocationCountAt(int index){
    if(index < 0 || index > LOCATIONTYPESIZE) return -1;
    return locationCount[index];
}

int GeographicalRisk::getLocationCountAt(condenseLocationType index){
    return getLocationCountAt((int)index);
}


