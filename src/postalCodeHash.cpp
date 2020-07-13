/****************
 * COVID-19ABMGuelphS20
 * 13/07/20
 * ver 0.03
 * 
 * This is the source code for the postalCodeHash object for the COVID-19 eABM
 ***************/

#include "postalCodeHash.hh"
#include <boost/algorithm/string.hpp>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "location.hh"

PostalCodeHash::PostalCodeHash(string tsvFile, string evenMoreLocations, int hashSize){
    ifstream toParse;
    string holder;
    string currPostalCode;
    hashTable = new Location[hashSize];

    toParse = openFile(tsvFile);
    if(toParse.is_open()){
        while(getline(toParse, holder)){
            vector<string> tabValues;
            split(tabValues, holder, boost::is_any_of("\t"));//Splits data into vector holder
            if(tabValues.size() != 6) continue;
            currPostalCode = getPostalCode(tabValues[1]);
            placePostalInHash(currPostalCode, tabValues[5] , hashSize);
        }
        toParse.close();
    }

    toParse = openFile(evenMoreLocations);
    if(toParse.is_open()){
        while(getline(toParse, holder)){
            placePostalInHash(holder, hashSize);
        }
        toParse.close();
    }
}

PostalCodeHash::~PostalCodeHash(){
    delete[] hashTable;
}

int PostalCodeHash::getPostalHash(int hashSize, string postalCodeToHash){
    if(postalCodeToHash.length() <= 3) return 0;

    int hashTotal = 0;
    for(int i = 0; i < (int)postalCodeToHash.length(); i++){
        if(postalCodeToHash.at(i) == ' ');//Every postal code has a space so no need for adding it to the hash total
        else{
            if(isalpha(postalCodeToHash.at(i))){
                hashTotal += (postalCodeToHash.at(i) - 65) * pow(5, i);
            }else{
                hashTotal += (postalCodeToHash.at(i)) * pow(7, i);
            }
        }
    }

    return hashTotal % (hashSize - 1);
}

/*************************PRIVATE FUNCTIONS******************************/


string PostalCodeHash::getPostalCode(string fullAddress){
    if(fullAddress.empty()) return "";
    vector<string> commaValues;//Comma holder
    split(commaValues, fullAddress, boost::is_any_of(","));
    for(int i = 0; i < (int)commaValues.size(); i++){
        if(commaValues[i].length() == 7 || commaValues[i].length() == 3){
            if(isalpha(commaValues[i][0]) && isdigit(commaValues[i][1]) && isalpha(commaValues[i][2])) return commaValues[i];
        }
    }

    return "unknown";
}


ifstream PostalCodeHash::openFile(string fileName){
    ifstream fileHolder;
    fileHolder.open(fileName, ios::in);//open the file for reading
    if(!fileHolder.good()){
        fileHolder.close();
    }
    return fileHolder;
}


void PostalCodeHash::placePostalInHash(string newPostalCode, int hashSize){
    int currHashValue;
    bool placed;
    if(newPostalCode.compare("unknown") == 0);
    else{
        currHashValue = PostalCodeHash::getPostalHash(hashSize, newPostalCode);
        placed = false;
            while(placed == false){
            if(hashTable[currHashValue].postalCode.compare("") == 0){//If the bucket is empty
                hashTable[currHashValue].postalCode = newPostalCode;
                placed = true;
            }else if(hashTable[currHashValue].postalCode.compare(newPostalCode) == 0){//If the bucket has the same postal code
                placed = true;
            }else{//If occupied by a differnt postal code go to the next one
                if(currHashValue == hashSize - 1) currHashValue = 0;
                else currHashValue++;
            }
        }
    }
}


void PostalCodeHash::placePostalInHash(string newPostalCode, string locationName, int hashSize){
    int currHashValue;
    bool placed;

    if(newPostalCode.compare("unknown") == 0);
    else{
        currHashValue = PostalCodeHash::getPostalHash(hashSize, newPostalCode);
        placed = false;
            while(placed == false){
            if(hashTable[currHashValue].postalCode.compare("") == 0){//If the bucket is empty
                hashTable[currHashValue].postalCode = newPostalCode;
                hashTable[currHashValue].locationCount[locationTypeMap[locationName]]++;
                placed = true;
            }else if(hashTable[currHashValue].postalCode.compare(newPostalCode) == 0){//If the bucket has the same postal code
                hashTable[currHashValue].locationCount[locationTypeMap[locationName]]++;
                placed = true;
            }else{//If occupied by a differnt postal code go to the next one
                if(currHashValue == hashSize - 1) currHashValue = 0;
                else currHashValue++;
            }
        }
    }
}
