/****************
 * COVID-19ABMGuelphS20
 * 04/08/20
 * ver 0.06
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

#define LOCATIONTYPESIZE 10

enum condenseLocationType {GENSTORE, TRANSPORT, SCHOOL, PARKSANDREC, SERVICES, ENTERTAINMENT, HEALTH, PLACEOFWORSHIP, UNNEEDED, RESIDENTIAL};

//Declare simulation class
class GeographicalRisk {
    public:
    /**
     * GeographicalRisk
     * 
     * This is the default constructor for the Geographical risk class
     */
    GeographicalRisk();

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

    /**
     * getLocationCountAt
     * 
     * This function will take in a index and return how many of
     * the specified location index
     * 
     * @param index, must be in range 0 <= index <= 8. Refer to condenseLocationType enum for which index you want
     * @return a int of the amount of the specified shops in a location
     */
    int getLocationCountAt(condenseLocationType index);

    /**
     * getLocationCountAt
     * 
     * This function will call the private function updateAvgCountsAndRisk and update the risk for the region
     * and various total counts, it will then take the succeptible people in the region and 
     * 
     */
    int infectPeople();

    //int getAmountOfLocations();

    // attributes shared by location and risk
    double chanceOfInfection;
    int locationCount[LOCATIONTYPESIZE];
    int amountOfLocations;

    std::vector<Agent *> susceptible;
    std::vector<Agent *> infected;

    private:

    /**
     * getLocationCountAt
     * 
     * This takes the current businesses and agents in the area and decides the amount of COVID transfer
     * risk in the given region
     * 
     */
    void updateAvgCountsAndRisk();

    // TODO: maybe needed later, if not can be changed to local function variables
    double avgSymptomaticCarriers;
    double avgAsymptomatic;
    double avgMaskWearer;
    double avgHygiene;
    int socialDistancingSeverity = 1; // user input on a scale of 1 to 10, front end slider?
    SIRtotals sirTotalLocation;
};

#endif