/****************
 * COVID-19ABMGuelphS20
 * 27/11/20
 * ver 2.04
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
    srand(time(NULL));
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
    initiallyInfectedChance = 0.00035;
    initiallyInfected = 0;

    //modular value setters
    for(int i = 0; i < 18; i++){
        agentRecoveryTime[i] = 0;
        agentIncubationTime[i] = 0;
        agentNeedsHospital[i] = 0;
        agentDeathChance[i] = 0;
        agentChanceOfICU[i] = 0;
        for(int j = 0; j < 5; j++){
            agentMitagationChance[i][j] = 0;
        }
    }
    for(int i = 0; i < 5; i++){
        mitagationEffectivness[i] = 0;
    }
    for(int i = 0; i < 10; i++){
        locationRisks[i] = 0;
    }
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                for(int l = 0; l < 10; l++){
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

    cout << "infected total: " << getInfectedTotal() << "\n";
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
    
    /* This section of codes updates the status 
       of agents that are currently in the hospital 
    */

    // hospital timestep method calls
    guelphHospital.HospitalTimeStep(sirTimeStep, agentRecoveryTime, agentDeathChance, agentChanceOfICU);
    deceasedAgents.insert(deceasedAgents.end(), guelphHospital.newlyDeceased.begin(), guelphHospital.newlyDeceased.end());
    guelphHospital.newlyDeceased.clear();
    recoveredAgents.insert(recoveredAgents.end(), guelphHospital.newlyRecovered.begin(), guelphHospital.newlyRecovered.end());//TODO distibute recoverd Agents into locations
    guelphHospital.newlyRecovered.clear();


    /* This section of code updates the status 
       of agents that are in isolation 
    */

    // isolation compartment timestep method calls
    isoCompartment.SimulateIsoTimeStep(sirTimeStep, agentRecoveryTime, agentNeedsHospital);
    recoveredAgents.insert(recoveredAgents.end(), isoCompartment.newlyRecovered.begin(), isoCompartment.newlyRecovered.end());
    isoCompartment.newlyRecovered.clear();
    for (int i = 0; i < (int)isoCompartment.newlyHospitalized.size(); i++) {
        guelphHospital.increaseHospitalCount(isoCompartment.newlyHospitalized[i]);
    }
    isoCompartment.newlyHospitalized.clear();


    /* Each location will be checked to see if agents need to be moved into the hospital
        This is currently done in the following process:
        1. Loop through each location
        2. For reach location get the number of infected agents
        3. For each infected agent at that location we check and see if the agent needs to go to the hospital
        4. If the agent does need to go to the hospital they are removed from the infected list and placed in the hospital list
        5. Once all infected agents are checked for hospital status we then check and see if each agent needs a status update
            5.1) It is checked if each agent has been in incubation long enough to now be infected
            5.2) Then if the agent has been infected long enough to now recover
    */

    Location *locationHolder;
    //gets each location and steps their time then checks if each agent will need the hospital
    for (int i = 0; i < locationInfo->getLocationListLength(); i++) {
        //locationInfo->getLocationAt(i)->locationTimeStep(agentMitagationChance, mitagationEffectivness, locationRisks);//TODO this is usless atm but may be needed later
        locationHolder = locationInfo->getLocationAt(i);

        // loop through all agents at a given location
        for(int j = 0; j < locationHolder->getInfectedSize(); j++){

            if(locationHolder->getInfectedAgentAt(j)->getSeverity() == INCUBATION){
                //check if agent is past incubation time and into infected time
                locationHolder->getInfectedAgentAt(j)->agentIncubationCheck(agentIncubationTime);

                // check to see if an incubating agent will be entering isolation
                if( (double)rand() / (double)RAND_MAX > 0.50) {
                    isoCompartment.AddMildlyInfectedAgents(locationHolder->getInfectedAgentAt(j));
                    locationHolder->removeInfectedAgent(j);
                    j--;
                    continue;
                }

            }else if(locationHolder->getInfectedAgentAt(j)->getSeverity() == INFECTED){

                //check to see if an infected agent will be entering isolation

                //check to see if every single infected agent who has not yet completed a agentHopsitalRoll needs to go to the hospital
                if(locationHolder->getInfectedAgentAt(j)->getAgentHospitalRoll() == -1){
                    if(locationHolder->getInfectedAgentAt(j)->randomAgentNeedsHospital(agentNeedsHospital)){
                        locationHolder->getInfectedAgentAt(j)->setAgentHospitalRoll(1); // TODO: DEFAULT VALUE OF 1 SET, this should be the number of timesteps until hospital 
                        
                        // TODO Currently all infected agents are moved to the hospital immediately, this needs to be updated to insertion over time
                        guelphHospital.increaseHospitalCount(locationHolder->getInfectedAgentAt(j));
                        locationHolder->removeInfectedAgent(j);//TODO this might skip over other agents
                        j--;
                        continue;
                    }else{
                        // if the roll fails then the agent will not be going to the hospital during the simulation
                        locationHolder->getInfectedAgentAt(j)->setAgentHospitalRoll(0);
                    }
                }

                //check if agent is past infected time and into recoverd time
                locationHolder->getInfectedAgentAt(j)->agentInfectedCheck(agentRecoveryTime);

            // if agent is recovered we wat to remove them from the infected list               
            }else if(locationHolder->getInfectedAgentAt(j)->getSeverity() == RECOVERED){
                    recoveredAgents.insert( recoveredAgents.end(), locationHolder->removeInfectedAgent(j));//TODO this could be an issue
                }
            }
        }
    
    /* Finally we check to see if the agents are going to move from
       one location to another during the timestep.
    */
    newlyInfected = locationInfo->simulateAgentMovement(currTime, currDay, agentChanceOfMovment, agentMitagationChance, mitagationEffectivness, locationRisks);

    cout << "newly infected: " << newlyInfected << "\n";

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



    //print to log file for each timestep
    ofstream logFile;
    logFile.open("Results.txt", std::ios::app);

    logFile << "Time elapsed: " << timeElapsed << " hours, " << daysTotal <<  " days" << endl;
    logFile << "******************************" << endl;
    logFile << "New cases " <<  newlyInfected << endl;
    logFile << "Infected current " << infectedCurrent << endl;
    logFile << "Infected total " << infectedTotal << endl;
    logFile << "Deceased total " << deceasedTotal << endl;
    logFile << "Recovered total " << recoveredTotal << endl;
    
    logFile << "Hospital current " << hospitalCurrent << endl;
    logFile << "Hospital total " << hospitalTotal << endl;

    logFile << "ICU current " << icuCurrent << endl;
    logFile << "ICU total " << icuTotal << endl;
    logFile << "******************************" << endl;
    logFile << endl;

    logFile.close();

    //increase time at end of day
    stepTime();
}

void Simulation::simDayTimeStep(){
    for(int i = 0; i < 6; i++){
        simulateTimeStep();
    }
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

void Simulation::setAgentRecoveryTime(int ageRange, int value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 127) return;

    agentRecoveryTime[ageRange] = value;
}

void Simulation::setAgentDeathChance(int ageRange, double value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 1) return;
    agentDeathChance[ageRange] = value;
}

int Simulation::getAgentRecoveryTime(int ageRange){
    if(ageRange < 0 || ageRange > 17) return -1;
    return agentRecoveryTime[ageRange];
}

double Simulation::getAgentDeathChance(int ageRange){
    if(ageRange < 0 || ageRange > 17) return -1;
    return agentDeathChance[ageRange];
}

void Simulation::setAgentChanceOfMovment(int ageGroup, int day, int time, int location, double value){
    if(ageGroup < 0 || ageGroup > 17){
        cout << "bad age\n"; 
        return;
    }
    if(day < 0 || day > 1){
        cout << "bad day\n"; 
        return;
    } 
    if(time < 0 || time > 24){
        cout << "bad time\n"; 
        return;
    }
    if(location < 0 || location > 9){
        cout << "bad location\n";
        return;
    } 
    if(value < 0 || value > 1) {
        cout << "bad value\n"; 
        return;
    }

    agentChanceOfMovment[ageGroup][day][time][location] = value;
}

double Simulation::getAgentChanceOfMovment(int ageGroup, int day, int time, int location){
    if(ageGroup < 0 || ageGroup > 17) return-1;
    if(day < 0 || day > 1) return -1;
    if(time < 0 || time > 24) return -1;
    if(location < 0 || location > 9) return -1;

    return agentChanceOfMovment[ageGroup][day][time][location];
    
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

void Simulation::setLocationRisk(int location, double value){
    if(location < 0 || location > 8) return;
    if(value < 0 || value > 1.0) return;

    locationRisks[location] = value;
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

void Simulation::setAgentIncubationTime(int ageGroup, int value){
    if(ageGroup < 0 || ageGroup > 17) return;

    agentIncubationTime[ageGroup] = value;
}

int Simulation::getAgentIncubationTime(int ageGroup){
    if(ageGroup < 0 || ageGroup > 17) return -1;

    return agentIncubationTime[ageGroup];
}

int Simulation::saveCurrentPreset(int fileNum){

    ofstream newFile;
    newFile.open("simulationValues.csv");

    cout << "successfully opened file \n";
    //add agent mitagation chance to file each row denoting an ageGroup
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 5; j++){
            newFile << agentMitagationChance[i][j];
            if(j != 4) newFile << ",";
        }
        newFile << "\n";
    }

    newFile << "-Mitigation Effectiveness-\n";
    for(int i = 0; i < 4; i++){
        newFile << mitagationEffectivness[i] << ",";
    }
    newFile << mitagationEffectivness[4] << "\n-Location Risks-\n";

    for(int i = 0; i < 8; i++){
        newFile << locationRisks[i] << ",";
    }
    newFile << locationRisks[8] << "\n-Agent Recovery Time-\n";

    for(int i = 0; i < 17; i++){
        newFile <<  agentRecoveryTime[i] << ",";
    }
    newFile <<  agentRecoveryTime[17] << "\n-Agent Incubation Time-\n";

    for(int i = 0; i < 17; i++){
        newFile <<  agentIncubationTime[i] << ",";
    }
    newFile <<  agentIncubationTime[17] << "\n-Agent Hospital Chance-\n";

    for(int i = 0; i < 17; i++){
        newFile <<  agentNeedsHospital[i] << ",";
    }
    newFile <<  agentNeedsHospital[17] << "\n-Agent Death Chance-\n";

    for(int i = 0; i < 17; i++){
        newFile <<  agentDeathChance[i] << ",";
    }
    newFile <<  agentDeathChance[17] << "\n-Agent ICU Chance-\n";

    for(int i = 0; i < 17; i++){
        newFile <<  agentChanceOfICU[i] << ",";
    }
    newFile <<  agentChanceOfICU[17] << "\n-Agent Chance of movement-\n";

    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                // save the location movement chances for each agent for given age, weekday status, and time of day
                newFile << i << ",";
                newFile << j << ",";
                newFile << k << ",";
                newFile << agentChanceOfMovment[i][j][k][0] << ",";
                newFile << agentChanceOfMovment[i][j][k][1] << ",";
                newFile << agentChanceOfMovment[i][j][k][2] << ",";
                newFile << agentChanceOfMovment[i][j][k][3] << ",";
                newFile << agentChanceOfMovment[i][j][k][4] << ",";
                newFile << agentChanceOfMovment[i][j][k][5] << ",";
                newFile << agentChanceOfMovment[i][j][k][6] << ",";
                newFile << agentChanceOfMovment[i][j][k][7] << ",";
                newFile << agentChanceOfMovment[i][j][k][8] << "\n";
            }
        }
    }
    newFile.close();
    cout << "file writing complete \n";
    return 5;
}

void Simulation::setPresets(int preset){
    switch(preset){
        case 0:
            setRealWorldPreset();
            break;
        case 1:
            setAnarchyPreset();
            break;
        case 2:
            setInformedPopulation();
            break;
        case 3:
            setConspiracyPopulation();
            break;
        case 4:
            setRealWorldNoSchool();
            break;
        case 5:
            setRealWorldNoVaccine();
            break;
        default:
            setRealWorldPreset();
            break;
    }
    cout << "Pre-set complete\n";
}

void Simulation::setRealWorldPreset(){
    //0 to 4
    setAgentMitagationChance(0, 0, .8);
    setAgentMitagationChance(0, 1, 0);//babies dont wear masks
    setAgentMitagationChance(0, 2, .1);
    setAgentMitagationChance(0, 3, .85);
    setAgentMitagationChance(0, 4, .6);

    //5 to 9
    setAgentMitagationChance(1, 0, .8);
    setAgentMitagationChance(1, 1, .9);
    setAgentMitagationChance(1, 2, .6);
    setAgentMitagationChance(1, 3, .5);
    setAgentMitagationChance(1, 4, .8);

    //10 to 14
    setAgentMitagationChance(2, 0, .8);
    setAgentMitagationChance(2, 1, .8);
    setAgentMitagationChance(2, 2, .8);
    setAgentMitagationChance(2, 3, .8);
    setAgentMitagationChance(2, 4, .9);

    //15 to 19
    setAgentMitagationChance(3, 0, .6);
    setAgentMitagationChance(3, 1, .8);
    setAgentMitagationChance(3, 2, .8);
    setAgentMitagationChance(3, 3, .85);
    setAgentMitagationChance(3, 4, .8);

    //25 to 85+, because pretty much every adult/senoir should be following these rules
    for(int i = 4; i < 18; i++){
        setAgentMitagationChance(i, 0, .8);
        setAgentMitagationChance(i, 1, .8);
        setAgentMitagationChance(i, 2, .75);
        setAgentMitagationChance(i, 3, .75);
        setAgentMitagationChance(i, 4, .9);
    }

    setDefaultMovementData();
    setDefaultHospitalData();
    setDefaultLocationRisks();
    setDefaultMitagationEffectivness();
}

void Simulation::setAnarchyPreset(){
    for(int i = 0; i < 5; i++){
        setMitagationEffectivness(i, 0);
        for(int j = 0; j < 18; j++){
            setAgentMitagationChance(j, i, 0);
        }
    }
    for(int i = 0; i < 9; i++){
        setLocationRisk(i, 1);
    }
    for(int i = 0; i < 18; i++){
        setAgentRecoveryTime(i, 127);
        setAgentChanceOfICU(i, 1);
        setAgentDeathChance(i, 1);
        setAgentIncubationTime(i, 1);
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

void Simulation::setInformedPopulation(){  
    //0 to 4
    setAgentMitagationChance(0, 0, 1);
    setAgentMitagationChance(0, 1, 0);//babies dont wear masks
    setAgentMitagationChance(0, 2, .1);
    setAgentMitagationChance(0, 3, .95);
    setAgentMitagationChance(0, 4, 1);

    //5 to 9
    setAgentMitagationChance(1, 0, .8);
    setAgentMitagationChance(1, 1, .9);
    setAgentMitagationChance(1, 2, .4);
    setAgentMitagationChance(1, 3, .5);
    setAgentMitagationChance(1, 4, 1);

    //10 to 14
    setAgentMitagationChance(2, 0, .9);
    setAgentMitagationChance(2, 1, 1);
    setAgentMitagationChance(2, 2, .7);
    setAgentMitagationChance(2, 3, .7);
    setAgentMitagationChance(2, 4, 1);

    //15 to 19
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

    setDefaultLocationRisks();
    setDefaultHospitalData();
    setDefaultMitagationEffectivness();
    setDefaultMovementData();
}

void Simulation::setConspiracyPopulation(){
    //0 to 4
    setAgentMitagationChance(0, 0, .3);
    setAgentMitagationChance(0, 1, 0);//babies dont wear masks
    setAgentMitagationChance(0, 2, .1);
    setAgentMitagationChance(0, 3, .4);
    setAgentMitagationChance(0, 4, .02);

    //5 to 9
    setAgentMitagationChance(1, 0, .3);
    setAgentMitagationChance(1, 1, .1);
    setAgentMitagationChance(1, 2, .2);
    setAgentMitagationChance(1, 3, .4);
    setAgentMitagationChance(1, 4, .02);

    //10 to 14
    setAgentMitagationChance(2, 0, .3);
    setAgentMitagationChance(2, 1, .2);
    setAgentMitagationChance(2, 2, .3);
    setAgentMitagationChance(2, 3, .3);
    setAgentMitagationChance(2, 4, .05);

    //15 to 19
    setAgentMitagationChance(3, 0, .35);
    setAgentMitagationChance(3, 1, .2);
    setAgentMitagationChance(3, 2, .2);
    setAgentMitagationChance(3, 3, .3);
    setAgentMitagationChance(3, 4, .05);

    //25 to 85+, because pretty much every adult/senoir should be following these rules
    for(int i = 4; i < 18; i++){
        setAgentMitagationChance(i, 0, .3);
        setAgentMitagationChance(i, 1, .1);
        setAgentMitagationChance(i, 2, .2);
        setAgentMitagationChance(i, 3, .3);
        setAgentMitagationChance(i, 4, .05);//Some people really just hate vaccines
    }

    setDefaultMovementData();
    setDefaultLocationRisks();
    setDefaultHospitalData();
    setDefaultMitagationEffectivness();  
}

void Simulation::setRealWorldNoSchool(){
    setRealWorldPreset();

    //set every agents chance to move to a school 0
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                setAgentChanceOfMovment(i, j, k, 2, 0);
            }
        }
    }
}

void Simulation::setRealWorldNoVaccine(){
    setRealWorldPreset();

    //set every agents chance to have a vaccine to 0 to simulate no vaccines
    for(int i = 0; i < 18; i++){
        setAgentMitagationChance(i, 4, 0);
    }
}

void Simulation::setDefaultLocationRisks(){
    setLocationRisk(GENSTORE, .6);
    setLocationRisk(TRANSPORT, .6);
    setLocationRisk(SCHOOL, .75);
    setLocationRisk(PARKSANDREC, .2);
    setLocationRisk(SERVICES, .6);
    setLocationRisk(ENTERTAINMENT, .82);
    setLocationRisk(HEALTH, .6);
    setLocationRisk(PLACEOFWORSHIP, .8);
    setLocationRisk(UNNEEDED, 0);
    setLocationRisk(RESIDENTIAL, .3);
}

void Simulation::setDefaultMitagationEffectivness(){
    setMitagationEffectivness(0, .95);
    setMitagationEffectivness(1, .95);
    setMitagationEffectivness(2, .95);
    setMitagationEffectivness(3, .99);
    setMitagationEffectivness(4, .99);
}

void Simulation::setDefaultHospitalData(){
    //0 to 4
    setAgentRecoveryTime(0, 2);
    setAgentChanceOfICU(0, .01);
    setAgentDeathChance(0, .001);
    setAgentIncubationTime(0, 7);
    setAgentNeedsHospital(0, .001);

    //5 to 9
    setAgentRecoveryTime(1, 3);
    setAgentChanceOfICU(1, .01);
    setAgentDeathChance(1, .01);
    setAgentIncubationTime(1, 7);
    setAgentNeedsHospital(1, .01);

    //10 to 14
    setAgentRecoveryTime(2, 5);
    setAgentChanceOfICU(2, .01);
    setAgentDeathChance(2, .001);
    setAgentIncubationTime(2, 8);
    setAgentNeedsHospital(2, .01);

    //15 to 19
    setAgentRecoveryTime(3, 7);
    setAgentChanceOfICU(3, .01);
    setAgentDeathChance(3, .01);
    setAgentIncubationTime(3, 10);
    setAgentNeedsHospital(3, .01);

    //20 to 44
    for(int i = 4; i < 9; i++){
        setAgentRecoveryTime(i, 14);
        setAgentChanceOfICU(i, .15);
        setAgentDeathChance(i, .01);
        setAgentIncubationTime(i, 10);
        setAgentNeedsHospital(i, .03);
    }

    //45 to 64
    for(int i = 9; i < 13; i++){
        setAgentRecoveryTime(i, 14);
        setAgentChanceOfICU(i, .25);
        setAgentDeathChance(i, .04);
        setAgentIncubationTime(i, 10);
        setAgentNeedsHospital(i, .08);
    }

    //65 to 85+
    for(int i = 13; i < 18; i++){
        setAgentRecoveryTime(i, 14);
        setAgentChanceOfICU(i, .25);
        setAgentDeathChance(i, .15);
        setAgentIncubationTime(i, 10);
        setAgentNeedsHospital(i, .10);
    }

    cout << "in function: " << getAgentIncubationTime(3) << "\n";
    
}

//please have mercy on me
void Simulation::setDefaultMovementData(){
    for(int i = 0; i < 18; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 6; k++){
                setAgentChanceOfMovment(i, j, k, 8, 0);
            }
        }
    }
    //0 to 4
    for(int i = 0; i < 2; i++){
        setAgentChanceOfMovment(0, i, 0, 0, .01);
        setAgentChanceOfMovment(0, i, 1, 0, .01);
        setAgentChanceOfMovment(0, i, 2, 0, .05);
        setAgentChanceOfMovment(0, i, 3, 0, .1);
        setAgentChanceOfMovment(0, i, 4, 0, .05);
        setAgentChanceOfMovment(0, i, 5, 0, .01);
        setAgentChanceOfMovment(0, i, 0, 1, .01);
        setAgentChanceOfMovment(0, i, 1, 1, .01);
        setAgentChanceOfMovment(0, i, 2, 1, .05);
        setAgentChanceOfMovment(0, i, 3, 1, .1);
        setAgentChanceOfMovment(0, i, 4, 1, .05);
        setAgentChanceOfMovment(0, i, 5, 1, .01);
        setAgentChanceOfMovment(0, i, 0, 2, 0);
        setAgentChanceOfMovment(0, i, 1, 2, 0);
        setAgentChanceOfMovment(0, i, 2, 2, 0);
        setAgentChanceOfMovment(0, i, 3, 2, 0);
        setAgentChanceOfMovment(0, i, 4, 2, 0);
        setAgentChanceOfMovment(0, i, 5, 2, 0);
        setAgentChanceOfMovment(0, i, 0, 3, 0);
        setAgentChanceOfMovment(0, i, 1, 3, 0);
        setAgentChanceOfMovment(0, i, 2, 3, .01);
        setAgentChanceOfMovment(0, i, 3, 3, .05);
        setAgentChanceOfMovment(0, i, 4, 3, .01);
        setAgentChanceOfMovment(0, i, 5, 3, 0);
        setAgentChanceOfMovment(0, i, 0, 4, .01);
        setAgentChanceOfMovment(0, i, 1, 4, .01);
        setAgentChanceOfMovment(0, i, 2, 4, .05);
        setAgentChanceOfMovment(0, i, 3, 4, .1);
        setAgentChanceOfMovment(0, i, 4, 4, .05);
        setAgentChanceOfMovment(0, i, 5, 4, .01);
        setAgentChanceOfMovment(0, i, 0, 5, .01);
        setAgentChanceOfMovment(0, i, 1, 5, .01);
        setAgentChanceOfMovment(0, i, 2, 5, .05);
        setAgentChanceOfMovment(0, i, 3, 5, .1);
        setAgentChanceOfMovment(0, i, 4, 5, .05);
        setAgentChanceOfMovment(0, i, 5, 5, .01);
        setAgentChanceOfMovment(0, i, 0, 6, .05);
        setAgentChanceOfMovment(0, i, 1, 6, .08);
        setAgentChanceOfMovment(0, i, 2, 6, .1);
        setAgentChanceOfMovment(0, i, 3, 6, .04);
        setAgentChanceOfMovment(0, i, 4, 6, .02);
        setAgentChanceOfMovment(0, i, 5, 6, .01);
        setAgentChanceOfMovment(0, i, 0, 7, .01);
        setAgentChanceOfMovment(0, i, 1, 7, .01);
        setAgentChanceOfMovment(0, i, 2, 7, .01);
        setAgentChanceOfMovment(0, i, 3, 7, .01);
        setAgentChanceOfMovment(0, i, 4, 7, .01);
        setAgentChanceOfMovment(0, i, 5, 7, .01);
        setAgentChanceOfMovment(0, i, 0, 9, .95);
        setAgentChanceOfMovment(0, i, 1, 9, .9);
        setAgentChanceOfMovment(0, i, 2, 9, .8);
        setAgentChanceOfMovment(0, i, 3, 9, .8);
        setAgentChanceOfMovment(0, i, 4, 9, .9);
        setAgentChanceOfMovment(0, i, 5, 9, .95);
    }
    //5 to 9
    setAgentChanceOfMovment(1, 0, 0, 0, .01);
    setAgentChanceOfMovment(1, 0, 1, 0, .01);
    setAgentChanceOfMovment(1, 0, 2, 0, .05);
    setAgentChanceOfMovment(1, 0, 3, 0, .1);
    setAgentChanceOfMovment(1, 0, 4, 0, .05);
    setAgentChanceOfMovment(1, 0, 5, 0, .01);
    setAgentChanceOfMovment(1, 0, 0, 1, .01);
    setAgentChanceOfMovment(1, 0, 1, 1, .01);
    setAgentChanceOfMovment(1, 0, 2, 1, .05);
    setAgentChanceOfMovment(1, 0, 3, 1, .1);
    setAgentChanceOfMovment(1, 0, 4, 1, .05);
    setAgentChanceOfMovment(1, 0, 5, 1, .01);
    setAgentChanceOfMovment(1, 0, 0, 2, 0);
    setAgentChanceOfMovment(1, 0, 1, 2, 0);
    setAgentChanceOfMovment(1, 0, 2, 2, .9);
    setAgentChanceOfMovment(1, 0, 3, 2, .9);
    setAgentChanceOfMovment(1, 0, 4, 2, .5);
    setAgentChanceOfMovment(1, 0, 5, 2, 0);
    setAgentChanceOfMovment(1, 0, 0, 3, 0);
    setAgentChanceOfMovment(1, 0, 1, 3, 0);
    setAgentChanceOfMovment(1, 0, 2, 3, .01);
    setAgentChanceOfMovment(1, 0, 3, 3, .05);
    setAgentChanceOfMovment(1, 0, 4, 3, .01);
    setAgentChanceOfMovment(1, 0, 5, 3, 0);
    setAgentChanceOfMovment(1, 0, 0, 4, .01);
    setAgentChanceOfMovment(1, 0, 1, 4, .01);
    setAgentChanceOfMovment(1, 0, 2, 4, .05);
    setAgentChanceOfMovment(1, 0, 3, 4, .1);
    setAgentChanceOfMovment(1, 0, 4, 4, .05);
    setAgentChanceOfMovment(1, 0, 5, 4, .01);
    setAgentChanceOfMovment(1, 0, 0, 5, .01);
    setAgentChanceOfMovment(1, 0, 1, 5, .01);
    setAgentChanceOfMovment(1, 0, 2, 5, .05);
    setAgentChanceOfMovment(1, 0, 3, 5, .1);
    setAgentChanceOfMovment(1, 0, 4, 5, .05);
    setAgentChanceOfMovment(1, 0, 5, 5, .01);
    setAgentChanceOfMovment(1, 0, 0, 6, .05);
    setAgentChanceOfMovment(1, 0, 1, 6, .08);
    setAgentChanceOfMovment(1, 0, 2, 6, .1);
    setAgentChanceOfMovment(1, 0, 3, 6, .04);
    setAgentChanceOfMovment(1, 0, 4, 6, .02);
    setAgentChanceOfMovment(1, 0, 5, 6, .01);
    setAgentChanceOfMovment(1, 0, 0, 7, .01);
    setAgentChanceOfMovment(1, 0, 1, 7, .01);
    setAgentChanceOfMovment(1, 0, 2, 7, .01);
    setAgentChanceOfMovment(1, 0, 3, 7, .01);
    setAgentChanceOfMovment(1, 0, 4, 7, .01);
    setAgentChanceOfMovment(1, 0, 5, 7, .01);
    setAgentChanceOfMovment(1, 0, 0, 9, .95);
    setAgentChanceOfMovment(1, 0, 1, 9, .9);
    setAgentChanceOfMovment(1, 0, 2, 9, .8);
    setAgentChanceOfMovment(1, 0, 3, 9, .8);
    setAgentChanceOfMovment(1, 0, 4, 9, .9);
    setAgentChanceOfMovment(1, 0, 5, 9, .95);
    setAgentChanceOfMovment(1, 1, 0, 0, .01);
    setAgentChanceOfMovment(1, 1, 1, 0, .01);
    setAgentChanceOfMovment(1, 1, 2, 0, .05);
    setAgentChanceOfMovment(1, 1, 3, 0, .1);
    setAgentChanceOfMovment(1, 1, 4, 0, .05);
    setAgentChanceOfMovment(1, 1, 5, 0, .01);
    setAgentChanceOfMovment(1, 1, 0, 1, .01);
    setAgentChanceOfMovment(1, 1, 1, 1, .01);
    setAgentChanceOfMovment(1, 1, 2, 1, .05);
    setAgentChanceOfMovment(1, 1, 3, 1, .1);
    setAgentChanceOfMovment(1, 1, 4, 1, .05);
    setAgentChanceOfMovment(1, 1, 5, 1, .01);
    setAgentChanceOfMovment(1, 1, 0, 2, 0);
    setAgentChanceOfMovment(1, 1, 1, 2, 0);
    setAgentChanceOfMovment(1, 1, 2, 2, 0);
    setAgentChanceOfMovment(1, 1, 3, 2, 0);
    setAgentChanceOfMovment(1, 1, 4, 2, 0);
    setAgentChanceOfMovment(1, 1, 5, 2, 0);
    setAgentChanceOfMovment(1, 1, 0, 3, 0);
    setAgentChanceOfMovment(1, 1, 1, 3, 0);
    setAgentChanceOfMovment(1, 1, 2, 3, .01);
    setAgentChanceOfMovment(1, 1, 3, 3, .05);
    setAgentChanceOfMovment(1, 1, 4, 3, .01);
    setAgentChanceOfMovment(1, 1, 5, 3, 0);
    setAgentChanceOfMovment(1, 1, 0, 4, .01);
    setAgentChanceOfMovment(1, 1, 1, 4, .01);
    setAgentChanceOfMovment(1, 1, 2, 4, .05);
    setAgentChanceOfMovment(1, 1, 3, 4, .1);
    setAgentChanceOfMovment(1, 1, 4, 4, .05);
    setAgentChanceOfMovment(1, 1, 5, 4, .01);
    setAgentChanceOfMovment(1, 1, 0, 5, .01);
    setAgentChanceOfMovment(1, 1, 1, 5, .01);
    setAgentChanceOfMovment(1, 1, 2, 5, .1);
    setAgentChanceOfMovment(1, 1, 3, 5, .3);
    setAgentChanceOfMovment(1, 1, 4, 5, .5);
    setAgentChanceOfMovment(1, 1, 5, 5, .01);
    setAgentChanceOfMovment(1, 1, 0, 6, .05);
    setAgentChanceOfMovment(1, 1, 1, 6, .08);
    setAgentChanceOfMovment(1, 1, 2, 6, .1);
    setAgentChanceOfMovment(1, 1, 3, 6, .04);
    setAgentChanceOfMovment(1, 1, 4, 6, .02);
    setAgentChanceOfMovment(1, 1, 5, 6, .01);
    setAgentChanceOfMovment(1, 1, 0, 7, .01);
    setAgentChanceOfMovment(1, 1, 1, 7, .01);
    setAgentChanceOfMovment(1, 1, 2, 7, .01);
    setAgentChanceOfMovment(1, 1, 3, 7, .01);
    setAgentChanceOfMovment(1, 1, 4, 7, .01);
    setAgentChanceOfMovment(1, 1, 5, 7, .01);
    setAgentChanceOfMovment(1, 1, 0, 9, .95);
    setAgentChanceOfMovment(1, 1, 1, 9, .9);
    setAgentChanceOfMovment(1, 1, 2, 9, .8);
    setAgentChanceOfMovment(1, 1, 3, 9, .8);
    setAgentChanceOfMovment(1, 1, 4, 9, .9);
    setAgentChanceOfMovment(1, 1, 5, 9, .95);

    //10 to 14
    setAgentChanceOfMovment(2, 0, 0, 0, .01);
    setAgentChanceOfMovment(2, 0, 1, 0, .01);
    setAgentChanceOfMovment(2, 0, 2, 0, .05);
    setAgentChanceOfMovment(2, 0, 3, 0, .1);
    setAgentChanceOfMovment(2, 0, 4, 0, .05);
    setAgentChanceOfMovment(2, 0, 5, 0, .01);
    setAgentChanceOfMovment(2, 0, 0, 1, .01);
    setAgentChanceOfMovment(2, 0, 1, 1, .01);
    setAgentChanceOfMovment(2, 0, 2, 1, .05);
    setAgentChanceOfMovment(2, 0, 3, 1, .1);
    setAgentChanceOfMovment(2, 0, 4, 1, .05);
    setAgentChanceOfMovment(2, 0, 5, 1, .01);
    setAgentChanceOfMovment(2, 0, 0, 2, 0);
    setAgentChanceOfMovment(2, 0, 1, 2, 0);
    setAgentChanceOfMovment(2, 0, 2, 2, .9);
    setAgentChanceOfMovment(2, 0, 3, 2, .9);
    setAgentChanceOfMovment(2, 0, 4, 2, .5);
    setAgentChanceOfMovment(2, 0, 5, 2, 0);
    setAgentChanceOfMovment(2, 0, 0, 3, 0);
    setAgentChanceOfMovment(2, 0, 1, 3, 0);
    setAgentChanceOfMovment(2, 0, 2, 3, .01);
    setAgentChanceOfMovment(2, 0, 3, 3, .05);
    setAgentChanceOfMovment(2, 0, 4, 3, .01);
    setAgentChanceOfMovment(2, 0, 5, 3, 0);
    setAgentChanceOfMovment(2, 0, 0, 4, .01);
    setAgentChanceOfMovment(2, 0, 1, 4, .01);
    setAgentChanceOfMovment(2, 0, 2, 4, .05);
    setAgentChanceOfMovment(2, 0, 3, 4, .1);
    setAgentChanceOfMovment(2, 0, 4, 4, .05);
    setAgentChanceOfMovment(2, 0, 5, 4, .01);
    setAgentChanceOfMovment(2, 0, 0, 5, .01);
    setAgentChanceOfMovment(2, 0, 1, 5, .01);
    setAgentChanceOfMovment(2, 0, 2, 5, .05);
    setAgentChanceOfMovment(2, 0, 3, 5, .1);
    setAgentChanceOfMovment(2, 0, 4, 5, .05);
    setAgentChanceOfMovment(2, 0, 5, 5, .01);
    setAgentChanceOfMovment(2, 0, 0, 6, .05);
    setAgentChanceOfMovment(2, 0, 1, 6, .08);
    setAgentChanceOfMovment(2, 0, 2, 6, .1);
    setAgentChanceOfMovment(2, 0, 3, 6, .04);
    setAgentChanceOfMovment(2, 0, 4, 6, .02);
    setAgentChanceOfMovment(2, 0, 5, 6, .01);
    setAgentChanceOfMovment(2, 0, 0, 7, .01);
    setAgentChanceOfMovment(2, 0, 1, 7, .01);
    setAgentChanceOfMovment(2, 0, 2, 7, .01);
    setAgentChanceOfMovment(2, 0, 3, 7, .01);
    setAgentChanceOfMovment(2, 0, 4, 7, .01);
    setAgentChanceOfMovment(2, 0, 5, 7, .01);
    setAgentChanceOfMovment(2, 0, 0, 9, .95);
    setAgentChanceOfMovment(2, 0, 1, 9, .9);
    setAgentChanceOfMovment(2, 0, 2, 9, .8);
    setAgentChanceOfMovment(2, 0, 3, 9, .8);
    setAgentChanceOfMovment(2, 0, 4, 9, .9);
    setAgentChanceOfMovment(2, 0, 5, 9, .95);
    setAgentChanceOfMovment(2, 1, 0, 0, .01);
    setAgentChanceOfMovment(2, 1, 1, 0, .01);
    setAgentChanceOfMovment(2, 1, 2, 0, .05);
    setAgentChanceOfMovment(2, 1, 3, 0, .1);
    setAgentChanceOfMovment(2, 1, 4, 0, .05);
    setAgentChanceOfMovment(2, 1, 5, 0, .01);
    setAgentChanceOfMovment(2, 1, 0, 1, .01);
    setAgentChanceOfMovment(2, 1, 1, 1, .01);
    setAgentChanceOfMovment(2, 1, 2, 1, .05);
    setAgentChanceOfMovment(2, 1, 3, 1, .1);
    setAgentChanceOfMovment(2, 1, 4, 1, .05);
    setAgentChanceOfMovment(2, 1, 5, 1, .01);
    setAgentChanceOfMovment(2, 1, 0, 2, 0);
    setAgentChanceOfMovment(2, 1, 1, 2, 0);
    setAgentChanceOfMovment(2, 1, 2, 2, 0);
    setAgentChanceOfMovment(2, 1, 3, 2, 0);
    setAgentChanceOfMovment(2, 1, 4, 2, 0);
    setAgentChanceOfMovment(2, 1, 5, 2, 0);
    setAgentChanceOfMovment(2, 1, 0, 3, 0);
    setAgentChanceOfMovment(2, 1, 1, 3, 0);
    setAgentChanceOfMovment(2, 1, 2, 3, .01);
    setAgentChanceOfMovment(2, 1, 3, 3, .05);
    setAgentChanceOfMovment(2, 1, 4, 3, .01);
    setAgentChanceOfMovment(2, 1, 5, 3, 0);
    setAgentChanceOfMovment(2, 1, 0, 4, .01);
    setAgentChanceOfMovment(2, 1, 1, 4, .01);
    setAgentChanceOfMovment(2, 1, 2, 4, .05);
    setAgentChanceOfMovment(2, 1, 3, 4, .1);
    setAgentChanceOfMovment(2, 1, 4, 4, .05);
    setAgentChanceOfMovment(2, 1, 5, 4, .01);
    setAgentChanceOfMovment(2, 1, 0, 5, .01);
    setAgentChanceOfMovment(2, 1, 1, 5, .01);
    setAgentChanceOfMovment(2, 1, 2, 5, .1);
    setAgentChanceOfMovment(2, 1, 3, 5, .3);
    setAgentChanceOfMovment(2, 1, 4, 5, .5);
    setAgentChanceOfMovment(2, 1, 5, 5, .01);
    setAgentChanceOfMovment(2, 1, 0, 6, .05);
    setAgentChanceOfMovment(2, 1, 1, 6, .08);
    setAgentChanceOfMovment(2, 1, 2, 6, .1);
    setAgentChanceOfMovment(2, 1, 3, 6, .04);
    setAgentChanceOfMovment(2, 1, 4, 6, .02);
    setAgentChanceOfMovment(2, 1, 5, 6, .01);
    setAgentChanceOfMovment(2, 1, 0, 7, .01);
    setAgentChanceOfMovment(2, 1, 1, 7, .01);
    setAgentChanceOfMovment(2, 1, 2, 7, .01);
    setAgentChanceOfMovment(2, 1, 3, 7, .01);
    setAgentChanceOfMovment(2, 1, 4, 7, .01);
    setAgentChanceOfMovment(2, 1, 5, 7, .01);
    setAgentChanceOfMovment(2, 1, 0, 9, .95);
    setAgentChanceOfMovment(2, 1, 1, 9, .9);
    setAgentChanceOfMovment(2, 1, 2, 9, .8);
    setAgentChanceOfMovment(2, 1, 3, 9, .8);
    setAgentChanceOfMovment(2, 1, 4, 9, .9);
    setAgentChanceOfMovment(2, 1, 5, 9, .95);

    //15 to 19
    setAgentChanceOfMovment(3, 0, 0, 0, .01);
    setAgentChanceOfMovment(3, 0, 1, 0, .01);
    setAgentChanceOfMovment(3, 0, 2, 0, .05);
    setAgentChanceOfMovment(3, 0, 3, 0, .1);
    setAgentChanceOfMovment(3, 0, 4, 0, .05);
    setAgentChanceOfMovment(3, 0, 5, 0, .01);
    setAgentChanceOfMovment(3, 0, 0, 1, .01);
    setAgentChanceOfMovment(3, 0, 1, 1, .01);
    setAgentChanceOfMovment(3, 0, 2, 1, .05);
    setAgentChanceOfMovment(3, 0, 3, 1, .1);
    setAgentChanceOfMovment(3, 0, 4, 1, .05);
    setAgentChanceOfMovment(3, 0, 5, 1, .01);
    setAgentChanceOfMovment(3, 0, 0, 2, 0);
    setAgentChanceOfMovment(3, 0, 1, 2, 0);
    setAgentChanceOfMovment(3, 0, 2, 2, .9);
    setAgentChanceOfMovment(3, 0, 3, 2, .9);
    setAgentChanceOfMovment(3, 0, 4, 2, .5);
    setAgentChanceOfMovment(3, 0, 5, 2, 0);
    setAgentChanceOfMovment(3, 0, 0, 3, 0);
    setAgentChanceOfMovment(3, 0, 1, 3, 0);
    setAgentChanceOfMovment(3, 0, 2, 3, .01);
    setAgentChanceOfMovment(3, 0, 3, 3, .05);
    setAgentChanceOfMovment(3, 0, 4, 3, .01);
    setAgentChanceOfMovment(3, 0, 5, 3, 0);
    setAgentChanceOfMovment(3, 0, 0, 4, .01);
    setAgentChanceOfMovment(3, 0, 1, 4, .01);
    setAgentChanceOfMovment(3, 0, 2, 4, .05);
    setAgentChanceOfMovment(3, 0, 3, 4, .1);
    setAgentChanceOfMovment(3, 0, 4, 4, .05);
    setAgentChanceOfMovment(3, 0, 5, 4, .01);
    setAgentChanceOfMovment(3, 0, 0, 5, .01);
    setAgentChanceOfMovment(3, 0, 1, 5, .01);
    setAgentChanceOfMovment(3, 0, 2, 5, .05);
    setAgentChanceOfMovment(3, 0, 3, 5, .1);
    setAgentChanceOfMovment(3, 0, 4, 5, .05);
    setAgentChanceOfMovment(3, 0, 5, 5, .01);
    setAgentChanceOfMovment(3, 0, 0, 6, .05);
    setAgentChanceOfMovment(3, 0, 1, 6, .08);
    setAgentChanceOfMovment(3, 0, 2, 6, .1);
    setAgentChanceOfMovment(3, 0, 3, 6, .04);
    setAgentChanceOfMovment(3, 0, 4, 6, .02);
    setAgentChanceOfMovment(3, 0, 5, 6, .01);
    setAgentChanceOfMovment(3, 0, 0, 7, .01);
    setAgentChanceOfMovment(3, 0, 1, 7, .01);
    setAgentChanceOfMovment(3, 0, 2, 7, .01);
    setAgentChanceOfMovment(3, 0, 3, 7, .01);
    setAgentChanceOfMovment(3, 0, 4, 7, .01);
    setAgentChanceOfMovment(3, 0, 5, 7, .01);
    setAgentChanceOfMovment(3, 0, 0, 9, .95);
    setAgentChanceOfMovment(3, 0, 1, 9, .9);
    setAgentChanceOfMovment(3, 0, 2, 9, .8);
    setAgentChanceOfMovment(3, 0, 3, 9, .8);
    setAgentChanceOfMovment(3, 0, 4, 9, .9);
    setAgentChanceOfMovment(3, 0, 5, 9, .95);
    setAgentChanceOfMovment(3, 1, 0, 0, .01);
    setAgentChanceOfMovment(3, 1, 1, 0, .01);
    setAgentChanceOfMovment(3, 1, 2, 0, .05);
    setAgentChanceOfMovment(3, 1, 3, 0, .1);
    setAgentChanceOfMovment(3, 1, 4, 0, .05);
    setAgentChanceOfMovment(3, 1, 5, 0, .01);
    setAgentChanceOfMovment(3, 1, 0, 1, .01);
    setAgentChanceOfMovment(3, 1, 1, 1, .01);
    setAgentChanceOfMovment(3, 1, 2, 1, .05);
    setAgentChanceOfMovment(3, 1, 3, 1, .1);
    setAgentChanceOfMovment(3, 1, 4, 1, .05);
    setAgentChanceOfMovment(3, 1, 5, 1, .01);
    setAgentChanceOfMovment(3, 1, 0, 2, 0);
    setAgentChanceOfMovment(3, 1, 1, 2, 0);
    setAgentChanceOfMovment(3, 1, 2, 2, 0);
    setAgentChanceOfMovment(3, 1, 3, 2, 0);
    setAgentChanceOfMovment(3, 1, 4, 2, 0);
    setAgentChanceOfMovment(3, 1, 5, 2, 0);
    setAgentChanceOfMovment(3, 1, 0, 3, 0);
    setAgentChanceOfMovment(3, 1, 1, 3, 0);
    setAgentChanceOfMovment(3, 1, 2, 3, .01);
    setAgentChanceOfMovment(3, 1, 3, 3, .05);
    setAgentChanceOfMovment(3, 1, 4, 3, .01);
    setAgentChanceOfMovment(3, 1, 5, 3, 0);
    setAgentChanceOfMovment(3, 1, 0, 4, .01);
    setAgentChanceOfMovment(3, 1, 1, 4, .01);
    setAgentChanceOfMovment(3, 1, 2, 4, .05);
    setAgentChanceOfMovment(3, 1, 3, 4, .1);
    setAgentChanceOfMovment(3, 1, 4, 4, .05);
    setAgentChanceOfMovment(3, 1, 5, 4, .01);
    setAgentChanceOfMovment(3, 1, 0, 5, .01);
    setAgentChanceOfMovment(3, 1, 1, 5, .01);
    setAgentChanceOfMovment(3, 1, 2, 5, .1);
    setAgentChanceOfMovment(3, 1, 3, 5, .3);
    setAgentChanceOfMovment(3, 1, 4, 5, .5);
    setAgentChanceOfMovment(3, 1, 5, 5, .01);
    setAgentChanceOfMovment(3, 1, 0, 6, .05);
    setAgentChanceOfMovment(3, 1, 1, 6, .08);
    setAgentChanceOfMovment(3, 1, 2, 6, .1);
    setAgentChanceOfMovment(3, 1, 3, 6, .04);
    setAgentChanceOfMovment(3, 1, 4, 6, .02);
    setAgentChanceOfMovment(3, 1, 5, 6, .01);
    setAgentChanceOfMovment(3, 1, 0, 7, .01);
    setAgentChanceOfMovment(3, 1, 1, 7, .01);
    setAgentChanceOfMovment(3, 1, 2, 7, .01);
    setAgentChanceOfMovment(3, 1, 3, 7, .01);
    setAgentChanceOfMovment(3, 1, 4, 7, .01);
    setAgentChanceOfMovment(3, 1, 5, 7, .01);
    setAgentChanceOfMovment(3, 1, 0, 9, .95);
    setAgentChanceOfMovment(3, 1, 1, 9, .9);
    setAgentChanceOfMovment(3, 1, 2, 9, .8);
    setAgentChanceOfMovment(3, 1, 3, 9, .8);
    setAgentChanceOfMovment(3, 1, 4, 9, .9);
    setAgentChanceOfMovment(3, 1, 5, 9, .95);

    //20 to 24
    setAgentChanceOfMovment(4, 0, 0, 0, .01);
    setAgentChanceOfMovment(4, 0, 1, 0, .01);
    setAgentChanceOfMovment(4, 0, 2, 0, .05);
    setAgentChanceOfMovment(4, 0, 3, 0, .1);
    setAgentChanceOfMovment(4, 0, 4, 0, .05);
    setAgentChanceOfMovment(4, 0, 5, 0, .01);
    setAgentChanceOfMovment(4, 0, 0, 1, .01);
    setAgentChanceOfMovment(4, 0, 1, 1, .01);
    setAgentChanceOfMovment(4, 0, 2, 1, .05);
    setAgentChanceOfMovment(4, 0, 3, 1, .1);
    setAgentChanceOfMovment(4, 0, 4, 1, .05);
    setAgentChanceOfMovment(4, 0, 5, 1, .01);
    setAgentChanceOfMovment(4, 0, 0, 2, 0);
    setAgentChanceOfMovment(4, 0, 1, 2, 0);
    setAgentChanceOfMovment(4, 0, 2, 2, .9);
    setAgentChanceOfMovment(4, 0, 3, 2, .9);
    setAgentChanceOfMovment(4, 0, 4, 2, .5);
    setAgentChanceOfMovment(4, 0, 5, 2, 0);
    setAgentChanceOfMovment(4, 0, 0, 3, 0);
    setAgentChanceOfMovment(4, 0, 1, 3, 0);
    setAgentChanceOfMovment(4, 0, 2, 3, .01);
    setAgentChanceOfMovment(4, 0, 3, 3, .05);
    setAgentChanceOfMovment(4, 0, 4, 3, .01);
    setAgentChanceOfMovment(4, 0, 5, 3, 0);
    setAgentChanceOfMovment(4, 0, 0, 4, .01);
    setAgentChanceOfMovment(4, 0, 1, 4, .01);
    setAgentChanceOfMovment(4, 0, 2, 4, .05);
    setAgentChanceOfMovment(4, 0, 3, 4, .1);
    setAgentChanceOfMovment(4, 0, 4, 4, .05);
    setAgentChanceOfMovment(4, 0, 5, 4, .01);
    setAgentChanceOfMovment(4, 0, 0, 5, .01);
    setAgentChanceOfMovment(4, 0, 1, 5, .01);
    setAgentChanceOfMovment(4, 0, 2, 5, .05);
    setAgentChanceOfMovment(4, 0, 3, 5, .1);
    setAgentChanceOfMovment(4, 0, 4, 5, .05);
    setAgentChanceOfMovment(4, 0, 5, 5, .01);
    setAgentChanceOfMovment(4, 0, 0, 6, .05);
    setAgentChanceOfMovment(4, 0, 1, 6, .08);
    setAgentChanceOfMovment(4, 0, 2, 6, .1);
    setAgentChanceOfMovment(4, 0, 3, 6, .04);
    setAgentChanceOfMovment(4, 0, 4, 6, .02);
    setAgentChanceOfMovment(4, 0, 5, 6, .01);
    setAgentChanceOfMovment(4, 0, 0, 7, .01);
    setAgentChanceOfMovment(4, 0, 1, 7, .01);
    setAgentChanceOfMovment(4, 0, 2, 7, .01);
    setAgentChanceOfMovment(4, 0, 3, 7, .01);
    setAgentChanceOfMovment(4, 0, 4, 7, .01);
    setAgentChanceOfMovment(4, 0, 5, 7, .01);
    setAgentChanceOfMovment(4, 0, 0, 9, .95);
    setAgentChanceOfMovment(4, 0, 1, 9, .9);
    setAgentChanceOfMovment(4, 0, 2, 9, .8);
    setAgentChanceOfMovment(4, 0, 3, 9, .8);
    setAgentChanceOfMovment(4, 0, 4, 9, .9);
    setAgentChanceOfMovment(4, 0, 5, 9, .95);
    setAgentChanceOfMovment(4, 1, 0, 0, .01);
    setAgentChanceOfMovment(4, 1, 1, 0, .01);
    setAgentChanceOfMovment(4, 1, 2, 0, .05);
    setAgentChanceOfMovment(4, 1, 3, 0, .1);
    setAgentChanceOfMovment(4, 1, 4, 0, .05);
    setAgentChanceOfMovment(4, 1, 5, 0, .01);
    setAgentChanceOfMovment(4, 1, 0, 1, .01);
    setAgentChanceOfMovment(4, 1, 1, 1, .01);
    setAgentChanceOfMovment(4, 1, 2, 1, .05);
    setAgentChanceOfMovment(4, 1, 3, 1, .1);
    setAgentChanceOfMovment(4, 1, 4, 1, .05);
    setAgentChanceOfMovment(4, 1, 5, 1, .01);
    setAgentChanceOfMovment(4, 1, 0, 2, 0);
    setAgentChanceOfMovment(4, 1, 1, 2, 0);
    setAgentChanceOfMovment(4, 1, 2, 2, 0);
    setAgentChanceOfMovment(4, 1, 3, 2, 0);
    setAgentChanceOfMovment(4, 1, 4, 2, 0);
    setAgentChanceOfMovment(4, 1, 5, 2, 0);
    setAgentChanceOfMovment(4, 1, 0, 3, 0);
    setAgentChanceOfMovment(4, 1, 1, 3, 0);
    setAgentChanceOfMovment(4, 1, 2, 3, .01);
    setAgentChanceOfMovment(4, 1, 3, 3, .05);
    setAgentChanceOfMovment(4, 1, 4, 3, .01);
    setAgentChanceOfMovment(4, 1, 5, 3, 0);
    setAgentChanceOfMovment(4, 1, 0, 4, .01);
    setAgentChanceOfMovment(4, 1, 1, 4, .01);
    setAgentChanceOfMovment(4, 1, 2, 4, .05);
    setAgentChanceOfMovment(4, 1, 3, 4, .1);
    setAgentChanceOfMovment(4, 1, 4, 4, .05);
    setAgentChanceOfMovment(4, 1, 5, 4, .01);
    setAgentChanceOfMovment(4, 1, 0, 5, .01);
    setAgentChanceOfMovment(4, 1, 1, 5, .01);
    setAgentChanceOfMovment(4, 1, 2, 5, .1);
    setAgentChanceOfMovment(4, 1, 3, 5, .3);
    setAgentChanceOfMovment(4, 1, 4, 5, .5);
    setAgentChanceOfMovment(4, 1, 5, 5, .01);
    setAgentChanceOfMovment(4, 1, 0, 6, .05);
    setAgentChanceOfMovment(4, 1, 1, 6, .08);
    setAgentChanceOfMovment(4, 1, 2, 6, .1);
    setAgentChanceOfMovment(4, 1, 3, 6, .04);
    setAgentChanceOfMovment(4, 1, 4, 6, .02);
    setAgentChanceOfMovment(4, 1, 5, 6, .01);
    setAgentChanceOfMovment(4, 1, 0, 7, .01);
    setAgentChanceOfMovment(4, 1, 1, 7, .01);
    setAgentChanceOfMovment(4, 1, 2, 7, .01);
    setAgentChanceOfMovment(4, 1, 3, 7, .01);
    setAgentChanceOfMovment(4, 1, 4, 7, .01);
    setAgentChanceOfMovment(4, 1, 5, 7, .01);
    setAgentChanceOfMovment(4, 1, 0, 9, .95);
    setAgentChanceOfMovment(4, 1, 1, 9, .9);
    setAgentChanceOfMovment(4, 1, 2, 9, .8);
    setAgentChanceOfMovment(4, 1, 3, 9, .8);
    setAgentChanceOfMovment(4, 1, 4, 9, .9);
    setAgentChanceOfMovment(4, 1, 5, 9, .95);

    for(int i = 5; i <= 10; i++){
        setAgentChanceOfMovment(i, 0, 0, 0, .01);
        setAgentChanceOfMovment(i, 0, 1, 0, .01);
        setAgentChanceOfMovment(i, 0, 2, 0, .05);
        setAgentChanceOfMovment(i, 0, 3, 0, .1);
        setAgentChanceOfMovment(i, 0, 4, 0, .05);
        setAgentChanceOfMovment(i, 0, 5, 0, .01);
        setAgentChanceOfMovment(i, 0, 0, 1, .01);
        setAgentChanceOfMovment(i, 0, 1, 1, .01);
        setAgentChanceOfMovment(i, 0, 2, 1, .05);
        setAgentChanceOfMovment(i, 0, 3, 1, .1);
        setAgentChanceOfMovment(i, 0, 4, 1, .05);
        setAgentChanceOfMovment(i, 0, 5, 1, .01);
        setAgentChanceOfMovment(i, 0, 0, 2, 0);
        setAgentChanceOfMovment(i, 0, 1, 2, 0);
        setAgentChanceOfMovment(i, 0, 2, 2, 0);
        setAgentChanceOfMovment(i, 0, 3, 2, 0);
        setAgentChanceOfMovment(i, 0, 4, 2, 0);
        setAgentChanceOfMovment(i, 0, 5, 2, 0);
        setAgentChanceOfMovment(i, 0, 0, 3, 0);
        setAgentChanceOfMovment(i, 0, 1, 3, 0);
        setAgentChanceOfMovment(i, 0, 2, 3, .01);
        setAgentChanceOfMovment(i, 0, 3, 3, .05);
        setAgentChanceOfMovment(i, 0, 4, 3, .01);
        setAgentChanceOfMovment(i, 0, 5, 3, 0);
        setAgentChanceOfMovment(i, 0, 0, 4, .01);
        setAgentChanceOfMovment(i, 0, 1, 4, .01);
        setAgentChanceOfMovment(i, 0, 2, 4, .05);
        setAgentChanceOfMovment(i, 0, 3, 4, .1);
        setAgentChanceOfMovment(i, 0, 4, 4, .05);
        setAgentChanceOfMovment(i, 0, 5, 4, .01);
        setAgentChanceOfMovment(i, 0, 0, 5, .01);
        setAgentChanceOfMovment(i, 0, 1, 5, .01);
        setAgentChanceOfMovment(i, 0, 2, 5, .05);
        setAgentChanceOfMovment(i, 0, 3, 5, .1);
        setAgentChanceOfMovment(i, 0, 4, 5, .05);
        setAgentChanceOfMovment(i, 0, 5, 5, .01);
        setAgentChanceOfMovment(i, 0, 0, 6, .05);
        setAgentChanceOfMovment(i, 0, 1, 6, .08);
        setAgentChanceOfMovment(i, 0, 2, 6, .1);
        setAgentChanceOfMovment(i, 0, 3, 6, .04);
        setAgentChanceOfMovment(i, 0, 4, 6, .02);
        setAgentChanceOfMovment(i, 0, 5, 6, .01);
        setAgentChanceOfMovment(i, 0, 0, 7, .01);
        setAgentChanceOfMovment(i, 0, 1, 7, .01);
        setAgentChanceOfMovment(i, 0, 2, 7, .01);
        setAgentChanceOfMovment(i, 0, 3, 7, .01);
        setAgentChanceOfMovment(i, 0, 4, 7, .01);
        setAgentChanceOfMovment(i, 0, 5, 7, .01);
        setAgentChanceOfMovment(i, 0, 0, 9, .95);
        setAgentChanceOfMovment(i, 0, 1, 9, .9);
        setAgentChanceOfMovment(i, 0, 2, 9, .8);
        setAgentChanceOfMovment(i, 0, 3, 9, .8);
        setAgentChanceOfMovment(i, 0, 4, 9, .9);
        setAgentChanceOfMovment(i, 0, 5, 9, .95);
        setAgentChanceOfMovment(i, 1, 0, 0, .01);
        setAgentChanceOfMovment(i, 1, 1, 0, .01);
        setAgentChanceOfMovment(i, 1, 2, 0, .05);
        setAgentChanceOfMovment(i, 1, 3, 0, .1);
        setAgentChanceOfMovment(i, 1, 4, 0, .05);
        setAgentChanceOfMovment(i, 1, 5, 0, .01);
        setAgentChanceOfMovment(i, 1, 0, 1, .01);
        setAgentChanceOfMovment(i, 1, 1, 1, .01);
        setAgentChanceOfMovment(i, 1, 2, 1, .05);
        setAgentChanceOfMovment(i, 1, 3, 1, .1);
        setAgentChanceOfMovment(i, 1, 4, 1, .05);
        setAgentChanceOfMovment(i, 1, 5, 1, .01);
        setAgentChanceOfMovment(i, 1, 0, 2, 0);
        setAgentChanceOfMovment(i, 1, 1, 2, 0);
        setAgentChanceOfMovment(i, 1, 2, 2, 0);
        setAgentChanceOfMovment(i, 1, 3, 2, 0);
        setAgentChanceOfMovment(i, 1, 4, 2, 0);
        setAgentChanceOfMovment(i, 1, 5, 2, 0);
        setAgentChanceOfMovment(i, 1, 0, 3, 0);
        setAgentChanceOfMovment(i, 1, 1, 3, 0);
        setAgentChanceOfMovment(i, 1, 2, 3, .01);
        setAgentChanceOfMovment(i, 1, 3, 3, .05);
        setAgentChanceOfMovment(i, 1, 4, 3, .01);
        setAgentChanceOfMovment(i, 1, 5, 3, 0);
        setAgentChanceOfMovment(i, 1, 0, 4, .01);
        setAgentChanceOfMovment(i, 1, 1, 4, .01);
        setAgentChanceOfMovment(i, 1, 2, 4, .05);
        setAgentChanceOfMovment(i, 1, 3, 4, .1);
        setAgentChanceOfMovment(i, 1, 4, 4, .05);
        setAgentChanceOfMovment(i, 1, 5, 4, .01);
        setAgentChanceOfMovment(i, 1, 0, 5, .01);
        setAgentChanceOfMovment(i, 1, 1, 5, .01);
        setAgentChanceOfMovment(i, 1, 2, 5, .1);
        setAgentChanceOfMovment(i, 1, 3, 5, .3);
        setAgentChanceOfMovment(i, 1, 4, 5, .5);
        setAgentChanceOfMovment(i, 1, 5, 5, .5);
        setAgentChanceOfMovment(i, 1, 0, 6, .05);
        setAgentChanceOfMovment(i, 1, 1, 6, .08);
        setAgentChanceOfMovment(i, 1, 2, 6, .1);
        setAgentChanceOfMovment(i, 1, 3, 6, .04);
        setAgentChanceOfMovment(i, 1, 4, 6, .02);
        setAgentChanceOfMovment(i, 1, 5, 6, .01);
        setAgentChanceOfMovment(i, 1, 0, 7, .01);
        setAgentChanceOfMovment(i, 1, 1, 7, .01);
        setAgentChanceOfMovment(i, 1, 2, 7, .01);
        setAgentChanceOfMovment(i, 1, 3, 7, .01);
        setAgentChanceOfMovment(i, 1, 4, 7, .01);
        setAgentChanceOfMovment(i, 1, 5, 7, .01);
        setAgentChanceOfMovment(i, 1, 0, 9, .95);
        setAgentChanceOfMovment(i, 1, 1, 9, .9);
        setAgentChanceOfMovment(i, 1, 2, 9, .8);
        setAgentChanceOfMovment(i, 1, 3, 9, .8);
        setAgentChanceOfMovment(i, 1, 4, 9, .9);
        setAgentChanceOfMovment(i, 1, 5, 9, .95);
    }

    for(int i = 11; i < 18; i++){
        setAgentChanceOfMovment(i, 0, 0, 0, .01);
        setAgentChanceOfMovment(i, 0, 1, 0, .01);
        setAgentChanceOfMovment(i, 0, 2, 0, .05);
        setAgentChanceOfMovment(i, 0, 3, 0, .1);
        setAgentChanceOfMovment(i, 0, 4, 0, .05);
        setAgentChanceOfMovment(i, 0, 5, 0, .01);
        setAgentChanceOfMovment(i, 0, 0, 1, .01);
        setAgentChanceOfMovment(i, 0, 1, 1, .01);
        setAgentChanceOfMovment(i, 0, 2, 1, .05);
        setAgentChanceOfMovment(i, 0, 3, 1, .1);
        setAgentChanceOfMovment(i, 0, 4, 1, .05);
        setAgentChanceOfMovment(i, 0, 5, 1, .01);
        setAgentChanceOfMovment(i, 0, 0, 2, 0);
        setAgentChanceOfMovment(i, 0, 1, 2, 0);
        setAgentChanceOfMovment(i, 0, 2, 2, 0);
        setAgentChanceOfMovment(i, 0, 3, 2, 0);
        setAgentChanceOfMovment(i, 0, 4, 2, 0);
        setAgentChanceOfMovment(i, 0, 5, 2, 0);
        setAgentChanceOfMovment(i, 0, 0, 3, 0);
        setAgentChanceOfMovment(i, 0, 1, 3, 0);
        setAgentChanceOfMovment(i, 0, 2, 3, .01);
        setAgentChanceOfMovment(i, 0, 3, 3, .05);
        setAgentChanceOfMovment(i, 0, 4, 3, .01);
        setAgentChanceOfMovment(i, 0, 5, 3, 0);
        setAgentChanceOfMovment(i, 0, 0, 4, .01);
        setAgentChanceOfMovment(i, 0, 1, 4, .01);
        setAgentChanceOfMovment(i, 0, 2, 4, .05);
        setAgentChanceOfMovment(i, 0, 3, 4, .1);
        setAgentChanceOfMovment(i, 0, 4, 4, .05);
        setAgentChanceOfMovment(i, 0, 5, 4, .01);
        setAgentChanceOfMovment(i, 0, 0, 5, .01);
        setAgentChanceOfMovment(i, 0, 1, 5, .01);
        setAgentChanceOfMovment(i, 0, 2, 5, .05);
        setAgentChanceOfMovment(i, 0, 3, 5, .1);
        setAgentChanceOfMovment(i, 0, 4, 5, .05);
        setAgentChanceOfMovment(i, 0, 5, 5, .01);
        setAgentChanceOfMovment(i, 0, 0, 6, .05);
        setAgentChanceOfMovment(i, 0, 1, 6, .08);
        setAgentChanceOfMovment(i, 0, 2, 6, .1);
        setAgentChanceOfMovment(i, 0, 3, 6, .04);
        setAgentChanceOfMovment(i, 0, 4, 6, .02);
        setAgentChanceOfMovment(i, 0, 5, 6, .01);
        setAgentChanceOfMovment(i, 0, 0, 7, .01);
        setAgentChanceOfMovment(i, 0, 1, 7, .01);
        setAgentChanceOfMovment(i, 0, 2, 7, .01);
        setAgentChanceOfMovment(i, 0, 3, 7, .01);
        setAgentChanceOfMovment(i, 0, 4, 7, .01);
        setAgentChanceOfMovment(i, 0, 5, 7, .01);
        setAgentChanceOfMovment(i, 0, 0, 9, .95);
        setAgentChanceOfMovment(i, 0, 1, 9, .9);
        setAgentChanceOfMovment(i, 0, 2, 9, .8);
        setAgentChanceOfMovment(i, 0, 3, 9, .8);
        setAgentChanceOfMovment(i, 0, 4, 9, .9);
        setAgentChanceOfMovment(i, 0, 5, 9, .95);
        setAgentChanceOfMovment(i, 1, 0, 0, .01);
        setAgentChanceOfMovment(i, 1, 1, 0, .01);
        setAgentChanceOfMovment(i, 1, 2, 0, .05);
        setAgentChanceOfMovment(i, 1, 3, 0, .1);
        setAgentChanceOfMovment(i, 1, 4, 0, .05);
        setAgentChanceOfMovment(i, 1, 5, 0, .01);
        setAgentChanceOfMovment(i, 1, 0, 1, .01);
        setAgentChanceOfMovment(i, 1, 1, 1, .01);
        setAgentChanceOfMovment(i, 1, 2, 1, .05);
        setAgentChanceOfMovment(i, 1, 3, 1, .1);
        setAgentChanceOfMovment(i, 1, 4, 1, .05);
        setAgentChanceOfMovment(i, 1, 5, 1, .01);
        setAgentChanceOfMovment(i, 1, 0, 2, 0);
        setAgentChanceOfMovment(i, 1, 1, 2, 0);
        setAgentChanceOfMovment(i, 1, 2, 2, 0);
        setAgentChanceOfMovment(i, 1, 3, 2, 0);
        setAgentChanceOfMovment(i, 1, 4, 2, 0);
        setAgentChanceOfMovment(i, 1, 5, 2, 0);
        setAgentChanceOfMovment(i, 1, 0, 3, 0);
        setAgentChanceOfMovment(i, 1, 1, 3, 0);
        setAgentChanceOfMovment(i, 1, 2, 3, .01);
        setAgentChanceOfMovment(i, 1, 3, 3, .05);
        setAgentChanceOfMovment(i, 1, 4, 3, .01);
        setAgentChanceOfMovment(i, 1, 5, 3, 0);
        setAgentChanceOfMovment(i, 1, 0, 4, .01);
        setAgentChanceOfMovment(i, 1, 1, 4, .01);
        setAgentChanceOfMovment(i, 1, 2, 4, .05);
        setAgentChanceOfMovment(i, 1, 3, 4, .1);
        setAgentChanceOfMovment(i, 1, 4, 4, .05);
        setAgentChanceOfMovment(i, 1, 5, 4, .01);
        setAgentChanceOfMovment(i, 1, 0, 5, .01);
        setAgentChanceOfMovment(i, 1, 1, 5, .01);
        setAgentChanceOfMovment(i, 1, 2, 5, .1);
        setAgentChanceOfMovment(i, 1, 3, 5, .3);
        setAgentChanceOfMovment(i, 1, 4, 5, .5);
        setAgentChanceOfMovment(i, 1, 5, 5, .5);
        setAgentChanceOfMovment(i, 1, 0, 6, .05);
        setAgentChanceOfMovment(i, 1, 1, 6, .08);
        setAgentChanceOfMovment(i, 1, 2, 6, .1);
        setAgentChanceOfMovment(i, 1, 3, 6, .04);
        setAgentChanceOfMovment(i, 1, 4, 6, .02);
        setAgentChanceOfMovment(i, 1, 5, 6, .01);
        setAgentChanceOfMovment(i, 1, 0, 7, .01);
        setAgentChanceOfMovment(i, 1, 1, 7, .01);
        setAgentChanceOfMovment(i, 1, 2, 7, .01);
        setAgentChanceOfMovment(i, 1, 3, 7, .01);
        setAgentChanceOfMovment(i, 1, 4, 7, .01);
        setAgentChanceOfMovment(i, 1, 5, 7, .01);
        setAgentChanceOfMovment(i, 1, 0, 9, .95);
        setAgentChanceOfMovment(i, 1, 1, 9, .9);
        setAgentChanceOfMovment(i, 1, 2, 9, .8);
        setAgentChanceOfMovment(i, 1, 3, 9, .8);
        setAgentChanceOfMovment(i, 1, 4, 9, .9);
        setAgentChanceOfMovment(i, 1, 5, 9, .95);
    }

}
