/****************
 * COVID-19ABMGuelphS20
 * 13/10/20
 * ver 1.03
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
    int infectPeople();

    /**
     * setAgentMitagationChance
     * 
     * This is responsible for setting each age groups chance of
     * following each mitigation strategy. ageGroup 0 = 0 to 4, ageGroup 1 = 5 to 9 etc
     * strategy is 0 = social distancing, 1 = maskwearing, 2 = hygine, 3 = isolation
     * 
     * @param the age group the set of agents are in range 0 - 17
     * @param the mitigation strategy used in range 0 - 3
     */
    void setAgentMitagationChance(int ageGroup, int strategy, double value);
    
    /**
     * setMitagationEffectivness
     * 
     * This sets each mitigation strategys effectivness with a value 
     * between 0 and 1.0. 0 = social distancing, 1 = maskwearing, 2 = hygine, 3 = isolation
     * 
     * @param int strategy this is the strategy too be used in range 0 - 3
     * @param double value in range 0 - 1.0
     */
    void setMitagationEffectivness(int strategy, double value);

    /**
     * setLocationRisk
     * 
     * This sets each locations risk with a value
     * between 0 and 1.0. 0 = genstore, 1 = transportation, etc
     * 
     * @param int location is the location to be checked in range 0 - 8
     * @param double value in range 0 - 1.0
     */
    void setLocationRisk(int location, double value);

    /**
     * getAgentMitagationChance
     * 
     * This gets the ageGroups mitagation chance for the wanted
     * strategy. where ageGroup: 0 = 0 - 4, 1 = 5 - 9 etc and 
     * strategy: 0 = social distancing, 1 = maskwearing, etc.
     * 
     * @param ageGroup is the age group in range 0 - 17.
     * @param strategy is the wanted strategy in range 0 - 3.
     */
    double getAgentMitagationChance(int ageGroup, int strategy);

    /**
     * getMitagationEffectivness
     * 
     * This gets the mitagation strategys given effectivness
     * where 0 = social distancing, 1 = maskwearing, etc.
     * 
     * @param strategy is the wanted strategy in range 0 - 3.
     */
    double getMitagationEffectivness(int strategy);

    /**
     * getLocationRisk
     * 
     * This gets each locations given risk where
     * 0 = genreal store, 1 = transport, etc
     * 
     * @param the wanted location in range 0 - 8
     */
    double getLocationRisk(int location);



    //int getAmountOfLocations();

    // attributes shared by location and risk
    double chanceOfInfection;
    int locationCount[LOCATIONTYPESIZE];
    int amountOfLocations;
    int socialDistancingSeverity;
    double locationRisks[9];

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

    // TODO: maybe needed later if not can be changed to local function variables
    double avgSymptomaticCarriers;
    double avgAsymptomatic;
    double avgMaskWearer;
    double avgHygiene;
    SIRtotals sirTotalLocation;

    double agentMitagationChance[18][4];
    double mitagationEffectivness[4];
};

#endif