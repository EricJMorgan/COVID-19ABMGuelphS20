/****************
 * COVID-19ABMGuelphS20
 * 07/07/20
 * ver 0.02
 * 
 * This is the class file for the agent class
 ***************/


#include <iostream>
#include "agent.hh"

// Constructor
Agent::Agent(AgentInfo agentInfo) {
    info = agentInfo;
    DecideEthnicity();
    DecideMartialStatus();
    DecideHouseholdIncome();
}

AgentInfo Agent::getAgentInfo(){
    return info;
}

string Agent::getEthnicity(){
    return ethnicity;
}

void Agent::DecideHouseholdIncome() {
    if (!HouseholdIncome.empty()) {
        return;
    }

    if (info < 4 || 18 <= info <= 21) {
        income = HNA;
    }

    double randomNumber = (double) rand()/RAND_MAX;

    // Marital probabilities backed by Gov of Canada Census
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
    if (!maritalStatus.empty()) {
        return;
    }

    if (info < 4 || 18 <= info <= 21) {
        maritalStatus = "Single";
    }

    double randomNumber = (double) rand()/RAND_MAX;
    
    // Marital probabilities backed by Gov of Canada Census
    if (0 <= randomNumber && randomNumber < 0.2904142) {
        ethnicity = "Single";
    } else if (0.2904142 <= randomNumber && randomNumber < 0.3888837) {
        ethnicity = "Common Law";
    } else if (0.3888837 <= randomNumber && randomNumber < 0.8566257) {
        ethnicity = "Married";
    } else if (0.8566257 <= randomNumber && randomNumber < 0.8867302) {
        ethnicity = "Seperated";
    } else if (0.8867302 <= randomNumber && randomNumber < 0.9468475) {
        ethnicity = "Divorced";
    } else {
        ethnicity = "Widowed";
    }
}

void Agent::DecideEthnicity() {
    if (!ethnicity.empty()) {
        return;
    }

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
