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
    if(agentInfo== MALE0TO4 || agentInfo == FEMALE0TO4);
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
    }
    else if(agentInfo == MALE20TO24 || agentInfo == FEMALE20TO24){
        if(willGoToSchool(currDay, timeOfDay) && willMove(70)) return findIndexToMove(hasSchool);
    }
    else if(agentInfo == MALE25TO29 || agentInfo == FEMALE25TO29){

    }
    else if(agentInfo == MALE30TO34 || agentInfo == FEMALE30TO34){

    }
    else if(agentInfo == MALE35TO39 || agentInfo == FEMALE35TO39){

    }
    else if(agentInfo == MALE40TO44 || agentInfo == FEMALE40TO44){

    }
    else if(agentInfo == MALE45TO49 || agentInfo == FEMALE45TO49){

    }
    else if(agentInfo == MALE50TO54 || agentInfo == FEMALE50TO54){

    }
    else if(agentInfo == MALE55TO59 || agentInfo == FEMALE55TO59){

    }
    else if(agentInfo == MALE60TO64 || agentInfo == FEMALE60TO64){

    }
    else if(agentInfo == MALE65TO69 || agentInfo == FEMALE65TO69){

    }
    else if(agentInfo == MALE70TO74 || agentInfo == FEMALE70TO74){
        
    }
    else if(agentInfo == MALE75TO79 || agentInfo == FEMALE75TO79){

    }
    else if(agentInfo == MALE80TO84 || agentInfo == MALE80TO84){

    }
    else if(agentInfo == MALE85 || agentInfo == FEMALE85){

    }

    return findIndexToMove(hasResidential);//default return
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

bool Transportation::willGoToSchool(DayOfWeek currDay, int timeOfDay){//TODO students might move to multiple schools a day, might need a fix
    return isWeekDay(currDay) && (inTimeRange(timeOfDay, 8, 16));
}
// Agent *Transportation::moveSusceptibleToInfected(int locationIndex, int agentIndex){
//     if(locationIndex < 0 || locationIndex >= getLocationListLength()) return NULL;
//     if(agentIndex < 0 || agentIndex >= getLocationAt(locationIndex).getSusceptibleSize()) return NULL;

//     Agent *holder = locationList.at(locationIndex).removeSusceptibleAgent(agentIndex);
//     holder->AgentInfected();//TODO not sure if its ok to use SIR class here
//     locationList.at(locationIndex).addAgentToInfected(holder);
//     return holder;
// }