/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.05
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
    timeStep = 2;
    currDay = MON;

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

void Simulation::simulateTimeStep(){
    //TODO add agent movment and infection

    // agent sir time step
    // infection geographical time step infect
    // hospital
    // isolation compartment
    // transport agents

    stepTime();//increase time at end of day
}

Agent Simulation::getAgentAt(int index){
    if(index >= agentCount || index < 0){
        cerr << "ERROR INVALID INDEX" << endl;
        return Agent(MALE0TO4);
    }

    Agent holder = Agent(simAgents[index]->getAgentInfo());
    return holder;
}

/********************Private functions***************************************/
void Simulation::addNewAgent(string personInfo, int amountToAdd){
    for(int i = 0; i < amountToAdd; i++){
        Agent* tempAgent = new Agent(AgentInfoMap[personInfo]);
        simAgents[agentCount] = tempAgent;
        agentCount++;
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
