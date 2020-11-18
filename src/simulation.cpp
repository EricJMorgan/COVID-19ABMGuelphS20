/****************
 * COVID-19ABMGuelphS20
 * 12/11/20
 * ver 2.03
 * 
 * This is the class file for the simulation class. This is where all of the classes come together
 * to run the actual simulation. This is in charge of setting up all the objects, and running each timestep
 * for the simulation, along with giving the results as outputs to both the frontend and the console.
 ***************/


#include "simulation.hh"
#include "agent.hh"
#include "transportation.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

// Constructor
Simulation::Simulation(string fileName) {
    //init vars and open a file
    ifstream demographicFile;
    demographicFile.open(fileName, ios::in);
    string line;
    //init values
    int arraySize = 0;
    population = 0;
    currTime = 0;
    hospitalTotal = 0;
    hospitalCurrent = 0;
    icuCurrent = 0;
    icuTotal = 0;
    timeStep = 4;
    recoveredTotal = 0;
    deceasedTotal = 0;
    newlyInfected = 0;
    sirTimeStep = (double)timeStep / 24.0;
    timeElapsed = 0;
    currDay = MON;
    initiallyInfectedChance = 0.0005;
    initiallyInfected = 0;

    //modular value setters
    for(int i = 0; i < 18; i++){
        agentRecoveryTime[i] = 0;
        agentIncubationTime[i] = 0;
        agentNeedsHospital[i] = 0;
        agentDeathChance[i] = 0;
        agentChanceOfICU[i] = 0;
        for(int j = 0; j < 4; j++){
            agentMitagationChance[i][j] = 0;
        }
    }
    for(int i = 0; i < 4; i++){
        mitagationEffectivness[i] = 0;
    }
    for(int i = 0; i < 9; i++){
        locationRisks[i] = 0;
    }
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                for(int l = 0; l < 9; l++){
                    agentChanceOfMovment[i][j][k][l] = 0;
                }
            }
        }
    }



    //make sure the file is valid
    if(!demographicFile.good()){
        cout << "Error invalid file" << endl;
        return;
    }

    getline(demographicFile, line);
    vector<string> csvValues;
    split(csvValues, line, boost::is_any_of(","));

    //loop while it is getting the gender statistic
    while(csvValues[0].compare("Gender") == 0){
        arraySize += stoi(csvValues[2]);
        getline(demographicFile, line);
        split(csvValues, line, boost::is_any_of(","));
    }

    simAgents = new Agent*[arraySize];
    demographicFile.close();

    population = arraySize;

    setUpAgents(fileName);

    locationInfo = new Transportation(simAgents, population);
}

Simulation::~Simulation(){
    for(int i = 0; i < agentCount; i++){
        delete simAgents[i];
    }
    delete[] simAgents;
    delete locationInfo;
}

int Simulation::getPopulation(){
    return population;
}

//This is where all the methods to update data are called for each 4 hour interval
void Simulation::simulateTimeStep(){
    // hospital timestep method calls
    guelphHospital.HospitalTimeStep(sirTimeStep, agentRecoveryTime, agentDeathChance, agentChanceOfICU);
    deceasedAgents.insert(deceasedAgents.end(), guelphHospital.newlyDeceased.begin(), guelphHospital.newlyDeceased.end());
    guelphHospital.newlyDeceased.clear();
    recoveredAgents.insert(recoveredAgents.end(), guelphHospital.newlyRecovered.begin(), guelphHospital.newlyRecovered.end());
    guelphHospital.newlyRecovered.clear();

    // isolation compartment timestep method calls
    isoCompartment.SimulateIsoTimeStep(sirTimeStep, agentRecoveryTime, agentNeedsHospital);
    recoveredAgents.insert(recoveredAgents.end(), isoCompartment.newlyRecovered.begin(), isoCompartment.newlyRecovered.end());
    isoCompartment.newlyRecovered.clear();
    for (int i = 0; i < (int)isoCompartment.newlyHospitalized.size(); i++) {
        guelphHospital.increaseHospitalCount(isoCompartment.newlyHospitalized[i]);
    }
    isoCompartment.newlyHospitalized.clear();

    Location *locationHolder;
    //gets each location and steps their time then checks if each agent will need the hospital
    for (int i = 0; i < (int)locationInfo->getLocationListLength(); i++) {
        locationInfo->getLocationAt(i)->locationTimeStep(agentMitagationChance, mitagationEffectivness, locationRisks);

        locationHolder = locationInfo->getLocationAt(i);
        for(int j = 0; j < locationHolder->getInfectedSize(); j++){
            if(locationHolder->getInfectedAgentAt(j)->randomAgentNeedsHospital(agentNeedsHospital)){
                guelphHospital.increaseHospitalCount(locationHolder->getInfectedAgentAt(j));
                locationHolder->removeInfectedAgent(j);//TODO this might skip over other agents
            }
            if(locationHolder->getInfectedAgentAt(j)->getSeverity() == INCUBATION) locationHolder->getInfectedAgentAt(j)->agentIncubationCheck(agentIncubationTime);

        }
    }
    
    
    // transport agents from location to location
    newlyInfected = locationInfo->simulateAgentMovment(currTime, currDay, agentChanceOfMovment);

    //update SIR totals
    deceasedTotal = (int)deceasedAgents.size();
    recoveredTotal = (int)recoveredAgents.size();
    infectedTotal += newlyInfected;
    infectedCurrent = infectedTotal - deceasedTotal - recoveredTotal;
    hospitalCurrent = guelphHospital.getTotalBeds();
    hospitalTotal = guelphHospital.getTotalHospitalCount();
    icuCurrent = guelphHospital.getIcuBeds();
    icuTotal = guelphHospital.getTotalICUCount();

    timeElapsed += timeStep;
    double daysTotal = (double)timeElapsed/24.0;

    //print to console for de-bugging
    cout << "Time elapsed: " << timeElapsed << " hours, " << daysTotal <<  " days" << endl;
    cout << "******************************" << endl;
    cout << "New cases " <<  newlyInfected << endl;
    cout << "Infected current " << infectedCurrent << endl;
    cout << "Infected total " << infectedTotal << endl;
    cout << "Deceased total " << deceasedTotal << endl;
    cout << "Recovered total " << recoveredTotal << endl;
    
    cout << "Hospital current " << hospitalCurrent << endl;
    cout << "Hospital total " << hospitalTotal << endl;

    cout << "ICU current " << icuCurrent << endl;
    cout << "ICU total " << icuTotal << endl;
    cout << "******************************" << endl;
    cout << endl;


    //increase time at end of day
    stepTime();
}

Agent *Simulation::getAgentAt(int index){
    if(index >= agentCount || index < 0){
        cerr << "ERROR INVALID INDEX" << endl;
        return NULL;
    }

    Agent *holder = simAgents[index];
    return holder;
}

/********************Private functions***************************************/
void Simulation::addNewAgent(string personInfo, int amountToAdd){
    //for the amount of agents in a demographic, add them to the agent list
    for(int i = 0; i < amountToAdd; i++){
        Agent* tempAgent = new Agent(AgentInfoMap[personInfo]);
        simAgents[agentCount] = tempAgent;
        double chanceInfected  = (double) rand()/RAND_MAX;
        if (chanceInfected < initiallyInfectedChance) {
            tempAgent->infectAgent();
            initiallyInfected++;
        }
        infectedCurrent = initiallyInfected;
        infectedTotal = initiallyInfected;
        agentCount++;
        tempAgent = NULL;
    }
}

void Simulation::setUpAgents(string filename) {

    //open file
    ifstream demographicFile;
    demographicFile.open(filename, ios::in);
    string line;
    agentCount = 0;

    if(!demographicFile.good()){
        cout << "Error invalid file" << endl;
        return;
    }

    //Get inital first line
    getline(demographicFile, line);
    vector<string> csvValues;
    split(csvValues, line, boost::is_any_of(","));

    //loop while it is getting the gender statistic
    while(csvValues[0].compare("Gender") == 0){
        addNewAgent(csvValues[1], stoi(csvValues[2]));
        getline(demographicFile, line);
        split(csvValues, line, boost::is_any_of(","));
    }

    demographicFile.close();
}


void Simulation::stepTime(){
    currTime += timeStep;
    if(currTime >= 24){
        currTime = 0;
        currDay = getNextDay(currDay);
    }
}

DayOfWeek Simulation::getNextDay(DayOfWeek oldDay){
    switch (oldDay){
        case MON:
            return TUE;
        case TUE:
            return WED;
        case WED:
            return THU;
        case THU:
            return FRI;
        case FRI:
            return SAT;
        case SAT:
            return SUN;
        case SUN:
            return MON;
        default:
            return MON;
    }
}

int Simulation::getInfectedCurrent() {
    return infectedCurrent;
}

int Simulation::getInfectedTotal() {
    return infectedTotal;
}

int Simulation::getDeceasedTotal() {
    return deceasedTotal;
}

int Simulation::getRecoveredTotal() {
    return recoveredTotal;
}

int Simulation::getHospitalTotal() {
    return hospitalTotal;
}

int Simulation::getHospitalCurrent() {
    return hospitalCurrent;
}

int Simulation::getICUtotal() {
    return icuTotal;
}

int Simulation::getICUCurrent() {
    return icuCurrent;
}

int Simulation::getNewlyInfected() {
    return newlyInfected;
}

void Simulation::setAgentMitagationChance(int ageGroup, int strategy, double value){
    agentMitagationChance[ageGroup][strategy] = value;
} 

void Simulation::setMitagationEffectivness(int strategy, double value){
    mitagationEffectivness[strategy] = value;
}

void Simulation::setLocationRisk(int location, double value){
    if(location < 0 || location > 8) return;
    if(value < 0 || value > 1.0) return;

    locationRisks[location] = value;
}

double Simulation::getAgentMitagationChance(int ageGroup, int strategy){
    return agentMitagationChance[ageGroup][strategy];
}

double Simulation::getMitagationEffectivness(int strategy){
    return mitagationEffectivness[strategy];
}

double Simulation::getLocationRisk(int location){
    if(location < 0 || location > 8) return -1;

    return locationRisks[location];
}

void Simulation::setAgentRecoveryTime(int ageRange, short value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 127) return;

    agentRecoveryTime[ageRange] = value;
}

void Simulation::setAgentDeathChance(int ageRange, double value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 1) return;
    agentDeathChance[ageRange] = value;
}

short Simulation::getAgentRecoveryTime(int ageRange){
    if(ageRange < 0 || ageRange > 17) return -1;
    return agentRecoveryTime[ageRange];
}

double Simulation::getAgentDeathChance(int ageRange){
    if(ageRange < 0 || ageRange > 17) return -1;
    return agentDeathChance[ageRange];
}

void Simulation::setAgentChanceOfMovment(int ageGroup, int day, int time, int location, double value){
    if(ageGroup < 0 || ageGroup > 17) return;
    if(day < 0 || day > 1) return;
    if(time < 0 || time > 24) return;
    if(location < 0 || location > 9) return;
    if(value < 0 || value > 1) return;

    agentChanceOfMovment[ageGroup][day][time][location] = value;
}

double Simulation::getAgentChanceOfMovment(int ageGroup, int day, int time, int location){
    if(ageGroup < 0 || ageGroup > 17) return-1;
    if(day < 0 || day > 1) return -1;
    if(time < 0 || time > 24) return -1;
    if(location < 0 || location > 9) return -1;

    return agentChanceOfMovment[ageGroup][day][time][location];
    
}

void Simulation::setAgentIncubationPeriod(int ageRange, short value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 127) return;

    agentIncubationTime[ageRange] = value;
}

short Simulation::getAgentIncubationPeriod(int ageRange){
    if(ageRange < 0 || ageRange > 17) return -1;

    return agentIncubationTime[ageRange];
}

void Simulation::setAgentNeedsHospital(int ageGroup, double chance){
    if(ageGroup < 0 || ageGroup > 17) return;
    if(chance < 0 || chance > 1) return;

    agentNeedsHospital[ageGroup] = chance;
}

double Simulation::getAgentNeedsHospital(int ageGroup){
    if(ageGroup < 0 || ageGroup > 17) return -1;

    return agentNeedsHospital[ageGroup];
}

void Simulation::setLocationRisks(int location, double value){
    if(location < 0 || location > 9) return;
    if(value < 0 || value > 1) return;

    locationRisks[location] = value;
}

double Simulation::getLocationRisks(int location){
    if(location < 0 || location > 8) return -1;

    return locationRisks[location];
}

void Simulation::setAgentChanceOfICU(int ageGroup, double value){
    if(ageGroup < 0 || ageGroup > 17) return;
    if(value < 0 || value > 1) return;

    agentChanceOfICU[ageGroup] = value;
}

double Simulation::getAgentChanceOfICU(int ageGroup){
    if(ageGroup < 0 || ageGroup > 17) return - 1;

    return agentChanceOfICU[ageGroup];
}

void Simulation::setAgentIncubationTime(int ageGroup, short value){
    if(ageGroup < 0 || ageGroup > 17) return;

    agentIncubationTime[ageGroup] = value;
}

short Simulation::getAgentIncubationTime(int ageGroup){
    if(ageGroup < 0 || ageGroup > 17) return -1;

    return agentIncubationTime[ageGroup];
}

void Simulation::simDayTimeStep(){
    for(int i = 0; i < 6; i++){
        simulateTimeStep();
    }
}

void Simulation::setPresets(int preset){
    switch(preset){
        case 0:

            break;

        default:
            break;
    }
}

void Simulation::setAnarchyPreset(){
    for(int i = 0; i < 5; i++){
        setMitagationEffectivness(i, 0);
        for(int j = 0; j < 18; j++){
            setAgentMitagationChance(j, i, 0);
        }
    }
    for(int i = 0; i < 9; i++){
        setLocationRisks(i, 1);
    }
    for(int i = 0; i < 18; i++){
        setAgentRecoveryTime(i, 127);
        setAgentChanceOfICU(i, 1);
        setAgentDeathChance(i, 1);
        setAgentIncubationTime(i, 127);
        setAgentNeedsHospital(i, 1);
    }
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                for(int l = 0; i < 9; i++){
                    setAgentChanceOfMovment(i, j, k, l, 1);
                }
            }
        }
    }

    //set chance to move to un-needed location to 0
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                setAgentChanceOfMovment(i, j, k, 8, 0);
            }
        }
    }
}

void Simulation::setRealWorldPreset(){

}

void Simulation::setTotalIsolation(){

}

void Simulation::setInformedPopulation(){
    //0 to 4
    setMitagationEffectivness(0, .95);
    setMitagationEffectivness(1, .85);
    setMitagationEffectivness(2, .8);
    setMitagationEffectivness(3, .99);
    setMitagationEffectivness(4, .95);
    
    //5 to 9
    setAgentMitagationChance(0, 0, 1);
    setAgentMitagationChance(0, 1, 0);//babies dont wear masks
    setAgentMitagationChance(0, 2, .1);
    setAgentMitagationChance(0, 3, .95);
    setAgentMitagationChance(0, 4, 1);

    //10 to 14
    setAgentMitagationChance(1, 0, .8);
    setAgentMitagationChance(1, 1, .9);
    setAgentMitagationChance(1, 2, .4);
    setAgentMitagationChance(1, 3, .5);
    setAgentMitagationChance(1, 4, 1);

    //14 to 19
    setAgentMitagationChance(2, 0, .9);
    setAgentMitagationChance(2, 1, 1);
    setAgentMitagationChance(2, 2, .7);
    setAgentMitagationChance(2, 3, .7);
    setAgentMitagationChance(2, 4, 1);

    //20 to 24
    setAgentMitagationChance(3, 0, .9);
    setAgentMitagationChance(3, 1, 1);
    setAgentMitagationChance(3, 2, .8);
    setAgentMitagationChance(3, 3, .85);
    setAgentMitagationChance(3, 4, 1);

    //25 to 85+, because pretty much every adult/senoir should be following these rules
    for(int i = 4; i < 18; i++){
        setAgentMitagationChance(i, 0, .9);
        setAgentMitagationChance(i, 1, 1);
        setAgentMitagationChance(i, 2, .8);
        setAgentMitagationChance(i, 3, .95);
        setAgentMitagationChance(i, 4, 1);
    }

    

}

void Simulation::setConspiracyPopulation(){

}

void Simulation::setRealWorldNoSchool(){
    setRealWorldPreset();
    //TODO add settings to remove in person school
}

void Simulation::setRealWorldNoVaccine(){
    setRealWorldPreset();
    //TODO add settings to remove all vaccines for virus
}

void Simulation::setDefaultLocationRisks(){
    setLocationRisks(GENSTORE, .6);
    setLocationRisks(TRANSPORT, .6);
    setLocationRisks(SCHOOL, .75);
    setLocationRisks(PARKSANDREC, .2);
    setLocationRisks(SERVICES, .6);
    setLocationRisks(ENTERTAINMENT, .82);
    setLocationRisks(HEALTH, .6);
    setLocationRisks(PLACEOFWORSHIP, .8);
    setLocationRisks(UNNEEDED, 0);
    setLocationRisks(RESIDENTIAL, .3);
}

void Simulation::setDefaultHospitalData(){
    //0 to 4
    setAgentRecoveryTime(0, 2);
    setAgentChanceOfICU(0, .01);
    setAgentDeathChance(0, .001);
    setAgentIncubationTime(0, 7);
    setAgentNeedsHospital(0, .001);

    //5 to 9
    setAgentRecoveryTime(1, 2);
    setAgentChanceOfICU(1, .01);
    setAgentDeathChance(1, .01);
    setAgentIncubationTime(1, 7);
    setAgentNeedsHospital(1, .01);

    //10 to 14
    setAgentRecoveryTime(2, 2);
    setAgentChanceOfICU(2, .01);
    setAgentDeathChance(2, .001);
    setAgentIncubationTime(2, 8);
    setAgentNeedsHospital(2, .1);

    //15 to 19
    setAgentRecoveryTime(0, 2);
    setAgentChanceOfICU(0, .01);
    setAgentDeathChance(0, .001);
    setAgentIncubationTime(0, 7);
    setAgentNeedsHospital(0, .001);
    
    
}