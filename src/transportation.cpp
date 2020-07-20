/****************
 * COVID-19ABMGuelphS20
 * 20/07/20
 * ver 0.02
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

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, getLocationListLength() - 1);

    for(int i = 0; i < arrSize; i++){
        locationList.at(distr(gen)).addAgentToSusceptible(arr[i]);
    }


    int popTotal = 0;
    for(int i = 0; i < getLocationListLength(); i++){
        cout << locationList.at(i).getSusceptibleSize() << endl;
        popTotal += locationList.at(i).getSusceptibleSize();
    }

    cout << "******" << popTotal << "******" << endl;

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