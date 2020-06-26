/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the header file for the simulation class
 ***************/


#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>

using namespace std;

//Declare simulation class
class Simulation{
    private:
    string name;
    int susceptible;
    int infected;
    int recovered;
    int deceased;
    int vaccinated;

    public:
    Simulation();
    void makeGraph();
    void displayMap();
};


#endif