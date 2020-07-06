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

using namespace std;

enum TransportType { BUS, CAR, WALK };

//Forward declarations
class Location;
class Agent;

//Declare simulation class
class Transportation {
    private:
    TransportType type;
    Location* destination;
    bool isStillInTransport;

    public:
    Transportation();
    void selectBestPath();
    void jumpCompartment();
    void determineAgentDestination();
};


#endif
