/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the class file for the simulation class
 ***************/


#include "simulation.hh"
#include "agent.hh"
#include <iostream>
#include <fstream>

// Constructor
Simulation::Simulation() {

}

void Simulation::setUpAgents(string filename) {
    ifstream demographicFile;
    demographicFile.open(filename, ios::in);
    string line;
    string agegroup;

    int agentCount = 0;

    getline(demographicFile, line, ',');
    
    while (line.compare("Gender") == 0) {
        getline(demographicFile, agegroup, ',');
        getline(demographicFile, line, ',');
        if (agegroup.compare("Male 0-4") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE0TO4, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 5-9") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE5TO9, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 10-14") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE10TO14, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 15-19") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE15TO19, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 20-24") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE20TO24, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 25-29") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE25TO29, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 30-34") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE30TO34, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 35-39") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE35TO39, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 40-44") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE40TO44, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 45-49") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE45TO49, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 50-54") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE50TO54, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 55-59") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE55TO59, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 60-64") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE60TO64, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 65-59") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE65TO69, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 70-74") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE70TO74, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 75-79") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE75TO79, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 80-84") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE80TO84, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Male 85+") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(MALE85, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 0-4") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE0TO4, "Female");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 5-9") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE0TO4, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 10-14") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE5TO9, "Female");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 15-19") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE15TO19, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 20-24") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE20TO24, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 25-29") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE25TO29, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 30-34") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE30TO34, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 35-39") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE35TO39, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 40-44") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE40TO44, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 45-49") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE45TO49, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 50-54") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE50TO54, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 55-59") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE55TO59, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 60-64") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE60TO64, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 65-59") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE65TO69, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 70-74") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE70TO74, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 75-79") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE75TO79, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 80-84") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE80TO84, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        } else if (agegroup.compare("Female 85+") == 0) {
            for (size_t i = 0; i < std::stoi(line); i++) {
                Agent* tempAgent = new Agent(FEMALE85, "Male");
                simAgents[agentCount] = tempAgent;
                agentCount++;
            }
        }
    
        getline(demographicFile, line, ',');
    }
    
    demographicFile.close();
}
