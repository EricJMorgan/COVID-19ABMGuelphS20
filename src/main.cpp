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
    // for(int i = 0; i < 131805; i++){
    //     cout << sim.getAgentAt(i).agentToString() << endl;
    // }

    PostalCodeHash postalCodeStuff = PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
    // for(int i = 0; i < 7000; i++){
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
    
    return 0;
}