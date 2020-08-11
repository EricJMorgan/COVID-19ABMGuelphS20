/****************
 * COVID-19ABMGuelphS20
 * 05/08/20
 * ver 1.01
 * 
 * This is the class file for the simulation class
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
    ifstream demographicFile;
    demographicFile.open(fileName, ios::in);
    string line;
    int arraySize = 0;
    population = 0;
    currTime = 0;
    hospitalTotal = 0;
    timeStep = 4;
    sirTimeStep = (double)timeStep / 24.0;
    timeElapsed = 0;
    currDay = MON;
    initiallyInfectedChance = 0.001;
    initiallyInfected = 0;

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

    double locationRisk[9];
    // locationRisk[0] = genStoreRisk;
    locationRisk[1] = transportRisk;
    locationRisk[2] = schoolRisk;
    locationRisk[3] = parkRisk;
    locationRisk[4] = serviceRisk;
    locationRisk[5] = entertainmentRisk;
    locationRisk[6] = healthPlaceRisk;
    locationRisk[7] = placeOfWorshipRisk;
    locationRisk[8] = residentialRisk;

    setUpAgents(fileName);

    locationInfo = new Transportation(simAgents, population, socialDistancingSeverity, locationRisk);
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

void Simulation::simulateTimeStep(){
    // hospital
    guelphHospital.HospitalTimeStep(sirTimeStep);
    deceasedAgents.insert(deceasedAgents.end(), guelphHospital.newlyDeceased.begin(), guelphHospital.newlyDeceased.end());
    guelphHospital.newlyDeceased.clear();
    recoveredAgents.insert(recoveredAgents.end(), guelphHospital.newlyRecovered.begin(), guelphHospital.newlyRecovered.end());
    guelphHospital.newlyRecovered.clear();

    // isolation compartment
    isoCompartment.SimulateIsoTimeStep(sirTimeStep);
    recoveredAgents.insert(recoveredAgents.end(), isoCompartment.newlyRecovered.begin(), isoCompartment.newlyRecovered.end());
    isoCompartment.newlyRecovered.clear();
    for (int i = 0; i < (int)isoCompartment.newlyHospitalized.size(); i++) {
        guelphHospital.increaseHospitalCount(isoCompartment.newlyHospitalized[i]);
        hospitalTotal++;
    }
    isoCompartment.newlyHospitalized.clear();

    // agent sir time step
    for (int i = 0; i < (int)locationInfo->getLocationListLength(); i++) {
        for (int j = 0; j < (int)locationInfo->getLocationAt(i)->getInfected().size(); j++) {
            string sirResponse = locationInfo->getLocationAt(i)->getInfected()[j]->SIRTimeStep(sirTimeStep);
            if (sirResponse == "ISOAGENT") {
                Agent* toIsolate = locationInfo->getLocationAt(i)->removeInfectedAgent(j);
                isoCompartment.AddMildlyInfectedAgents(toIsolate);
                j--;
            } else if (sirResponse == "RECOVERAGENT") {
                Agent* recoveredAgent = locationInfo->getLocationAt(i)->removeInfectedAgent(j);
                isoCompartment.AddMildlyInfectedAgents(recoveredAgent);
                recoveredAgents.push_back(recoveredAgent);
                j--;
            }
        }
    }
    
    // transport agents and infect ppl
    int newlyInfected = locationInfo->simulateAgentMovment(currTime, currDay);

    deceasedTotal = (int)deceasedAgents.size();
    recoveredTotal = (int)recoveredAgents.size();
    infectedTotal += newlyInfected;
    infectedCurrent = infectedTotal - deceasedTotal - recoveredTotal;
    hospitalCurrent = guelphHospital.getTotalBeds() + guelphHospital.getIcuBeds();
    icuCurrent = guelphHospital.getIcuBeds();
    icuTotal = guelphHospital.getTotalICUCount();

    timeElapsed += timeStep;
    double daysTotal = (double)timeElapsed/24.0;
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


    stepTime();//increase time at end of day
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
}
void Simulation::setMaskCompliance(double val){
    maskCompliance = val;
}
void Simulation::setHygieneMaintainence(double val){
    hygieneMaintainence = val;
}

//location risks
void Simulation::setGenStoreRisk(double val){
    genStoreRisk = val;
}
void Simulation::setTransportRisk(double val){
    transportRisk = val;
}
void Simulation::setSchoolRisk(double val){
    schoolRisk = val;
}
void Simulation::setParkRisk(double val){
    parkRisk = val;
}
void Simulation::setServiceRisk(double val){
    serviceRisk = val;
}
void Simulation::setEntertainmentRisk(double val){
    entertainmentRisk = val;
}
void Simulation::setHealthPlaceRisk(double val){
    healthPlaceRisk = val;
}
void Simulation::setPlaceOfWorshipRisk(double val){
    placeOfWorshipRisk = val;
}
void Simulation::setResidentialRisk(double val){
    residentialRisk = val;
}

/********************Private functions***************************************/
void Simulation::addNewAgent(string personInfo, int amountToAdd){
    for(int i = 0; i < amountToAdd; i++){
        Agent* tempAgent = new Agent(AgentInfoMap[personInfo], maskCompliance, hygieneMaintainence);
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
    return icuTotal;
}