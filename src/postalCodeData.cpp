 /****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.01
 * 
 * This is the src file for the postalCode classes
 ***************/

#include "postalCodeData.hh"


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




