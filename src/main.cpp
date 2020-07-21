/****************
 * COVID-19ABMGuelphS20
 * 20/07/20
 * ver 0.07
 * 
 * This is the main for the COVID-19 eABM
 ***************/


#include <iostream>
#include <time.h>
#include "simulation.hh"
//testing
#include "postalCodeHash.hh"
#include "agent.hh"


int main(){

    srand((unsigned int)time(NULL));

    Simulation sim = Simulation("demographicGuelph.csv");
    for(int i = 0; i < 10; i++){
        cout << sim.getAgentAt(i).agentToString() << endl;
    }

    sim.getAgentAt(0).AgentInfected();

    PostalCodeHash postalCodeStuff = PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
    // for(int i = 0; i < 14; i++){
    //     if(postalCodeStuff.hashTable[i].getPostalCodeGrouping().compare("") != 0){
    //         cout << postalCodeStuff.hashTable[i].getPostalCodeGrouping() << " ";
    //         for(int k = 0; k < LOCATIONTYPESIZE; k++){
    //             cout << postalCodeStuff.hashTable[i].getLocationCountAt(k) << " ";
    //         }
    //         cout << endl;
    //         for(int j = 0; j < (int)postalCodeStuff.hashTable[i].getPostalCodeListLength(); j++){
    //             cout << postalCodeStuff.hashTable[i].getPostalCodeAt(j) << ", ";
    //         }
    //         cout << endl << endl;
    //     }
    // }

    // testing geographical risk stuff
    // for(int k = 0; k < LOCATIONTYPESIZE; k++){
    //     cout << postalCodeStuff.hashTable[0].getLocationCountAt(k) << " ";
    // }
    // cout << endl;
    // for(int j = 0; j < (int)postalCodeStuff.hashTable[0].getPostalCodeListLength(); j++){
    //     cout << postalCodeStuff.hashTable[0].getPostalCodeAt(j) << ", ";
    // }

    // postalCodeStuff.hashTable[0].addAgentToInfected(&sim.getAgentAt(0));
    // for(int i = 1; i < 10; i++){
    //     postalCodeStuff.hashTable[0].addAgentToSusceptible(&sim.getAgentAt(i));
    // }

    // postalCodeStuff.hashTable[0].infectPeople();


    // testing SIR Model
    // Agent* tempAgent = new Agent(AgentInfoMap["Male 20-24"]);
    // cout << tempAgent->DetermineSeverity() << endl;
    // tempAgent->AgentInfected();
    // while (tempAgent->DetermineSeverity() != RECOVERED && tempAgent->DetermineSeverity() != DECEASED) {
        // cout << tempAgent->DetermineSeverity() << "yesirr" << endl;
    //     tempAgent->SIRTimeStep(1);
    // }

    // cout << tempAgent->DetermineSeverity() << endl;

    // free(tempAgent);


    
    return 0;
}
