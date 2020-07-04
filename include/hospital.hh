 /****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the header file for the hospital class
 ***************/


#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include <string>
#include <iostream>
#include "location.hh"

using namespace std;

//Declare simulation class
class Hospital: public Location {
    private:
    int totalBedCount;
    int icuBedCount;
    int numberPpl;

    public:
    Hospital();
    void FreeBeds();
    void IndicateOverflow();
    void IncreaseHospitalCount();
};

#endif
