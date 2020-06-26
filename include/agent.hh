/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the header file for the agent class
 ***************/


#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include <iostream>
//#include "location.hh"

using namespace std;

//Declare simulation class
class Agent{
    private:
    int age;
    string ethnicity;
    string gender;
    string maritalStatus;
    //TYPE addrress;
    string education;
    string major;
    bool employment;
    string sector;
    bool hygiene;
    bool socialDistancing;
    bool wearingMask;
    //TYPE currLocation;

    public:
    Agent();
    void goGrocery();
    void goWork();
    void goSchool();
    void goHome();
    void brownianMotion();
    void quarantineTime();
    void goodHygiene();
    void followWearMask();
    void followSocialDistancing();
};

#endif