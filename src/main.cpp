/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the main for the COVID-19 eABM
 ***************/


#include <iostream>
#include "simulation.hh"

int main(){

    Simulation sim;
    sim.setUpAgents("demographicGuelph.csv");


    return 0;
}
