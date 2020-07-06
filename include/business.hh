/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the header file for the business class
 ***************/


#ifndef BUSINESS_H_
#define BUSINESS_H_

#include <string>
#include <iostream>

using namespace std;

enum BusinessTypes { SCHOOL, MALL, ETC };

//Declare simulation class
class Business {
    private:
    bool isEssential;
    int openHour;
    int closeHours;
    BusinessTypes businessType;

    public:
    Business();
    void shutDown();
};

#endif
