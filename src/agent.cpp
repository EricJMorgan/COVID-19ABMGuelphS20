/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the class file for the agent class
 ***************/


#include <iostream>
#include "agent.hh"

// Constructor
Agent::Agent(AgeGroup agegroup, string agentGender) {
    age = agegroup;
    gender = agentGender;
    DecideEthnicity();
}

void Agent::DecideEthnicity() {
    if (!ethnicity.empty()) {
        return;
    }

    double randomNumber = (double) rand()/RAND_MAX;
    
    if (0 <= randomNumber < 0.0077) {
        ethnicity = "First Nations";
    } else if (0.0077 <= randomNumber < 0.0137324) {
        ethnicity = "Metis";
    } else if (0.0137324 <= randomNumber < 0.0138462) {
        ethnicity = "Inuit";
    } else if (0.0138462 <= randomNumber < 0.0141876) {
        ethnicity = "Other Aboriginal Descent";
    } else if (0.0141876 <= randomNumber < 0.0199537) {
        ethnicity = "Arab";
    } else if (0.0199537 <= randomNumber < 0.0418421) {
        ethnicity = "Black";
    } else if (0.0418421 <= randomNumber < 0.0737453) {
        ethnicity = "Chinese";
    } else if (0.0737453 <= randomNumber < 0.0953302) {
        ethnicity = "Filipino";
    } else if (0.0953302 <= randomNumber < 0.0967717) {
        ethnicity = "Japanese";
    } else if (0.0967717 <= randomNumber < 0.0991616) {
        ethnicity = "Korean";
    } else if (0.0991616 <= randomNumber < 0.1093661) {
        ethnicity = "Latin American";
    } else if (0.1093661 <= randomNumber < 0.1586813) {
        ethnicity = "South Asian";
    } else if (0.1586813 <= randomNumber < 0.1771935) {
        ethnicity = "Southeast Asian";
    } else if (0.1771935 <= randomNumber < 0.1888016) {
        ethnicity = "West Asian";
    } else {
        ethnicity = "White";
    }

}
