/****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
 * 
 * This is the class file for the hospital class. The purpose of
 * this class is to keep track of hopsital statistics. Mainly the amount
 * of beds being used and the amount of ICU beds being used.
 ***************/


#include <iostream>
#include "hospital.hh"

// Constructor
Hospital::Hospital() {
    //init values
    numberPpl = 0;
    icuCount = 0;
    totalICU = 0;
    totalHospital = 0;
    hospitalOverflow = false;
    icuOverflow = false;

}

void Hospital::indicateOverflow() {
    //sets the flag if more people are in beds than what the hospital has
    if(numberPpl > totalBedCount) {
        hospitalOverflow = true;
    } else {
        hospitalOverflow = false;
    }

    if(icuCount > icuBedCount) {
        icuOverflow = true;
    } else {
        icuOverflow = false;
    }
}

void Hospital::increaseHospitalCount(Agent* agentToAdd) {
    //error checking
    if (agentToAdd == NULL) {
        cout << "Passing NULL to increase hospital" << endl;
        return;
    }

    //adds agent to hospital beds
    hospitalGeneralWard.push_back(agentToAdd);
    numberPpl++;
    totalHospital++;
    indicateOverflow();
}

void Hospital::increaseIcuCount(Agent* agentToAdd) {
    //error checking
    if (agentToAdd == NULL) {
        cout << "Passing NULL to increase ICU" << endl;
        return;
    }
    
    //adds agent to ICU beds
    hospitalICU.push_back(agentToAdd);
    icuCount++;
    totalICU++;
    indicateOverflow(); 
}

void Hospital::HospitalTimeStep(double timestep, short agentRecoveryTime[18], double agentDeathChance[18], double agentChanceOfICU[18]) {
    //loop through all the beds in the icu
    string sirResponse;
    Agent *currAgent;
    int agentAgeGroup;
    for (int i = 0; i < (int)hospitalICU.size(); i++) {
        //get agent info
        currAgent = hospitalICU[i];
        agentAgeGroup = currAgent->getAgentAgeGroup();

        //if agent is finished the recovery time. Multiplied by 6 because it is incremented everytime step not every day
        if (currAgent->timeInHospital > (agentRecoveryTime[agentAgeGroup] * 6)) {
            hospitalICU.erase(hospitalICU.begin() + i);
            currAgent->recoverAgent();
            currAgent->timeInHospital = 0;
            newlyRecovered.push_back(currAgent);
            icuCount--;
        //if agent rolls within range of the death chance
        } else if (agentDeathChance[agentAgeGroup] >= ((double) rand() / (RAND_MAX))) {
            hospitalICU.erase(hospitalICU.begin() + i);
            currAgent->killAgent();
            currAgent->timeInHospital = 0;
            newlyDeceased.push_back(currAgent);
            icuCount--;
        //if agent stays put
        } else {
            currAgent->timeInHospital++;
            currAgent->timeInfected++;
        }
    }

    //loop through all the beds in the gen pop
    for (int i = 0; i < (int)hospitalGeneralWard.size(); i++) {
        //get agent info
        currAgent = hospitalGeneralWard[i];
        agentAgeGroup = currAgent->getAgentAgeGroup();

        //if agent rolls to go to the hospital
        if (agentChanceOfICU[agentAgeGroup] >= ((double) rand() / (RAND_MAX))) {
            hospitalGeneralWard.erase(hospitalGeneralWard.begin() + i);
            currAgent->ICUAgent();
            currAgent->timeInHospital++;
            hospitalICU.push_back(currAgent);
            icuCount++;
            totalICU++;
            numberPpl--;
        } else if (currAgent->timeInHospital > agentRecoveryTime[agentAgeGroup]) {
            hospitalGeneralWard.erase(hospitalGeneralWard.begin() + i);
            currAgent->recoverAgent();
            currAgent->timeInHospital = 0;
            newlyRecovered.push_back(currAgent);
            numberPpl--;
        } else {
            currAgent->timeInHospital++;
            currAgent->timeInfected++;
        }
    }
}

int Hospital::getTotalBeds() {
    return numberPpl;
}

int Hospital::getIcuBeds() {
    return icuCount;
}

int Hospital::getTotalICUCount() {
    return totalICU;
}

int Hospital::getTotalHospitalCount() {
    return totalHospital;
}


