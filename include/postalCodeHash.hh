#ifndef POSTALCODEHASH_H_
#define POSTALCODEHASH_H_

#include "location.hh"

class PostalCodeHash{
    private:
    string getPostalCode(string fullAddress);
    void placePostalInHash(string newPostalCode, int hashSize);
    void placePostalInHash(string newPostalCode, string locationName, int hashSize);
    ifstream openFile(string fileName);

    public:
    PostalCodeHash(string tsvFile, string evenMoreLocations, int hashSize);
    ~PostalCodeHash();
    Location *hashTable;
    static int getPostalHash(int hashSize, string postalTSVToHash);
};

#endif