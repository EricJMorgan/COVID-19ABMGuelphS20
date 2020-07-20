/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the transportation class
 ***************/


#ifndef TRANSPORTATION_H_
#define TRANSPORTATION_H_

#include <string>
#include <iostream>
#include <vector>

#include "postalCodeHash.hh"

using namespace std;

//Forward declarations
// class Location;
// class Agent;
//sclass Simulation;
//class PostalCodeHash;

//Declare simulation class
class Transportation {
    public:
    Transportation();
    int getLocationListLength();
    Location getLocationAt(int index);


    private:
    PostalCodeHash *postalCodes;
    std::vector<Location> locationList;

};


#endif
