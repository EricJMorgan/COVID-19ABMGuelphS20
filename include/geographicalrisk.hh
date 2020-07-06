/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the geographical risk class
 ***************/


#ifndef GEOGRAPHICALRISK_H_
#define GEOGRAPHICALRISK_H_

#pragma once
#include <string>
#include <iostream>

using namespace std;

class Location;
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
    int socialDistancingSeverity;
    bool socialDistancing;
    Location* avgLocationRisk;

    public:
    GeographicalRisk();
    void updateAvgCounts();
    void infectPeople();
    void updateRegionRisk();

};

#endif