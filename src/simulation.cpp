/****************
 * COVID-19ABMGuelphS20
 * 15/07/20
 * ver 0.03
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
Simulation::Simulation(string fileName) {
    ifstream demographicFile;
    demographicFile.open(fileName, ios::in);
    string line;
    int arraySize = 0;
    population = 0;

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
    

}
// Destructor
Simulation::~Simulation(){
    for(int i = 0; i < agentCount; i++){
        delete simAgents[i];
    }
    delete[] simAgents;
}

/*************************
 * getAgentAt
 * 
 * Given the index of the agent this will get a copy of the agent at
 * the given location in the simAgents array
 * 
 * NOTE: must add error handling to function
 ************************/
Agent Simulation::getAgentAt(int index){//TODO add error checking for array bounds
    if(index >= agentCount || index < 0){
        cerr << "ERROR INVALID INDEX" << endl;
        return Agent(MALE0TO4);
    }

    Agent holder = Agent(simAgents[index]->getAgentInfo());
    return holder;
}

/*************************
 * addNewAgent
 * 
 * This adds a set of new agents to the arra
 ************************/
void Simulation::addNewAgent(string personInfo, int amountToAdd){
    for(int i = 0; i < amountToAdd; i++){
        Agent* tempAgent = new Agent(AgentInfoMap[personInfo]);
        simAgents[agentCount] = tempAgent;
        agentCount++;
    }
}


/*************************
 * setUpAgents
 * 
 * This takes in the filename and parses the file
 * and then places the data into the array
 ************************/
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

int Simulation::getPopulation(){
    return population;
}
