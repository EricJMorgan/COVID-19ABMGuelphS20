#ifndef POSTALCODEHASH_H_
#define POSTALCODEHASH_H_

#include "location.hh"

class PostalCodeHash{
    private:
    string getPostalCode(string fullAddress);

    public:
    PostalCodeHash(string tsvFile, int hashSize);
    ~PostalCodeHash();
    Location *hashTable;
    static int getPostalHash(int hashSize, string postalTSVToHash);
};

#endif