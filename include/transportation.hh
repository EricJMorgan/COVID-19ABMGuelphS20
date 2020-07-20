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
#include "agent.hh"

using namespace std;

//Forward declarations
// class Location;
// class Agent;
//sclass Simulation;
//class PostalCodeHash;

//Declare simulation class
class Transportation {
    public:
    /**
     * Transportation
     * 
     * This is the default constructor for the Transportation
     * class
     * 
     */
    Transportation(Agent **arr, int arrSize);

    ~Transportation();

    /**
     * getLocationListLength
     * 
     * This gets the length of the location list
     * that is generated what the object is made
     * 
     * @return the length of the internal List
     */
    int getLocationListLength();

    /**
     * getLocationAt
     * 
     * This gets the location data from a given index
     * due to the location never changing it only returns
     * a copy of the object
     * 
     * @param index, the index of the wanted data must be in range 0 <= index < listLength
     * @return a copy of the location object
     */
    Location getLocationAt(int index);


    private:
    PostalCodeHash *postalCodes;
    std::vector<Location> locationList;

};


#endif
