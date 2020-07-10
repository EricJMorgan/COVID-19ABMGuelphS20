/****************
 * COVID-19ABMGuelphS20
 * 09/07/20
 * ver 0.03
 * 
 * This is the header file for the location class
 ***************/


#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>
#include <iostream>
#include "SIRtotals.hh"
#include "transportation.hh"
#include "geographicalrisk.hh"
#include "postalCodeData.hh"

using namespace std;

//Forward declarations
class Agent;

//Declare simulation class
class Location : public PostalCodeData{
    private:
    int population;
    int pplDensity;
    int avgTimeSpent;
    int avgAgentInteraction;
    Agent* currentAgents;
    Transportation* transportaionRoutesFromLocation;
    GeographicalRisk avgLocationRisk;
    SIRtotals sirTotalLocation;

    public:
    Location();
    Location(string postalCode, int shopData[9]);
    int getPopulation();
    Agent* getSusceptible();
    Agent* getInfected();
    Agent* getRecovered();
};

#endif