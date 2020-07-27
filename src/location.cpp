/****************
 * COVID-19ABMGuelphS20
 * 17/07/20
 * ver 0.05
 * 
 * This is the class file for the location class
 ***************/


#include "location.hh"
#include <iostream>


// Constructor
Location::Location() {
    postalCodeGrouping = "";
    for(int i = 0; i < LOCATIONTYPESIZE; i++){
        locationCount[i] = 0;
    }
    population = 0;
    pplDensity = 0;
    avgTimeSpent = 0;
    avgAgentInteraction = 0;
    amountOfLocations = 0;
}

Location::Location(string newPostalCode, int shopData[LOCATIONTYPESIZE]){
    postalCodeGrouping = newPostalCode;
    for(int i = 0; i < 9; i++){
        locationCount[i] = shopData[i];
        if(i != 8) amountOfLocations += shopData[i];
        //if(shopData[i] != 0) isResidential = false;
    }
    population = 0;
    pplDensity = 0;
    avgTimeSpent = 0;
    avgAgentInteraction = 0;
}

void Location::setPostalCodeGrouping(string newPostalCodeGrouping){
    postalCodeGrouping = newPostalCodeGrouping;
}

string Location::getPostalCodeGrouping(){
    return postalCodeGrouping;
}

void Location::increaseLocationCountAt(int index){
    if(index < 0 || index > LOCATIONTYPESIZE) return;
    locationCount[index]++;
    //isResidential = false;
}

void Location::increaseLocationCountAt(condenseLocationType index){
    increaseLocationCountAt((int)index);
}

void Location::addPostalCodeToList(string postalCode){
    if(!postalCodeListContainsDup(postalCode)) postalCodes.push_back(postalCode);
}

int Location::getPostalCodeListLength(){
    return postalCodes.size();
}

string Location::getPostalCodeAt(int index){
    if(index < 0 || index >= getPostalCodeListLength()) return "";
    return postalCodes.at(index);
}


int Location::getPopulation(){
    return population;
}

vector<Agent *> Location::getSusceptible(){
    return susceptible;
}

vector<Agent *> Location::getInfected(){
    return infected;
}

bool Location::postalCodeListContainsDup(string newPostalCode){
    return std::find(postalCodes.begin(), postalCodes.end(), newPostalCode) != postalCodes.end();
}

void Location::addAgentToSusceptible(Agent *toAdd){
    if(toAdd == NULL) return;
    susceptible.push_back(toAdd);
}

void Location::addAgentToInfected(Agent *toAdd){
    if(toAdd == NULL) return;
    infected.push_back(toAdd);
}

Agent *Location::removeSusceptibleAgent(int index){//TODO stress test these as they could be very inificent
    if(index < 0 || index >= (int)susceptible.size()) return NULL;
    Agent *holder = susceptible.at(index);
    susceptible.erase(susceptible.begin() + index);
    return holder;
}

Agent *Location::removeInfectedAgent(int index){
    if(index < 0 || index >= (int)infected.size()) return NULL;
    Agent *holder = infected.at(index);
    infected.erase(infected.begin() + index);
    return holder;
}

Agent *Location::getSusceptibleAgentAt(int index){
    if(index < 0 || index >= (int)susceptible.size()) return NULL;
    return susceptible.at(index);
}

Agent *Location::getInfectedAgentAt(int index){
    if(index < 0 || index >= (int)susceptible.size()) return NULL;
    return infected.at(index);
}

int Location::getSusceptibleSize(){
    return (int)susceptible.size();
}

int Location::getInfectedSize(){
    return (int)susceptible.size();
}