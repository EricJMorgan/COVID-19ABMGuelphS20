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

using namespace std;

//Declare simulation class
class Location {
    private:
    string name;
    string sector;
    int population;
    //TYPE location;

    public:
    Location();
    int getPopulation();
    Agent* getSusceptible();
    Agent* getInfected();
    Agent* getRecovered();

};

#endif