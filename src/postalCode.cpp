 /****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.01
 * 
 * This is the src file for the postalCode classes
 ***************/

#include "postalCode.hh"

#include <boost/algorithm/string.hpp>
#include <ctype.h>
#include <math.h>
#include <vector>
#include <fstream>
#include <iostream>

//Default constructor for creating arrays of postal codes
PostalCodeData::PostalCodeData(){
    PostalCodeData("");
}

//Constructor fills postal code string and sets all locationcounts to 0
PostalCodeData::PostalCodeData(string newPostalCode){
    postalCode = newPostalCode;
    for(int i = 0; i < 9; i++){
        locationCount[i] = 0;
    }
}




/*********************************************************************/
/*************************
 * PostalCodeHash
 * 
 * This is the constructor. When called it will take a file and
 * size of the hash table(will be changed later to be smart). It will
 * then generate the hash table for the postal code data which can be accessed as
 * it is public.
 ************************/
PostalCodeHash::PostalCodeHash(string tsvFile, int hashSize){
    ifstream toParse;
    string holder;
    string currPostalCode;
    bool placed;
    int currHashValue;
    hashTable = new PostalCodeData[hashSize];

    toParse.open(tsvFile, ios::in);//open the file for reading
    if(!toParse.good()){
        hashTable = NULL;
        return;
    }
    
    while(getline(toParse, holder)){
        vector<string> tabValues;
        split(tabValues, holder, boost::is_any_of("\t"));//Splits data into vector holder

        currPostalCode = getPostalCode(tabValues[1]);
        if(currPostalCode.compare("unknown") == 0);
        else{
            currHashValue = PostalCodeHash::getPostalHash(hashSize, currPostalCode);
            placed = false;
             while(placed == false){
                if(hashTable[currHashValue].postalCode.compare("") == 0){//If the bucket is empty
                    hashTable[currHashValue].postalCode = currPostalCode;
                    hashTable[currHashValue].locationCount[locationTypeMap[tabValues[5]]]++;
                    placed = true;
                }else if(hashTable[currHashValue].postalCode.compare(currPostalCode) == 0){//If the bucket has the same postal code
                    hashTable[currHashValue].locationCount[locationTypeMap[tabValues[5]]]++;
                    placed = true;
                }else{//If occupied by a differnt postal code go to the next one
                    if(currHashValue == hashSize - 1) currHashValue = 0;
                    else currHashValue++;
                }
            }
        }
    }
    toParse.close();
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

/*************************
 * getPostalCode
 * 
 * This takes in the full address string given from the google places API
 * and gets just the postal code from it. 
 * NOTE, as of now the format by default is incorrect as it has the province 
 * and the postal code not sepreated by a comma so that must be changed before using
 * anything
 ************************/
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

