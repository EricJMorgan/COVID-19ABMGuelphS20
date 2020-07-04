/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the header file for the location class
 ***************/


#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>
#include <iostream>
#include "agent.hh"
#include "geographicalrisk.hh"

using namespace std;

//Declare simulation class
class Location {
    private:
    string name;
    string sector; //wtf is this
    int population;
    //TYPE location; need GIS stuff
    int pplDensity;
    int avgTimeSpent;
    int avgAgentInteraction;
    GeographicalRisk avgLocationRisk;
    Agent* currentAgents;

    public:
    Location();
    int getPopulation();
    Agent* getSusceptible();
    Agent* getInfected();
    Agent* getRecovered();
};

#endif