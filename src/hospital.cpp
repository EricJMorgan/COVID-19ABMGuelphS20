/****************
 * COVID-19ABMGuelphS20
 * 06/10/20
 * ver 1.03
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

    //set all age values too 0
    for(int i = 0; i < 18; i++){
        setAgentDeathChance(i, 0);
        setAgentRecoveryTime(i, 0);
    }
}

void Hospital::freeIcuBeds(int indexToRemove) {
    //error checking
    if (indexToRemove < 0 || indexToRemove >= (int)hospitalICU.size()) {
        cout << "Trying to free icu out of bounds index" << endl;
        return;
    }

    //removes agent at a given index
    hospitalICU.erase(hospitalICU.begin() + indexToRemove);
    icuCount--;
    indicateOverflow();
}

void Hospital::freeHospitalBeds(int indexToRemove) {
    //error checking
    if (indexToRemove < 0 || indexToRemove >= (int)hospitalGeneralWard.size()) {
        cout << "Trying to free hospital out of bounds index" << endl;
        return;
    }
    
    //removes agent at a given index
    hospitalGeneralWard.erase(hospitalGeneralWard.begin() + indexToRemove);
    numberPpl--;
    indicateOverflow();
}

void Hospital::indicateOverflow() {\
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

void Hospital::HospitalTimeStep(double timestep) {
    //loop through all the beds in the icu
    for (int i = 0; i < (int)hospitalICU.size(); i++) {
        string sirResponse  = hospitalICU[i]->SIRTimeStep(timestep);

        //check if an agent is recoverd or dead and remove them from the list
        if (sirResponse == "RECOVERAGENT") {
            Agent *recoveredAgent = hospitalICU.at(i);
            hospitalICU.erase(hospitalICU.begin() + i);
            newlyRecovered.push_back(recoveredAgent);
            icuCount--;
        } else if (sirResponse == "DECEASEAGENT") {
            Agent *deceasedAgent = hospitalICU.at(i);
            hospitalICU.erase(hospitalICU.begin() + i);
            newlyDeceased.push_back(deceasedAgent);
            icuCount--;
        }
    }

    //loop through all the beds in the gen pop
    for (int i = 0; i < (int)hospitalGeneralWard.size(); i++) {
        string sirResponse  = hospitalGeneralWard[i]->SIRTimeStep(timestep);

        //check if an agent is recoverd or needing to move too the ICU and remove them from the list
        if (sirResponse == "ICUAGENT") {
            Agent *toICU = hospitalGeneralWard.at(i);
            hospitalGeneralWard.erase(hospitalGeneralWard.begin() + i);
            hospitalICU.push_back(toICU);
            icuCount++;
            totalICU++;
            numberPpl--;
        } else if (sirResponse == "RECOVERAGENT") {
            Agent *recoveredAgent = hospitalGeneralWard.at(i);
            hospitalGeneralWard.erase(hospitalGeneralWard.begin() + i);
            newlyRecovered.push_back(recoveredAgent);
            numberPpl--;
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

void Hospital::setAgentRecoveryTime(int ageRange, short value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 127) return;

    agentRecoveryTime[ageRange] = value;
}

void Hospital::setAgentDeathChance(int ageRange, double value){
    if(ageRange < 0 || ageRange > 17) return;
    if(value < 0 || value > 1) return;
    agentDeathChance[ageRange] = value;
}
