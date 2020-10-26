/****************
 * COVID-19ABMGuelphS20
 * 30/09/20
 * ver 1.04
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

    // agent sir timestep method calls
    for (int i = 0; i < (int)locationInfo->getLocationListLength(); i++) {
        for (int j = 0; j < (int)locationInfo->getLocationAt(i)->getInfected().size(); j++) {
            string sirResponse = locationInfo->getLocationAt(i)->getInfected()[j]->SIRTimeStep(sirTimeStep);
            if (sirResponse == "ISOAGENT") {
                Agent* toIsolate = locationInfo->getLocationAt(i)->removeInfectedAgent(j);
                isoCompartment.AddMildlyInfectedAgents(toIsolate);
                j--;
            } else if (sirResponse == "RECOVERAGENT") {
                Agent* recoveredAgent = locationInfo->getLocationAt(i)->removeInfectedAgent(j);
                recoveredTotal++;
                isoCompartment.AddMildlyInfectedAgents(recoveredAgent);
                recoveredAgents.push_back(recoveredAgent);
                j--;
            } else if (sirResponse == "HOSPITALAGENT") {
                Agent* hospitalAgent = locationInfo->getLocationAt(i)->removeInfectedAgent(j);
                guelphHospital.increaseHospitalCount(hospitalAgent);
                j--;
            }
        }
    }
    
    // transport agents from location to location
    newlyInfected = locationInfo->simulateAgentMovment(currTime, currDay);

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

//user input setters
void Simulation::setSocialDistancingSeverity(int val){
    socialDistancingSeverity = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisk);
}

void Simulation::setMaskCompliance(double val){
    maskCompliance = val;
    for (int i = 0; i < agentCount; i++) {
        simAgents[i]->DecideMigitationStrategy(maskCompliance, hygieneMaintainence);
    }
}

void Simulation::setQuarantineSeverity(double val) {
    for (int i = 0; i < agentCount; i++) {
        simAgents[i]->setQuarantineCases(val);
    }
}

void Simulation::setHygieneMaintainence(double val){
    hygieneMaintainence = val;
    for (int i = 0; i < agentCount; i++) {
        simAgents[i]->DecideMigitationStrategy(maskCompliance, hygieneMaintainence);
    }
}

// Age-specific setters
void Simulation::setAgentRecoveryTime(int ageRange, short val){ 
    guelphHospital.setAgentRecoveryTime(ageRange, val);
}

void Simulation::setAgentDeathChance(int ageRange, double val){ 
    guelphHospital.setAgentDeathChance(ageRange, val);
}

//location risks
void Simulation::setGenStoreRisk(double val){
    locationRisks[0] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setTransportRisk(double val){
    locationRisks[1] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setSchoolRisk(double val){
    locationRisks[2] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setParkRisk(double val){
    locationRisks[3] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setServiceRisk(double val){
    locationRisks[4] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setEntertainmentRisk(double val){
    locationRisks[5] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setHealthPlaceRisk(double val){
    locationRisks[6] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setPlaceOfWorshipRisk(double val){
    locationRisks[7] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}

void Simulation::setResidentialRisk(double val){
    locationRisks[8] = val;
    locationInfo->updateLocationRisks(socialDistancingSeverity, locationRisks);
}


/********************Private functions***************************************/
void Simulation::addNewAgent(string personInfo, int amountToAdd){
    //for the amount of agents in a demographic, add them to the agent list
    for(int i = 0; i < amountToAdd; i++){
        Agent* tempAgent = new Agent(AgentInfoMap[personInfo]);
        simAgents[agentCount] = tempAgent;
        double chanceInfected  = (double) rand()/RAND_MAX;
        if (chanceInfected < initiallyInfectedChance) {
            tempAgent->AgentInfected();
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
    if(ageGroup < 0 || ageGroup > 17) return;
    if(strategy < 0 || strategy > 3) return;
    if(value < 0 || value > 1) return;

    agentMitagationChance[ageGroup][strategy] = value;
} 

void Simulation::setMitagationEffectivness(int strategy, double value){
    if(strategy < 0 || strategy > 3) return;
    if(value < 0 || value > 1) return;

    mitagationEffectivness[strategy] = value;
}

void Simulation::setLocationRisk(int location, double value){
    if(location < 0 || location > 8) return;
    if(value < 0 || value > 1.0) return;

    locationRisks[location] = value;
}

double Simulation::getAgentMitagationChance(int ageGroup, int strategy){
    if(ageGroup < 0 || ageGroup > 17) return -1;
    if(strategy < 0 || strategy > 3) return -1;

    return agentMitagationChance[ageGroup][strategy];
}

double Simulation::getMitagationEffectivness(int strategy){
    if(strategy < 0 || strategy > 3) return -1;

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

