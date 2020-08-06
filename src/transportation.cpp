/****************
 * COVID-19ABMGuelphS20
 * 04/08/20
 * ver 0.07
 * 
 * This is the class file for the transportation class
 ***************/


#include "transportation.hh"
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

Transportation::Transportation(Agent **arr, int arrSize){
    postalCodes = new PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
   
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
        locationList.at(rand() % getLocationListLength())->addAgentToSusceptible(arr[i]);
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
    if(locationOne < 0 || locationOne >= getLocationListLength()) return NULL;//Test cases to make sure input is valid
    if(locationTwo < 0 || locationTwo >= getLocationListLength()) return NULL;
    if(agentIndex < 0 || agentIndex >= getLocationAt(locationOne)->getSusceptibleSize()) return NULL;

    Agent *holder = getLocationAt(locationOne)->removeSusceptibleAgent(agentIndex);
    holder->setHasMoved(true);
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

int Transportation::simulateAgentMovment(int timeOfDay, DayOfWeek currDay){
    int locationListSize = getLocationListLength();//This is done so this function is not called more that once
    int newLocation;
    for(int i = 0; i < locationListSize; i++){
        for(int j = 0; j < getLocationAt(i)->getSusceptibleSize(); j++){
            if(!getLocationAt(i)->getSusceptibleAgentAt(j)->getHasMoved()){
                newLocation = agentMovingTo(getLocationAt(i)->getSusceptibleAgentAt(j)->getAgentInfo(), timeOfDay, currDay);
                moveSusceptibleAgent(i, newLocation, j);
                if(newLocation != i) j--;
            }
        }
        for(int j = 0; j < getLocationAt(i)->getInfectedSize(); j++){
            if(!getLocationAt(i)->getInfectedAgentAt(j)->getHasMoved()){
                newLocation = agentMovingTo(getLocationAt(i)->getInfectedAgentAt(j)->getAgentInfo(), timeOfDay, currDay);
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

    return InfectAgentsPostMovement();
}

int Transportation::InfectAgentsPostMovement(){
    int totalNewInfected = 0;
    int locationListSize = getLocationListLength();//This is done so this function is not called more that once
    for(int i = 0; i < locationListSize; i++){
        totalNewInfected += getLocationAt(i)->infectPeople();
    }

    return totalNewInfected;
}


int Transportation::agentMovingTo(AgentInfo agentInfo, int timeOfDay, DayOfWeek currDay){//TODO no health or Place of worship incluided yet
    if(agentInfo == MALE0TO4 || agentInfo == FEMALE0TO4);
    else if(agentInfo == MALE5TO9 || agentInfo == FEMALE5TO9){//5to9 year olds only go to school and then go home really
        if(willGoToSchool(currDay, timeOfDay)) return findIndexToMove(hasSchool);
        if(!isWeekDay(currDay) && inTimeRange(timeOfDay, 11, 18) && willMove(30)) return findIndexToMove(hasEntertainment);//TODO might change % chance based on income
    }
    else if(agentInfo == MALE10TO14 || agentInfo == FEMALE10TO14){
        if(willGoToSchool(currDay, timeOfDay)) return findIndexToMove(hasSchool);
        if(!isWeekDay(currDay) && inTimeRange(timeOfDay, 11, 18) && willMove(40)) return findIndexToMove(hasEntertainment);
    }
    else if(agentInfo == MALE15TO19 || agentInfo == FEMALE15TO19){
        if(willGoToSchool(currDay, timeOfDay) && willMove(85)) return findIndexToMove(hasSchool);
        if(!isWeekDay(currDay) && willMove(40) && inTimeRange(timeOfDay, 9, 18)) return findIndexToMove(hasParksAndRec);
        if((isWeekDay(currDay) && inTimeRange(timeOfDay, 11,20) && willMove(30)) || 
            (!isWeekDay(currDay) && inTimeRange(timeOfDay, 11, 24) && willMove(75))) return findIndexToMove(hasEntertainment);
        //TODO add mroe options to kids
        if(inTimeRange(timeOfDay, 12, 20) && willMove(40)) return findIndexToMove(hasServices);
    }
    else if(agentInfo == MALE20TO24 || agentInfo == FEMALE20TO24){
        if(willGoToSchool(currDay, timeOfDay) && willMove(75)) return findIndexToMove(hasSchool);
        if(willGoToWork(currDay, timeOfDay) && willMove(15)) return findIndexToMove(hasGenStore);
        if(inTimeRange(timeOfDay, 18, 24) && !isWeekDay(currDay) && willMove(70)) return findIndexToMove(hasEntertainment);
        if(inTimeRange(timeOfDay, 16, 20) && willMove(35)) return findIndexToMove(hasServices);
        if(inTimeRange(timeOfDay, 16, 18) && willMove(20)) return findIndexToMove(hasGenStore);
        if(inTimeRange(timeOfDay, 10, 18) && !isWeekDay(currDay) && willMove(50)) return findIndexToMove(hasParksAndRec);
    }
    else if(agentInfo == MALE25TO29 || agentInfo == FEMALE25TO29){
        if(willGoToWork(currDay, timeOfDay) && willMove(75)) return findIndexToMove(hasGenStore);
        if(willGoToSchool(currDay, timeOfDay) && willMove(15)) return findIndexToMove(hasSchool);//TODO no distinction between full and part time jobs
        if(inTimeRange(timeOfDay, 18, 24) && !isWeekDay(currDay) && willMove(45)) return findIndexToMove(hasEntertainment);
        if(inTimeRange(timeOfDay, 12,20) && willMove(25))return findIndexToMove(hasServices);
        if(inTimeRange(timeOfDay, 10, 18) && !isWeekDay(currDay) && willMove(20)) return findIndexToMove(hasParksAndRec);
    }
    else if(agentInfo == MALE30TO34 || agentInfo == FEMALE30TO34){
        return adultChanceOfMoving(currDay, timeOfDay, 85, 50, 55, 25, 25);
    }
    else if(agentInfo == MALE35TO39 || agentInfo == FEMALE35TO39){
        return adultChanceOfMoving(currDay, timeOfDay, 80, 70, 45, 25, 30);
    }
    else if(agentInfo == MALE40TO44 || agentInfo == FEMALE40TO44){
        return adultChanceOfMoving(currDay, timeOfDay,70, 85, 20, 35, 35);
    }
    else if(agentInfo == MALE45TO49 || agentInfo == FEMALE45TO49){
        return adultChanceOfMoving(currDay, timeOfDay, 65, 90, 15, 40, 25);
    }
    else if(agentInfo == MALE50TO54 || agentInfo == FEMALE50TO54){
        return adultChanceOfMoving(currDay, timeOfDay, 55, 90, 10, 45, 20);
    }
    else if(agentInfo == MALE55TO59 || agentInfo == FEMALE55TO59){
        return adultChanceOfMoving(currDay, timeOfDay, 50, 90, 10, 45, 20);
    }
    else if(agentInfo == MALE60TO64 || agentInfo == FEMALE60TO64){
        return adultChanceOfMoving(currDay, timeOfDay, 30, 70, 10, 50, 15);
    }
    else if(agentInfo == MALE65TO69 || agentInfo == FEMALE65TO69){
        return adultChanceOfMoving(currDay, timeOfDay, 25, 50, 10, 60, 20);
    }
    else if(agentInfo == MALE70TO74 || agentInfo == FEMALE70TO74){
        return adultChanceOfMoving(currDay, timeOfDay, 15, 30, 5, 60, 10);
    }
    else if(agentInfo == MALE75TO79 || agentInfo == FEMALE75TO79){
        return adultChanceOfMoving(currDay, timeOfDay, 5, 15, 5, 65, 5);
    }
    else if(agentInfo == MALE80TO84 || agentInfo == FEMALE80TO84){
        if(inTimeRange(timeOfDay, 10, 18) && !isWeekDay(currDay) && willMove(5)) return findIndexToMove(hasEntertainment);
        if(inTimeRange(timeOfDay, 9, 18) && willMove(80))return findIndexToMove(hasServices);
        if(inTimeRange(timeOfDay, 10, 18) && !isWeekDay(currDay) && willMove(5)) return findIndexToMove(hasParksAndRec);
    }
    else if(agentInfo == MALE85 || agentInfo == FEMALE85){

    }

    return findResidentialIndex(hasResidential);//default return
}

bool Transportation::isWeekDay(DayOfWeek currDay){
    return 0 <= currDay && currDay <= 4;
}

int Transportation::findIndexToMove(vector<Location*> toMoveList){
    return (monteCarloRandom(toMoveList.size()));
}

int Transportation::findResidentialIndex(vector<Location*> toMoveList){
    return (rand() % toMoveList.size());
}

bool Transportation::willMove(int percentChance){
    
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

int Transportation::adultChanceOfMoving(DayOfWeek currDay, int currTime, int genWork, int servWork, int goOut, int needServ, int goPark){
    if(willGoToWork(currDay, currTime) && willMove(genWork)) return findIndexToMove(hasGenStore);
    if(willGoToWork(currDay, currTime) && willMove(servWork)) return findIndexToMove(hasServices);
    if(inTimeRange(currTime, 18, 24) && !isWeekDay(currDay) && willMove(goOut)) return findIndexToMove(hasEntertainment);
    if(inTimeRange(currTime, 12,20) && willMove(needServ))return findIndexToMove(hasServices);
    if(inTimeRange(currTime, 10, 18) && !isWeekDay(currDay) && willMove(goPark)) return findIndexToMove(hasParksAndRec);
    return findResidentialIndex(hasResidential);
}

int Transportation::monteCarloRandom(int roof){
    int r1, r2;
    while(true){
        r1 = (int)(rand() % roof);
        r2 = (int)(rand() % roof);

        if(r2 <= r1) return r1;
    }
}
