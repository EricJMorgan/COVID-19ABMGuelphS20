/****************
 * COVID-19ABMGuelphS20
 * 16/07/20
 * ver 0.03
 * 
 * This is the class file for the location class
 ***************/


#include "location.hh"
#include <iostream>



// Constructor
Location::Location() {
    postalCodeGrouping = "";
    for(int i = 0; i < 9; i++){
        locationCount[i] = 0;
    }
    population = 0;
    pplDensity = 0;
    avgTimeSpent = 0;
    avgAgentInteraction = 0;
    transportaionRoutesFromLocation = NULL;
    isResidential = true;
}

Location::Location(string newPostalCode, int shopData[9]){
    postalCodeGrouping = newPostalCode;
    isResidential = true;
    for(int i = 0; i < 9; i++){
        locationCount[i] = shopData[i];
        if(shopData[i] != 0) isResidential = false;
    }
    population = 0;
    pplDensity = 0;
    avgTimeSpent = 0;
    avgAgentInteraction = 0;
    transportaionRoutesFromLocation = NULL;
}

bool Location::getIsResidential(){
    return isResidential;
}

void Location::setPostalCodeGrouping(string newPostalCodeGrouping){
    postalCodeGrouping = newPostalCodeGrouping;
}

string Location::getPostalCodeGrouping(){
    return postalCodeGrouping;
}

void Location::increaseLocationCountAt(int index){
    if(index < 0 || index > 8) return;
    locationCount[index]++;
    isResidential = false;
}

void Location::increaseLocationCountAt(condenseLocationType index){
    increaseLocationCountAt((int)index);
}

int Location::getLocationCountAt(condenseLocationType index){
    return getLocationCountAt((int)index);
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