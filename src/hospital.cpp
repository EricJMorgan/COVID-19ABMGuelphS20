/****************
 * COVID-19ABMGuelphS20
 * 17/07/20
 * ver 0.02
 * 
 * This is the class file for the hospital class
 ***************/


#include <iostream>
#include "hospital.hh"

// Constructor
Hospital::Hospital() {
    numberPpl = 0;
    icuCount = 0;
    overflow = false;
}

void Hospital::freeIcuBeds(int freeNum) {
    if(freeNum <= icuCount) {
        icuCount = icuCount - freeNum;
    } else {
        cout << "ERROR: Number of ICU cases to be freed exceeds current total" << endl;
        cout << "Will attempt to zero out the number of ICU cases instead" << endl;
        icuCount = 0;
    }
    indicateOverflow();
}

void Hospital::freeHospitalBeds(int freeNum) {
    if(freeNum <= numberPpl) {
        numberPpl = numberPpl - freeNum;
    } else {
        cout << "ERROR: Number of hospital cases to be freed exceeds current total" << endl;
        cout << "Will attempt to zero out the number of hospital cases instead" << endl;
        numberPpl = 0;
    }
    indicateOverflow();
}

void Hospital::indicateOverflow() {
    if(numberPpl > totalBedCount || icuCount > icuBedCount) {
        overflow = true;
    } else {
        overflow = false;
    }
}

void Hospital::increaseHospitalCount(int numAgents) {
    if(numAgents > 0) {
        numberPpl = numberPpl + numAgents;
        indicateOverflow();
    } else {
        cout << "ERROR: Number of agents is negative" << endl;
        cout << "Will add nothing to the number of hospitalized patients" << endl;
    }
}

void Hospital::increaseIcuCount(int numAgents) {
    if(numAgents > 0) {
        numberPpl = numberPpl + icuCount;
        indicateOverflow();
    } else {
        cout << "ERROR: Number of agents is negative" << endl;
        cout << "Will add nothing to the number of ICU patients" << endl;
    }
}

int Hospital::getTotalBeds() {
    return numberPpl;
}

int Hospital::getIcuBeds() {
    return icuCount;
}
