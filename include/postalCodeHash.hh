/****************
 * COVID-19ABMGuelphS20
 * 15/07/20
 * ver 0.04
 * 
 * This is the header file for the postalCodeHash object for the COVID-19 eABM
 ***************/

#ifndef POSTALCODEHASH_H_
#define POSTALCODEHASH_H_

#include "location.hh"

class PostalCodeHash{
    //PUBLIC FUNCTIONS
    public:
    Location **hashTable;

    /**
     * PostalCodeHash
     * 
     * This is the constructor for the postalcode hash object,
     * it takes in 2 file names representing the google places api printout and a list
     * of postal codes each on a new line and the wanted hashSize
     * NOTE: hashSize will soon be automated but for now it is manual
     * 
     * @param tsvFile, the string of the google places API print out, MUST HAVE POSTAL CODE IN FORMAT of ON,LNL NLN,
     * @param evenMoreLocations, the string of the full postalcode file
     * @param hashSize, the size of the wanted hashtable
     */
    PostalCodeHash(string tsvFile, string evenMoreLocations, int hashSize);

    /**
     * ~PostalCodeHash
     * 
     * This is the deconstructor of the postalCodeHash object
     */
    ~PostalCodeHash();

    /**
     * getPostaLHash
     * 
     * this function will return the hash value of a given postal code
     * 
     * @param hashSize, an int of the size of the hash table
     * @param postalTSVToHash, the string of the postalCode
     */
    static int getPostalHash(int hashSize, string postalTSVToHash);
    //PRIVATE FUNCTIONS
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

    /**
     * getFirstFiveChars
     * 
     * This function takes in a postal code and returns the first 5 chars of the postal code
     * not including the space.
     * 
     * @param fullPostal, This is the full postal code.
     * @return a string in the format LNL NL
     */
    string getFirstFiveChars(string fullPostal);
    
    /**
     * postalCodeListContainsDup
     * 
     * This function takes in the hash value and the postal code and checks the 
     * vector if it already contains the postal code
     * 
     * @param currHashValue, the location in the hashtable
     * @param newPostalCode, the postal code to go into the vector
     * @return returns true if it contains the postal code
     */
    bool postalCodeListContainsDup(int currHashValue, string newPostalCode);
};

#endif