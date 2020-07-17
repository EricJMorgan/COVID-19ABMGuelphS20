 /****************
 * COVID-19ABMGuelphS20
 * 17/07/20
 * ver 0.03
 * 
 * This is the header file for the hospital class
 ***************/


#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include <string>
#include <iostream>

using namespace std;

//22 intensive care
//62 surgery
//8 Paediatrics/children
//68 medicine
//22 obsterics/childbirth

//Declare simulation class
class Hospital {
    private:
    static int totalBedCount; //excluding ICU beds
    static int icuBedCount;   //total ICU beds
    int numberPpl;            //excluding ICU patients
    int icuCount;             //total ICU patients

    public:
    /**
     * Hospital
     * 
     * This is the default constructor for the location object
     */
    Hospital();

    /**
     * freeIcuBeds
     * 
     * This function frees up ICU beds upon patient's recovery or death
     * 
     * @param freeNum, this is the number of beds to be freed
     */
    void freeIcuBeds(int freeNum);

    /**
     * freeHospitalBeds
     * 
     * This function frees up hospital beds (excluding ICU beds) upon patient's
     * recovery or death
     * 
     * @param freeNum, this is the number of beds to be freed
     */
    void freeHospitalBeds(int freeNum);

    /**
     * indicateOverflow
     * 
     * This function checks if the hospital has exceeded its bed limitations for
     * either ICU or non-ICU beds; the simulation continues to run even when there
     * is an overflow
     */
    void indicateOverflow();

    /**
     * increaseHospitcalCount
     * 
     * This function adds agents to the hospital if they are in need of hospital
     * care
     * 
     * @param numAgents, this is the number of agents to be emitted to the hospital
     */
    void increaseHospitalCount(int numAgents);

    /**
     * increaseIcuCount
     * 
     * This function adds agents from the hospital to ICU if they are in need of
     * critical care
     * 
     * @param numAgents, this is the number of agents to be emitted to ICU
     */
    void increaseIcuCount(int numAgents);

    /**
     * getTotalBeds
     * 
     * This function returns the number of agents using hospital beds
     * 
     * @return the number of agents in hospital care, excluding ICU cases
     */
    int getTotalBeds();

    /**
     * getIcuBeds
     * 
     * This function returns the number of agents in ICU care
     * 
     * @return the number of agents in ICU cases
     */
    int getIcuBeds();
};

#endif
