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

enum AgeGroup { };
enum HouseholdIncome { };

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
    Agent();
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