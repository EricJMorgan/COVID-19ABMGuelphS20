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
    int locationCount[9];

    /**
     * getLocationCountAt
     * 
     * This function will take in a index and return how many of
     * the specified location index
     * 
     * @param index, must be in range 0 <= index <= 8. Refer to condenseLocationType enum for which index you want
     * @return a int of the amount of the specified shops in a location
     */
    int getLocationCountAt(int index);

    void infectPeople();

    private:
    void updateAvgCountsAndRisk();
    double avgSymptomaticCarriers;
    double avgAsymptomatic;
    double avgMaskWearer;
    double avgHygiene;
    int socialDistancingSeverity; // user input
    SIRtotals sirTotalLocation;
};

#endif