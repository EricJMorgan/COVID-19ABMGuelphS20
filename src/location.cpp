/****************
 * COVID-19ABMGuelphS20
 * 09/07/20
 * ver 0.02
 * 
 * This is the class file for the location class
 ***************/


#include "location.hh"
#include <iostream>



// Constructor
Location::Location() {
    postalCode = "";
    for(int i = 0; i < 9; i++){
        locationCount[i] = 0;
    }
    population = 0;
    pplDensity = 0;
    avgTimeSpent = 0;
    avgAgentInteraction = 0;
    currentAgents = NULL;
    transportaionRoutesFromLocation = NULL;
}

Location::Location(string newPostalCode, int shopData[9]){
    postalCode = newPostalCode;
    for(int i = 0; i < 9; i++){
        locationCount[i] = shopData[i];
    }
    population = 0;
    pplDensity = 0;
    avgTimeSpent = 0;
    avgAgentInteraction = 0;
    currentAgents = NULL;
    transportaionRoutesFromLocation = NULL;
}

int Location::getPopulation(){
    return population;
}

Agent *Location::getSusceptible(){
    return NULL;
}

Agent *Location::getInfected(){
    return NULL;
}

Agent *Location::getRecovered(){
    return NULL;
}
