/****************
 * COVID-19ABMGuelphS20
 * 13/10/20
 * ver 1.04
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

void GeographicalRisk::updateAvgCountsAndRisk() {
    
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


