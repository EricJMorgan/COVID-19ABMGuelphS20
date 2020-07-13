/****************
 * COVID-19ABMGuelphS20
 * 07/07/20
 * ver 0.02
 * 
 * This is the main for the COVID-19 eABM
 ***************/


#include <iostream>
#include "simulation.hh"
#include "postalCodeHash.hh"
#include "agent.hh"

int main(){

    //Simulation sim = Simulation("demographicGuelph.csv");
    // for(int i = 0; i < 131805; i++){
    //     cout << sim.getAgentAt(i).agentToString() << endl;
    // }

    PostalCodeHash postalCodeStuff = PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
    for(int i = 0; i < 5000; i++){
        if(postalCodeStuff.hashTable[i].postalCode.compare("") != 0){
            cout << postalCodeStuff.hashTable[i].postalCode << " ";
                for(int j = 0; j < 9; j++){
                    cout << postalCodeStuff.hashTable[i].locationCount[j] << " ";
                }
            cout << endl;
        }
    }

    return 0;
}
