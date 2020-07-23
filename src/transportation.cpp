/****************
 * COVID-19ABMGuelphS20
 * 23/07/20
 * ver 0.04
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

    //This sorts the location list so that the more locations a postal code grouping has the further up the list they are
    sort(locationList.begin(), locationList.end(), [](const Location& lhs, const Location& rhs){
        return lhs.amountOfLocations < rhs.amountOfLocations;
    });

    //This adds all the locations into lists to make the movement math eaiser
    Location *holder;
    for(int i = 0; i < getLocationListLength(); i++){
        getLocationAt(i)->setLocationIndex(i);
        holder = getLocationAt(i);
        if(holder->getLocationCountAt(GENSTORE)) hasGenStore.push_back(holder);
        if(holder->getLocationCountAt(TRANSPORT)) hasTransport.push_back(holder);
        if(holder->getLocationCountAt(SCHOOL)) hasSchool.push_back(holder);
        if(holder->getLocationCountAt(PARKSANDREC)) hasParksAndRec.push_back(holder);
        if(holder->getLocationCountAt(SERVICES)) hasServices.push_back(holder);
        if(holder->getLocationCountAt(ENTERTAINMENT)) hasEntertainment.push_back(holder);
        if(holder->getLocationCountAt(HEALTH)) hasHealth.push_back(holder);
        if(holder->getLocationCountAt(PLACEOFWORSHIP)) hasPlaceOfWorship.push_back(holder);
        if(holder->getLocationCountAt(RESIDENTIAL)) hasResidential.push_back(holder);
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

Location* Transportation::getLocationAt(int index){
    if(index < 0 || index >= getLocationListLength()) return NULL;
    return &locationList.at(index);
}

Agent *Transportation::moveSusceptibleAgent(int locationOne, int locationTwo, int agentIndex){
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getSusceptibleSize()) return NULL;

    Agent *holder = getLocationAt(locationOne)->removeSusceptibleAgent(agentIndex);
    getLocationAt(locationTwo)->addAgentToSusceptible(holder);
    return holder;
}

Agent *Transportation::moveInfectedAgent(int locationOne, int locationTwo, int agentIndex){
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getInfectedSize()) return NULL;

    Agent *holder = getLocationAt(locationOne)->removeInfectedAgent(agentIndex);
    getLocationAt(locationTwo)->addAgentToInfected(holder);
    return holder;
}

void Transportation::simulateAgentMovment(){
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

    InfectAgentsPostMovement();
}

void Transportation::InfectAgentsPostMovement(){
    int locationListSize = getLocationListLength();//This is done so this function is not called more that once
    for(int i = 0; i < locationListSize; i++){
        // will take care of all infecting

        getLocationAt(i)->infectPeople();
    }
}


int Transportation::agentMovingTo(Agent *toMove, int timeOfDay, DayOfWeek currDay){
    AgentInfo agentInfo = toMove->getAgentInfo();
    if(agentInfo== MALE0TO4 || agentInfo == FEMALE0TO4) return findIndexToMove(hasResidential);//For now lets assume babies stay home all day
    if(agentInfo == MALE5TO9 || agentInfo == FEMALE5TO9){//5to9 year olds only go to school and then go home really
        if(isWeekDay(currDay) && (inTimeRange(timeOfDay, 8, 16))) return findIndexToMove(hasSchool);
        if(!isWeekDay(currDay) && inTimeRange(timeOfDay, 11, 18) && willMove(30)) return findIndexToMove(hasEntertainment);//TODO might change % chance based on income
        return findIndexToMove(hasResidential);
    }

    return -1;
}

bool Transportation::isWeekDay(DayOfWeek currDay){
        return 0 <= currDay && currDay <= 4;
}

int Transportation::findIndexToMove(vector<Location*> toMoveList){//TODO the logic for this and making it more likley to pick data higher up on the list

    return -1;
}

bool Transportation::willMove(int percentChance){//TODO return true if the random shows into the percentage

    return false;
}

bool Transportation::inTimeRange(int timeOfDay, int min, int max){

    return false;
}
// Agent *Transportation::moveSusceptibleToInfected(int locationIndex, int agentIndex){
//     if(locationIndex < 0 || locationIndex >= getLocationListLength()) return NULL;
//     if(agentIndex < 0 || agentIndex >= getLocationAt(locationIndex).getSusceptibleSize()) return NULL;

//     Agent *holder = locationList.at(locationIndex).removeSusceptibleAgent(agentIndex);
//     holder->AgentInfected();//TODO not sure if its ok to use SIR class here
//     locationList.at(locationIndex).addAgentToInfected(holder);
//     return holder;
// }