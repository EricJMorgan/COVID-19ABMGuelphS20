/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
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
#include "business.hh"

using namespace std;

//Forward declarations
class Agent;

//Declare simulation class
class Location {
    private:
    string name; //postal code
    int population;
    int pplDensity;
    int avgTimeSpent;
    int avgAgentInteraction;
    Agent* currentAgents;
    Business* locationBusiness;
    Transportation* transportaionRoutesFromLocation;
    GeographicalRisk avgLocationRisk;
    SIRtotals sirTotalLocation;

    public:
    Location();
    int getPopulation();
    Agent* getSusceptible();
    Agent* getInfected();
    Agent* getRecovered();
};

#endif