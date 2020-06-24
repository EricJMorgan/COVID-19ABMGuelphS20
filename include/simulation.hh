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
    void makeGraph();
    void displayMap();
};


#endif