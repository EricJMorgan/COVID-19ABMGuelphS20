/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
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
