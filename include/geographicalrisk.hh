/****************
 * COVID-19ABMGuelphS20
 * 27/11/20
 * ver 2.01
 * 
 * This is the header file for the geographical risk class. The main
 * use for this class is to do the math for each area and decide how many 
 * people to infect in a given area.
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
     * @param index must be in range 0 <= index <= 8. Refer to condenseLocationType enum for which index you want
     * @return a int of the amount of the specified shops in a location
     */
    int getLocationCountAt(int index);

    /**
     * getLocationCountAt
     * 
     * This function will take in a index and return how many of
     * the specified location index
     * 
     * @param index must be in range 0 <= index <= 8. Refer to condenseLocationType enum for which index you want
     * @return a int of the amount of the specified shops in a location
     */
    int getLocationCountAt(condenseLocationType index);

    /**
     * getLocationCountAt
     * 
     * This function will call the private function updateAvgCountsAndRisk and update the risk for the region
     * and various total counts it will then take the succeptible people in the region and 
     * 
     */
    int infectPeople(double agentChanceOfMitigation[18][5], double mitigationEffect[5], double locationRisk[10]);

    

    //int getAmountOfLocations();

    // attributes shared by location and risk
    double chanceOfInfection;
    int locationCount[LOCATIONTYPESIZE];
    int amountOfLocations;
    int socialDistancingSeverity;
    

    std::vector<Agent *> susceptible;
    std::vector<Agent *> infected;

    private:

    // TODO: maybe needed later if not can be changed to local function variables
    double avgSymptomaticCarriers;
    double avgAsymptomatic;
    double avgMaskWearer;
    double avgHygiene;
    double agentChanceOfInfection[18];
    SIRtotals sirTotalLocation;

    void updateAvgCountsAndRisk(double agentChanceOfMitigation[18][5], double mitigationEffect[5], double locationRisk[10]);

    double calculateDensityRisk(double locationRisk[10]);
};

#endif