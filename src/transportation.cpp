/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the class file for the transportation class
 ***************/


#include "transportation.hh"
#include <iostream>
#include <string>

using namespace std;

Transportation::Transportation(Agent **arr, int arrSize){
    postalCodes = new PostalCodeHash("placeData.tsv", "AllPostalCodes.csv", 7000);
    for(int i = 0; i < 7000; i++){
        if(postalCodes->hashTable[i].getPostalCodeGrouping().compare("") != 0){
            locationList.push_back(postalCodes->hashTable[i]);
        }
    }
    for(int i = 0; i < arrSize; i++){
        //cout << arr[i]->DetermineSeverity() << endl;
    }

}

Transportation::~Transportation(){
    delete postalCodes;
}

int Transportation::getLocationListLength(){
    return (int)locationList.size();
}

Location Transportation::getLocationAt(int index){
    if(index < 0 || index >= getLocationListLength()) return Location();
    return locationList.at(index);
}