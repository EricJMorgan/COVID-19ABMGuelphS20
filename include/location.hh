#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>
#include <iostream>
#include "../include/agent.hh"

using namespace std;

//Declare simulation class
class Location {
    private:
    string name;
    string sector;
    int population;
    //TYPE location;

    public:
    int getPopulation();
    Agent* getSusceptible();
    Agent* getInfected();
    Agent* getRecovered();

};

#endif