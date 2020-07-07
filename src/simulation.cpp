/****************
 * COVID-19ABMGuelphS20
 * 07/07/20
 * ver 0.02
 * 
 * This is the class file for the simulation class
 ***************/


#include "simulation.hh"
#include "agent.hh"
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/algorithm/string.hpp>

// Constructor
Simulation::Simulation() {
    simAgents = new Agent*[132000];
}
// Destructor
Simulation::~Simulation(){
    for(int i = 0; i < agentCount; i++){
        delete simAgents[i];
    }
    delete[] simAgents;
}

Agent Simulation::getAgentAt(int index){//TODO add error checking for array bounds
    Agent holder = Agent(simAgents[index]->getAgentInfo());
    return holder;
}

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
