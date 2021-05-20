/****************
 * COVID-19ABMGuelphS20
 * 27/11/20
 * ver 2.03
 * 
 * This is the class file for the transportation class. It is used to decide where each agent will move at any given point.
 * The factors that affect this range from time, day, and age. It also initilizes the array of locations and places agents in inital starting areas
 ***************/


#include "transportation.hh"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <random>

using namespace std;

Transportation::Transportation(Agent **arr, int arrSize){
    postalCodes = new PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
   
    //place non empty buckets into postalCodegrouping list
    for(int i = 0; i < 7000; i++){
        if(postalCodes->hashTable[i]->getPostalCodeGrouping().compare("") != 0){
            locationList.push_back(postalCodes->hashTable[i]);
        }
    }

    //This sorts the location list so that the more locations a postal code grouping has the further up the list they are
    sort(locationList.begin(), locationList.end(), [](const Location* lhs, const Location* rhs){
        return lhs->amountOfLocations < rhs->amountOfLocations;
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

    for(int i = 0; i < arrSize; i++){
        if (arr[i]->getSeverity() == INFECTED) {
            locationList.at(rand() % getLocationListLength())->addAgentToInfected(arr[i]);
        } else if (arr[i]->getSeverity() == SUSCEPTIBLE) {
            locationList.at(rand() % getLocationListLength())->addAgentToSusceptible(arr[i]);
        }
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
    return locationList.at(index);
}

Agent *Transportation::moveSusceptibleAgent(int locationOne, int locationTwo, int agentIndex){
    //error checking
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getSusceptibleSize()) return NULL;

    Agent *holder = getLocationAt(locationOne)->removeSusceptibleAgent(agentIndex);
    holder->setHasMoved(true);
    getLocationAt(locationTwo)->addAgentToSusceptible(holder);
    return holder;
}

Agent *Transportation::moveInfectedAgent(int locationOne, int locationTwo, int agentIndex){
    //error checking
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getInfectedSize()) return NULL;

    Agent *holder = getLocationAt(locationOne)->removeInfectedAgent(agentIndex);
    getLocationAt(locationTwo)->addAgentToInfected(holder);
    return holder;
}

int Transportation::simulateAgentMovement(int timeOfDay, DayOfWeek currDay, double chanceOfMoving[18][2][6][10], double agentChanceOfMitigation[18][5], double mitigationEffect[5], double locationRisk[10]){
    int locationListSize = getLocationListLength();
    int newLocation;

    //loops through all the locations and moves each agent
    for(int i = 0; i < locationListSize; i++){
        for(int j = 0; j < getLocationAt(i)->getSusceptibleSize(); j++){
            if(!getLocationAt(i)->getSusceptibleAgentAt(j)->getHasMoved()){
                newLocation = agentMovingTo(getLocationAt(i)->getSusceptibleAgentAt(j), getLocationAt(i)->getSusceptibleAgentAt(j)->getAgentInfo(), timeOfDay, currDay, chanceOfMoving);
                moveSusceptibleAgent(i, newLocation, j);
                if(newLocation != i) j--;
            }
        }
        for(int j = 0; j < getLocationAt(i)->getInfectedSize(); j++){
            if(!getLocationAt(i)->getInfectedAgentAt(j)->getHasMoved()){
                newLocation = agentMovingTo(getLocationAt(i)->getInfectedAgentAt(j), getLocationAt(i)->getInfectedAgentAt(j)->getAgentInfo(), timeOfDay, currDay, chanceOfMoving);
                moveInfectedAgent(i, newLocation, j);
                if(newLocation != i) j--;
            }
        }
    }

    for(int i = 0; i < locationListSize; i++){
        for(int j = 0; j < getLocationAt(i)->getSusceptibleSize(); j++){
            getLocationAt(i)->getSusceptibleAgentAt(j)->setHasMoved(false);
        }
        for(int j = 0; j < getLocationAt(i)->getInfectedSize(); j++){
            getLocationAt(i)->getInfectedAgentAt(j)->setHasMoved(false);
        }
    }

    return InfectAgentsPostMovement(agentChanceOfMitigation, mitigationEffect, locationRisk);
}

int Transportation::InfectAgentsPostMovement(double agentChanceOfMitigation[18][5], double mitigationEffect[5], double locationRisk[10]){
    int totalNewInfected = 0;
    int locationListSize = getLocationListLength();//This is done so this function is not called more that once
    for(int i = 0; i < locationListSize; i++){
        if(getLocationAt(i)->getInfectedSize() > 0){
            totalNewInfected += getLocationAt(i)->infectPeople(agentChanceOfMitigation, mitigationEffect, locationRisk);
        }
    }

    cout << "Total new Infected: " << totalNewInfected << "\n";
    return totalNewInfected;
}


int Transportation::agentMovingTo(Agent *agent, AgentInfo agentInfo, int timeOfDay, DayOfWeek currDay, double chanceOfMoving[18][2][6][10]){
    //This checks the agents data and decides their chance of moving based on age, time, and day of the week
    double sumOfChances = 0;
    double chanceOfMovementRange[10];
    for(int i = 0; i < 10; i++) sumOfChances += chanceOfMoving[agent->getAgentAgeGroup()][!isWeekDay(currDay)][timeOfDay / 4][i];

    chanceOfMovementRange[0] = chanceOfMoving[agent->getAgentAgeGroup()][!isWeekDay(currDay)][timeOfDay / 4][0] / sumOfChances;
    for(int i = 1; i < 10; i++) 
        chanceOfMovementRange[i] = chanceOfMovementRange[i - 1] + (chanceOfMoving[agent->getAgentAgeGroup()][!isWeekDay(currDay)][timeOfDay / 4][0] / sumOfChances);
    
    std::uniform_real_distribution<double> unif(0, sumOfChances);
    std::default_random_engine re;
    double randomNumber = unif(re);

    int locationToMove;
    for(locationToMove = 0; locationToMove < 9; locationToMove++){
        if(randomNumber <= chanceOfMovementRange[locationToMove]) break;
    }

    switch(locationToMove){
        //This causes any agent going to school/home to always go to the same residential/education area
        case SCHOOL:
            return getAgentEducationIndex(agent);
        case RESIDENTIAL:
            return getAgentResidentialIndex(agent);
        default:
            return findIndexToMove(findLocationList(locationToMove));
    }
    
    
}

vector<Location*> Transportation::findLocationList(int locationToMove){
    switch (locationToMove)
    {
    case GENSTORE:
        return hasGenStore;
    case TRANSPORT:
        return hasTransport;
    case SCHOOL:
        return hasSchool;
    case PARKSANDREC:
        return hasParksAndRec;
    case SERVICES:
        return hasServices;
    case ENTERTAINMENT:
        return hasEntertainment;
    case HEALTH:
        return hasHealth;
    case PLACEOFWORSHIP:
        return hasPlaceOfWorship;
    case RESIDENTIAL:
        return hasResidential;
    default:
        return hasResidential;
    }
}

bool Transportation::isWeekDay(DayOfWeek currDay){
    return 0 <= currDay && currDay <= 4;
}

int Transportation::findIndexToMove(vector<Location*> toMoveList){//TODO the logic for this and making it more likley to pick data higher up on the list
    return (monteCarloRandom(toMoveList.size()));
}

int Transportation::findResidentialIndex(vector<Location*> toMoveList){
    return (rand() % toMoveList.size());
}

bool Transportation::willMove(int percentChance){//TODO return true if the random shows into the percentage

    return (1 + (rand() % 100)) <= percentChance;
}

bool Transportation::inTimeRange(int timeOfDay, int min, int max){
    if(timeOfDay < 0 || timeOfDay > 24) return false;
    return timeOfDay >= min && timeOfDay <= max;
}

bool Transportation::willGoToSchool(DayOfWeek currDay, int timeOfDay){//TODO students might move to multiple schools a day, might need a fix
    return isWeekDay(currDay) && inTimeRange(timeOfDay, 8, 16);
}

bool Transportation::willGoToWork(DayOfWeek currDay, int timeOfDay){
    return isWeekDay(currDay) && inTimeRange(timeOfDay, 9, 17);
}

int Transportation::getAgentEducationIndex(Agent *agent){
    if(agent->getEducationIndex() == -1) agent->setEducationIndex(findIndexToMove(hasSchool));
    return agent->getEducationIndex();
}

int Transportation::getAgentResidentialIndex(Agent *agent){
    if(agent->getResidentialIndex() == -1) agent->setResidentialIndex(findIndexToMove(hasResidential));
    return agent->getResidentialIndex();
}

int Transportation::monteCarloRandom(int roof){
    int r1, r2;
    while(true){
        r1 = (int)(rand() % roof);
        r2 = (int)(rand() % roof);

        if(r2 < r1) return r1;
    }
}
