/****************
 * COVID-19ABMGuelphS20
 * 17/07/20
 * ver 0.02
 * 
 * This is the class file for the hospital class
 ***************/


#include <iostream>
#include "hospital.hh"

int Hospital::totalBedCount = 130;
int Hospital::icuBedCount = 22;

// Constructor
Hospital::Hospital() {
    numberPpl = 0;
    icuCount = 0;
}

void Hospital::freeIcuBeds(int freeNum) {
    if(freeNum <= icuCount) {
        icuCount = icuCount - freeNum;
    } else {
        cout << "ERROR: Number of ICU cases to be freed exceeds current total" << endl;
        cout << "Will attempt to zero out the number of ICU cases instead" << endl;
        icuCount = 0;
    }
}

void Hospital::freeHospitalBeds(int freeNum) {
    if(freeNum <= numberPpl) {
        numberPpl = numberPpl - freeNum;
    } else {
        cout << "ERROR: Number of ICU cases to be freed exceeds current total" << endl;
        cout << "Will attempt to zero out the number of ICU cases instead" << endl;
        numberPpl = 0;
    }
}

