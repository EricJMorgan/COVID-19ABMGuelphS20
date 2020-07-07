/****************
 * COVID-19ABMGuelphS20
 * 07/07/20
 * ver 0.02
 * 
 * This is the main for the COVID-19 eABM
 ***************/


#include <iostream>
#include "simulation.hh"
#include "postalCode.hh"
#include "agent.hh"

int main(){

    Simulation sim;
    sim.setUpAgents("demographicGuelph.csv");
    for(int i = 0; i < 3876; i++){
        cout << sim.getAgentAt(i).getAgentInfo() << endl;
    }

    return 0;
}
