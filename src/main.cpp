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

    Simulation sim = Simulation("demographicGuelph.csv");
    for(int i = 0; i < 131805; i++){
        cout << sim.getAgentAt(i).getAgentInfo() << " " << sim.getAgentAt(i).getEthnicity() << endl;
    }

    return 0;
}
