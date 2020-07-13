#ifndef POSTALCODEHASH_H_
#define POSTALCODEHASH_H_

#include "location.hh"

class PostalCodeHash{
    private:
    /**
     * getPostalCode
     * 
     * This takes in the full address string given from the google places API
     * and gets just the postal code from it. 
     * NOTE, as of now the format by default is incorrect as it has the province 
     * and the postal code not sepreated by a comma so that must be changed before using
     * anything
     * 
     * @param fullAddress, the address in the google api printout format
     * @return the string of the postal Code in the format LNL NLN
     */
    string getPostalCode(string fullAddress);
    /**
     * placePostalInHash
     * 
     * This function takes in the postal code and hash table size and
     * places the postal code into the hash table
     * 
     * @param newPostalCode, string of the postal code
     * @param hashSize, the size of the hash table
     */
    void placePostalInHash(string newPostalCode, int hashSize);
    /**
     * placePostalInHash
     * 
     * This function takes in the postal code, location type and hash table size and
     * places the postal code into the hash table
     * 
     * @param newPostalCode, string of the postal code
     * @param locationName, string of the location type.
     * @param hashSize, the size of the hash table
     */
    void placePostalInHash(string newPostalCode, string locationName, int hashSize);
    /**
     * openFile
     * 
     * This fucktion takes in a file name,
     * opens and checks it validity before returns a ifstream object
     * 
     * @param fileName, name of the wanted file
     * @return the ifstream object of the file, will be closed if invalid
     */
    ifstream openFile(string fileName);

    public:
    /**
     * PostalCodeHash
     * 
     * This is the constructor for the postalcode hash object
    PostalCodeHash(string tsvFile, string evenMoreLocations, int hashSize);
    ~PostalCodeHash();
    static int getPostalHash(int hashSize, string postalTSVToHash);

    Location *hashTable;
};

#endif