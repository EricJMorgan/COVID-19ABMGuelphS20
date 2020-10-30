/****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
 * 
 * This is the class file for the agent class. It contains all of the 
 * info for each individual agent. When a new agent is created it decides its
 * ethnicty, gender, education, marital status, and income. 
 ***************/


#include <iostream>
#include "agent.hh"

// Constructor
Agent::Agent(AgentInfo agentInfo) {
    //Init varibles
    info = agentInfo;
    hasMoved = false;
    wearingMask = false;
    agentHygiene = false;

    DecideEthnicity();
    DecideMartialStatus();
    DecideHouseholdIncome();
    DecideEducation();
    setEducationIndex(-1);
    setResidentialIndex(-1);
}

AgentInfo Agent::getAgentInfo(){
    hasMoved = false;
    return info;
}

string Agent::getEthnicity(){
    return ethnicity;
}

void Agent::setHasMoved(bool newMove){
    hasMoved = newMove;
}

bool Agent::getHasMoved(){
    return hasMoved;
}

void Agent::setEducationIndex(int index){
    educationIndex = index;
}

int Agent::getEducationIndex(){
    return educationIndex;
}

void Agent::setResidentialIndex(int index){
    residentialIndex = index;
}

int Agent::getResidentialIndex(){
    return residentialIndex;
}


void Agent::DecideEducation() {
    //if agents are younger than 20 they will not have a formal education yet
    //Females have too be done like this due too their placement in the enum being
    //in the middle
    if (info < MALE20TO24 || (FEMALE0TO4 <= info && info <= FEMALE15TO19)) {
        education = NA;
    }

    double randomNumber = (double) rand()/RAND_MAX;

    // Household income probabilities probabilities backed by Gov of Canada Census
    if (0 <= randomNumber && randomNumber < 0.1902620) {
        education = NOCERTIF;
    } else if (0.1902620 <= randomNumber && randomNumber < 0.5289553) {
        education = HIGHSCHOOL;
    } else if (0.5289553 <= randomNumber && randomNumber < 0.5901270) {
        education = APPRENTICESHIP;
    } else if (0.5901270 <= randomNumber && randomNumber < 0.6203755) {
        education = COLLEGE;
    } else if (0.6203755 <= randomNumber && randomNumber < 0.6437085) {
        education = BELOWDEGREE;
    } else {
        education = UNIVERSITY;
    }
    
}

void Agent::DecideHouseholdIncome() {
    //if someone is younger than 20 we assume they have no income tied too themselves
    if (info < MALE20TO24 || (FEMALE0TO4 <= info && info <= FEMALE15TO19)) {
        income = HNA;
    }

    double randomNumber = (double) rand()/RAND_MAX;

    // Household income probabilities probabilities backed by Gov of Canada Census
    if (0 <= randomNumber && randomNumber < 0.0118064) {
        income = H0TO4;
    } else if (0.0118064 <= randomNumber && randomNumber < 0.0244768) {
        income = H5TO9;
    } else if (0.0244768 <= randomNumber && randomNumber < 0.0505855) {
        income = H10TO14;
    } else if (0.0505855 <= randomNumber && randomNumber < 0.0804377) {
        income = H15TO19;
    } else if (0.0804377 <= randomNumber && randomNumber < 0.1485889) {
        income = H20TO29;
    } else if (0.1485889 <= randomNumber && randomNumber < 0.2195239) {
        income = H30TO39;
    } else if (0.2195239 <= randomNumber && randomNumber < 0.2986177) {
        income = H40TO49;
    } else if (0.2986177 <= randomNumber && randomNumber < 0.3744480) {
        income = H50TO59;
    } else if (0.3744480 <= randomNumber && randomNumber < 0.5129583) {
        income = H60TO79;
    } else if (0.5129583 <= randomNumber && randomNumber < 0.6353426) {
        income = H80TO99;
    } else if (0.6353426 <= randomNumber && randomNumber < 0.7559992) {
        income = H100TO124;
    } else if (0.7559992 <= randomNumber && randomNumber < 0.8407563) {
        income = H125TO149;
    } else {
        income = H150;
    }
}

void Agent::DecideMartialStatus() { 
    //if someone is younger than 20 they are not in a serious relationship
    if (info < MALE20TO24 || (FEMALE0TO4 <= info && info <= FEMALE15TO19)) {
        maritalStatus = "Single";
    }

    double randomNumber = (double) rand()/RAND_MAX;
    
    // Marital probabilities backed by Gov of Canada Census
    if (0 <= randomNumber && randomNumber < 0.2904142) {
        maritalStatus = "Single";
    } else if (0.2904142 <= randomNumber && randomNumber < 0.3888837) {
        maritalStatus = "Common Law";
    } else if (0.3888837 <= randomNumber && randomNumber < 0.8566257) {
        maritalStatus = "Married";
    } else if (0.8566257 <= randomNumber && randomNumber < 0.8867302) {
        maritalStatus = "Seperated";
    } else if (0.8867302 <= randomNumber && randomNumber < 0.9468475) {
        maritalStatus = "Divorced";
    } else {
        maritalStatus = "Widowed";
    }
}

void Agent::DecideEthnicity() {
    double randomNumber = (double) rand()/RAND_MAX;
    
    // Race probabilities backed by Gov of Canada Census
    if (0 <= randomNumber && randomNumber < 0.0077) {
        ethnicity = "First Nations";
    } else if (0.0077 <= randomNumber && randomNumber < 0.0137324) {
        ethnicity = "Metis";
    } else if (0.0137324 <= randomNumber && randomNumber < 0.0138462) {
        ethnicity = "Inuit";
    } else if (0.0138462 <= randomNumber && randomNumber < 0.0141876) {
        ethnicity = "Other Aboriginal Descent";
    } else if (0.0141876 <= randomNumber && randomNumber < 0.0199537) {
        ethnicity = "Arab";
    } else if (0.0199537 <= randomNumber && randomNumber < 0.0418421) {
        ethnicity = "Black";
    } else if (0.0418421 <= randomNumber && randomNumber < 0.0737453) {
        ethnicity = "Chinese";
    } else if (0.0737453 <= randomNumber && randomNumber < 0.0953302) {
        ethnicity = "Filipino";
    } else if (0.0953302 <= randomNumber && randomNumber < 0.0967717) {
        ethnicity = "Japanese";
    } else if (0.0967717 <= randomNumber && randomNumber < 0.0991616) {
        ethnicity = "Korean";
    } else if (0.0991616 <= randomNumber && randomNumber < 0.1093661) {
        ethnicity = "Latin American";
    } else if (0.1093661 <= randomNumber && randomNumber < 0.1586813) {
        ethnicity = "South Asian";
    } else if (0.1586813 <= randomNumber && randomNumber < 0.1771935) {
        ethnicity = "Southeast Asian";
    } else if (0.1771935 <= randomNumber && randomNumber < 0.1888016) {
        ethnicity = "West Asian";
    } else {
        ethnicity = "White";
    }

}

void Agent::decideMitigationStrategy(double mitagationPerAge[18][4]) {
    int ageGroup = AgentAgeGroupReverse.at(info);
    double currRoll;

    //Roll for each mitagation chance for the agent
    currRoll = ((double) rand() / (RAND_MAX));
    wearingMask = (currRoll <= mitagationPerAge[ageGroup][0]);

    currRoll = ((double) rand() / (RAND_MAX));
    agentHygiene = (currRoll <= mitagationPerAge[ageGroup][1]);

    currRoll = ((double) rand() / (RAND_MAX));
    socialDistancing = (currRoll <= mitagationPerAge[ageGroup][2]);

    currRoll = ((double) rand() / (RAND_MAX));
    willIsolate = (currRoll <= mitagationPerAge[ageGroup][3]);
}

string Agent::agentToString() {
    string agentString = "";

    //just a string for error checking
    agentString.append(AgentInfoMapReverse[info]);
    agentString.append(" ");
    agentString.append(ethnicity);
    agentString.append(" ");
    agentString.append(maritalStatus);
    agentString.append(" ");
    agentString.append(HouseholdIncomeMap[income]);
    agentString.append(" ");
    agentString.append(EducationMap[education]);

    return agentString;
}

int Agent::getAgentAgeGroup() {
    return AgentAgeGroupReverse.at(info);
}

bool Agent::randomAgentNeedsHospital(double agentNeedsHospital[18]){
    return agentNeedsHospital[getAgentAgeGroup()] >= ((double) rand() / (RAND_MAX)) && (getSeverity() != INCUBATION);
}

void Agent::agentIncubationCheck(short agentIncubationTime[18]){
    //this is multiplied by the currTime step because this time will increment every time step instead of every day
    if(timeIncubating < (agentIncubationTime[getAgentAgeGroup()] * 6)){
        timeIncubating = 0;
        infectAgent();
    }
}