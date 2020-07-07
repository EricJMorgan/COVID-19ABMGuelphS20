/****************
 * COVID-19ABMGuelphS20
 * 07/07/20
 * ver 0.03
 * 
 * This is the header file for the agent class
 ***************/


#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include <iostream>
#include <boost/assign/list_of.hpp>
#include <map>
#pragma once

using namespace std;

enum AgentInfo { MALE0TO4, MALE5TO9, MALE10TO14, MALE15TO19, MALE20TO24, MALE25TO29, MALE30TO34, MALE35TO39, MALE40TO44, MALE45TO49,
                MALE50TO54, MALE55TO59, MALE60TO64, MALE65TO69, MALE70TO74, MALE75TO79, MALE80TO84, MALE85, FEMALE0TO4, FEMALE5TO9, 
                FEMALE10TO14, FEMALE15TO19, FEMALE20TO24, FEMALE25TO29, FEMALE30TO34, FEMALE35TO39, FEMALE40TO44, FEMALE45TO49,
                FEMALE50TO54, FEMALE55TO59, FEMALE60TO64, FEMALE65TO69, FEMALE70TO74, FEMALE75TO79, FEMALE80TO84, FEMALE85 };

enum HouseholdIncome { H0TO4, H5TO9, H10TO14, H15TO19, H20TO29, H30TO39, H40TO49, H50TO59, H60TO79, H80TO99, H100TO124, H125TO149, H150, HNA};

static std::map<std::string, AgentInfo> AgentInfoMap = boost::assign::map_list_of("Male 0-4", MALE0TO4)("Male 5-9", MALE5TO9)("Male 10-14", MALE10TO14)
("Male 15-19", MALE15TO19)("Male 20-24", MALE20TO24)("Male 25-29", MALE25TO29)("Male 30-34", MALE30TO34)("Male 35-39", MALE35TO39)
("Male 40-44", MALE40TO44)("Male 45-49", MALE45TO49)("Male 50-54", MALE50TO54)("Male 55-59", MALE55TO59)("Male 60-64", MALE60TO64)("Male 65-69", MALE65TO69)
("Male 70-74", MALE70TO74)("Male 75-79", MALE75TO79)("Male 80-84", MALE80TO84)("Male 85", MALE85)("Female 0-4", FEMALE0TO4)("Female 5-9", FEMALE5TO9)
("Female 10-14", FEMALE10TO14)("Female 15-19", FEMALE15TO19)("Female 20-24", FEMALE20TO24)("Female 25-29", FEMALE25TO29)("Female 30-34", FEMALE30TO34)
("Female 35-39", FEMALE35TO39)("Female 40-44", FEMALE40TO44)("Female 45-49", FEMALE45TO49)("Female 50-54", FEMALE50TO54)("Female 55-59", FEMALE55TO59)
("Female 60-64", FEMALE60TO64)("Female 65-69", FEMALE65TO69)("Female 70-74", FEMALE70TO74)("Female 75-79", FEMALE75TO79)("Female 80-84", FEMALE80TO84)
("Female 85", FEMALE85);

class Location;
//Declare simulation class
class Agent{
    private:
    AgentInfo info;
    HouseholdIncome income;
    string ethnicity;
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
    Agent(AgentInfo agentInfo);
    void goGrocery();
    void goWork();
    void goSchool();
    void goHome();
    void quarantineTime();
    void goodHygiene();
    void followWearMask();
    void followSocialDistancing();
    void DecideEthnicity();
    void DecideMartialStatus();
    void DecideHouseholdIncome();
    AgentInfo getAgentInfo();
    string getEthnicity();
};

#endif