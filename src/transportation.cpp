/****************
 * COVID-19ABMGuelphS20
 * 24/07/20
 * ver 0.05
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

    sort(locationList.begin(), locationList.end(), [](const Location& lhs, const Location& rhs){//Just to sort the list based on amount of locations
        return lhs.amountOfLocations < rhs.amountOfLocations;
    });

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

Location* Transportation::getLocationAt(int index){
    if(index < 0 || index >= getLocationListLength()) return NULL;
    return &locationList.at(index);
}

Agent *Transportation::moveSusceptibleAgent(int locationOne, int locationTwo, int agentIndex){
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getSusceptibleSize()) return NULL;

    Agent *holder = locationList.at(locationOne).removeSusceptibleAgent(agentIndex);
    locationList.at(locationTwo).addAgentToSusceptible(holder);
    return holder;
}

Agent *Transportation::moveInfectedAgent(int locationOne, int locationTwo, int agentIndex){
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getInfectedSize()) return NULL;

    Agent *holder = locationList.at(locationOne).removeInfectedAgent(agentIndex);
    locationList.at(locationTwo).addAgentToInfected(holder);
    return holder;
}

int Transportation::simulateAgentMovment(){
    int locationListSize = getLocationListLength();//This is done so this function is not called more that once
    int amountOfAgents;
    for(int i = 0; i < locationListSize; i++){
        amountOfAgents = getLocationAt(i)->getSusceptibleSize();
        for(int j = 0; j < amountOfAgents; j++){
            //TODO MOVE SUS AGENTS AROUND
        }
        amountOfAgents = getLocationAt(i)->getInfectedSize();
        for(int j = 0; j < amountOfAgents; j++){
            //TODO MOVE INFECTED AGENTS AROUND
        }
    }

    return InfectAgentsPostMovement();
}

int Transportation::InfectAgentsPostMovement(){
    int totalNewInfected = 0;
    int locationListSize = getLocationListLength();//This is done so this function is not called more that once
    for(int i = 0; i < locationListSize; i++){
        // will take care of all infecting

        totalNewInfected += getLocationAt(i)->infectPeople();
    }

    return totalNewInfected;
}

// Agent *Transportation::moveSusceptibleToInfected(int locationIndex, int agentIndex){
//     if(locationIndex < 0 || locationIndex >= getLocationListLength()) return NULL;
//     if(agentIndex < 0 || agentIndex >= getLocationAt(locationIndex).getSusceptibleSize()) return NULL;

//     Agent *holder = locationList.at(locationIndex).removeSusceptibleAgent(agentIndex);
//     holder->AgentInfected();//TODO not sure if its ok to use SIR class here
//     locationList.at(locationIndex).addAgentToInfected(holder);
//     return holder;
// }