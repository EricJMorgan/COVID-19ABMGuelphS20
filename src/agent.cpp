/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.05
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
    DecideEducation();
    DecideMigitationStrategy();
}

AgentInfo Agent::getAgentInfo(){
    return info;
}

string Agent::getEthnicity(){
    return ethnicity;
}

/*************************
 * DecideEducation
 * 
 * This function randomly decides an agents educational background income based on demographics
 * of guelph from the Canadian Census of 2017
 ************************/
void Agent::DecideEducation() {
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

/*************************
 * DecideHouseholdIncome
 * 
 * This function randomly decides an agents household income based on demographics
 * of guelph from the Canadian Census of 2017
 ************************/
void Agent::DecideHouseholdIncome() {
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

/*************************
 * DecideMartialStatus
 * 
 * This function randomly decides an agents marital status based 
 * on demographics of guelph from the Canadian Census of 2017
 ************************/
void Agent::DecideMartialStatus() { 
    if (info < 4 || (18 <= info && info <= 21)) {
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

/*************************
 * DecideEthnicity
 * 
 * This function randomly decides an agents ethnicity based on 
 * demographics of guelph from the Canadian Census of 2017
 ************************/
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

/*************************
 * DecideMigitationStrategy
 * 
 * This function randomly decides an agents chance of wearing 
 * a face mask and practicing good hygiene
 ************************/
void Agent::DecideMigitationStrategy() {
    double maskChance = (double) rand()/RAND_MAX;
    double hygieneChance = (double) rand()/RAND_MAX;

    if (maskChance < 0.5) {
        wearingMask = true;
    }

    if (hygieneChance < 0.5) {
        agentHygiene = true;
    }
    
    
}

string Agent::agentToString() {
    string agentString = "";

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