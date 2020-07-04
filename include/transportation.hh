/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the header file for the transportation class
 ***************/


#ifndef TRANSPORTATION_H_
#define TRANSPORTATION_H_

#include <string>
#include <iostream>
#include <location.hh>
#include <agent.hh>

using namespace std;

enum TransportType { BUS, CAR, WALK };

//Declare simulation class
class Transportation {
    private:
    TransportType type;
    Location guelphBusRoutes[];
    Location agentOrigin;
    Location agentDestination;
    Agent currAgent;

    public:
    Transportation();
    void selectBestPath();
    void jumpCompartment();
    void determineAgentDestination();
};


#endif
