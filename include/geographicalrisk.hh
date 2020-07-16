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
#include "SIRtotals.hh"
#include "agent.hh"

using namespace std;

//Declare simulation class
class GeographicalRisk {
    public:
    /**
     * GeographicalRisk
     * 
     * This is the default constructor for the Geographical risk class
     */
    GeographicalRisk();

    int population;
    double chanceOfInfection;
    Agent* currentAgents;

    void updateAvgCountsAndRisk();
    void infectPeople();

    private:
    int avgSymptomaticCarriers;
    double avgAgentAge;
    double avgMaskWearer;
    double avgHygiene;
    int ethnicityRatios[5];
    double sexRatioMale;
    int socialDistancingSeverity; // user input
    SIRtotals sirTotalLocation;
};

#endif