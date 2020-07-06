/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.02
 * 
 * This is the header file for the agent class
 ***************/


#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include <iostream>
#pragma once

using namespace std;

enum AgeGroup { MALE0TO4, MALE5TO9, MALE10TO14, MALE15TO19, MALE20TO24, MALE25TO29, MALE30TO34, MALE35TO39, MALE40TO44, MALE45TO49,
                MALE50TO54, MALE55TO59, MALE60TO64, MALE65TO69, MALE70TO74, MALE75TO79, MALE80TO84, MALE85, FEMALE0TO4, FEMALE5TO9, 
                FEMALE10TO14, FEMALE15TO19, FEMALE20TO24, FEMALE25TO29, FEMALE30TO34, FEMALE35TO39, FEMALE40TO44, FEMALE45TO49,
                FEMALE50TO54, FEMALE55TO59, FEMALE60TO64, FEMALE65TO69, FEMALE70TO74, FEMALE75TO79, FEMALE80TO84, FEMALE85 };

enum HouseholdIncome { H0TO4, H5TO9, H10TO14, H15TO19, H20TO29, H30TO39, H40TO49, H50TO59, H60TO79, H80TO99, H100TO124, H125TO149, H150};

class Location;
//Declare simulation class
class Agent{
    private:
    AgeGroup age;
    HouseholdIncome income;
    string ethnicity;
    string gender;
    string maritalStatus;
    Location* address;
    string education;
    string major;
    bool employment;
    string sector;
    bool hygiene;
    bool socialDistancing;
    bool wearingMask;
    Location* currLocation;

    public:
    Agent(AgeGroup agegroup, string agentGender);
    void goGrocery();
    void goWork();
    void goSchool();
    void goHome();
    void quarantineTime();
    void goodHygiene();
    void followWearMask();
    void followSocialDistancing();
};

#endif