 /****************
 * COVID-19ABMGuelphS20
 * 13/10/20
 * ver 1.04
 * 
 * This is the header file for the hospital class. The purpose of
 * this class is to keep track of hopsital statistics. Mainly the amount
 * of beds being used and the amount of ICU beds being used.
 ***************/


#ifndef HOSPITAL_H_
#define HOSPITAL_H_

#include <string>
#include <iostream>
#include <vector>
#include "agent.hh"

using namespace std;

//Declare simulation class
class Hospital {
    public:
    /**
     * Hospital
     * 
     * This is the default constructor for the hospital object
     */
    Hospital();

    /**
     * freeIcuBeds
     * 
     * This function frees up ICU beds upon patient's recovery or death
     * 
     * @param freeNum this is the number of beds to be freed
     */
    void freeIcuBeds(int freeNum);

    /**
     * freeHospitalBeds
     * 
     * This function frees up hospital beds (excluding ICU beds) upon patient's
     * recovery or death
     * 
     * @param freeNum this is the number of beds to be freed
     */
    void freeHospitalBeds(int freeNum);

    /**
     * increaseHospitcalCount
     * 
     * This function adds agents to the hospital if they are in need of hospital
     * care
     * 
     * @param agentToAdd this is the agent to be emitted to the hospital
     */
    void increaseHospitalCount(Agent* agentToAdd);

    /**
     * increaseIcuCount
     * 
     * This function adds agents from the hospital to ICU if they are in need of
     * critical care
     * 
     * @param agentToAdd this is the agent to be emitted to ICU
     */
    void increaseIcuCount(Agent* agentToAdd);

    /**
     * getTotalBeds
     * 
     * This function returns the number of agents using hospital beds
     * 
     * @return the number of agents in hospital care excluding ICU cases
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

    /**
     * HospitalTimeStep
     * 
     * This moves the Agents currently in the hospital through an SIR timestep
     * and then determines if the agent needs to be moved to a different stage
     * 
     * @param the timestep size
     */
    void HospitalTimeStep(double timestep);

     /**
     * getTotalICUCount
     * 
     * This gets the total number of agents ever put in intensive care unit
     */
    int getTotalICUCount();

    /**
     * getTotalHospitalCount
     * 
     * This gets the total number of agents ever put in the hospital
     */
    int getTotalHospitalCount();

    /**
     * setAgentRecoveryTime
     * 
     * This will set each age ranges time too recovery from
     * the given virus. Age ranges are 0 = 0 - 4, 1 = 5 - 9 ...
     * 
     * @param int ageRange in range 0 - 17
     * @param short value in range 0 - 127
     */
    void setAgentRecoveryTime(int ageRange, short value);

    /**
     * setAgentDeathChance
     * 
     * This will set each age ranges chance too die from
     * the given virus. Age ranges are 0 = 0 - 4, 1 = 5 - 9...
     * 
     * @param int ageRange in range 0 -17
     * @param double value in range 0 - 1.0
     */
    void setAgentDeathChance(int ageRange, double value);

    /**
     * getAgentRecoveryTime
     * 
     * This will get the given ages time to recover
     * where ageRange is 0 = 0 -4, 1 = 5 - 9.
     * 
     * @param ageRange the age of the wanted recovery time in range 0 - 17.
     * @return a short of the time it takes for the agent to recover
     */
    short getAgentRecoveryTime(int ageRange);

    /**
     * getAgentDeathChance
     * 
     * This will get the given ages chance of death where
     * ageRange is 0 = 0 - 4, 1 = 5 - 9, etc.
     * 
     * @param ageRange the age of the wanted death chance in range 0 - 17.
     * @return a double of the chance of death
     */
    double getAgentDeathChance(int ageRange);

    // returns to be read and cleared
    std::vector<Agent *> newlyDeceased;
    std::vector<Agent *> newlyRecovered;

    private:
    const int totalBedCount = 130;  //excluding ICU beds
    const int icuBedCount = 22;     //total ICU beds
    int numberPpl;                  //excluding ICU patients
    int icuCount;                   //total ICU patients
    bool hospitalOverflow; //TODO figure out how to handle overflow
    bool icuOverflow;
    int totalICU;
    int totalHospital;

    short agentRecoveryTime[18];
    double agentDeathChance[18];

    std::vector<Agent *> hospitalGeneralWard; // Agents admitted to general hospital
    std::vector<Agent *> hospitalICU;         // Agents admitted to ICU

    /**
     * indicateOverflow
     * 
     * This function checks if the hospital has exceeded its bed limitations for
     * either ICU or non-ICU beds; the simulation continues to run even when there
     * is an overflow
     */
    void indicateOverflow();
};

#endif
