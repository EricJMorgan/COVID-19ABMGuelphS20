/****************
 * COVID-19ABMGuelphS20
 * 20/07/20
 * ver 0.02
 * 
 * This is the class file for the transportation class
 ***************/


#include "transportation.hh"
#include <iostream>
#include <string>

using namespace std;

Transportation::Transportation(Agent **arr, int arrSize){
    postalCodes = new PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
   
    

    for(int i = 0; i < 7000; i++){
        if(postalCodes->hashTable[i].getPostalCodeGrouping().compare("") != 0){
            locationList.push_back(postalCodes->hashTable[i]);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, getLocationListLength() - 1);

    for(int i = 0; i < arrSize; i++){
        locationList.at(distr(gen)).addAgentToSusceptible(arr[i]);
    }
}

Transportation::~Transportation(){
    delete postalCodes;
}

int Transportation::getLocationListLength(){
    return (int)locationList.size();
}

Location Transportation::getLocationAt(int index){
    if(index < 0 || index >= getLocationListLength()) return Location();
    return locationList.at(index);
}

Agent *Transportation::moveSusceptibleAgent(int locationOne, int locationTwo, int agentIndex){
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne).getSusceptibleSize()) return NULL;

    Agent *holder = locationList.at(locationOne).removeSusceptibleAgent(agentIndex);
    locationList.at(locationTwo).addAgentToSusceptible(holder);
    return holder;
}

Agent *Transportation::moveInfectedAgent(int locationOne, int locationTwo, int agentIndex){
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne).getInfectedSize()) return NULL;

    Agent *holder = locationList.at(locationOne).removeInfectedAgent(agentIndex);
    locationList.at(locationTwo).addAgentToInfected(holder);
    return holder;
}