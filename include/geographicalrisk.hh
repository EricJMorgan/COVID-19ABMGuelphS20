/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the header file for the geographical risk class
 ***************/


#ifndef GEOGRAPHICALRISK_H_
#define GEOGRAPHICALRISK_H_

#include <string>
#include <iostream>
#include "location.hh"

using namespace std;

//Declare simulation class
class GeographicalRisk {
    private:
    int symptomaticCarriers;
    int avgAgentAge;
    double chanceOfInfection;
    int avgMaskWearer;
    int avgHygiene;
    int ethnicityRatios[5];
    double sexRatio;
    int infectedTotal;
    int susceptibleTotal;
    Location avgLocationRisk;

    public:
    GeographicalRisk();
    void updateAvgCounts();
    void infectPeople();
    void updateRegionRisk();

};

#endif