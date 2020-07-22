/****************
 * COVID-19ABMGuelphS20
 * 21/07/20
 * ver 0.06
 * 
 * This is the header file for the agent class
 ***************/


#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include <iostream>
#include <boost/assign/list_of.hpp>
#include <map>
#include "SIR.hh"
#pragma once

using namespace std;

// Household income groups
enum HouseholdIncome { H0TO4, H5TO9, H10TO14, H15TO19, H20TO29, H30TO39, H40TO49, H50TO59, H60TO79, H80TO99, H100TO124, H125TO149, H150, HNA};

static std::map<HouseholdIncome, std::string> HouseholdIncomeMap = boost::assign::map_list_of(H0TO4, "$0-$4,999")(H5TO9, "$5,000-$9,999")(H10TO14, "$10,000-$14,999")
(H15TO19, "$15,000-$19,999")(H20TO29, "$20,000-$29,999")(H30TO39, "$30,000-$39,999")(H40TO49, "$40,000-$49,999")(H50TO59, "$50,000=$59,999")(H60TO79, "$60,000-$79,999")
(H80TO99, "$80,000-$99,999")(H100TO124, "$100,000-$124,999")(H125TO149, "$125,000-$149,999")(H150, "$150,000+")(HNA, "N/A");

// Education level for agent
enum Education { NOCERTIF, HIGHSCHOOL, APPRENTICESHIP, COLLEGE, BELOWDEGREE, UNIVERSITY, NA};

static std::map<Education, std::string> EducationMap = boost::assign::map_list_of(NOCERTIF, "No Certifcation")(HIGHSCHOOL, "Highschool")(APPRENTICESHIP, "Apprenticeship")
(COLLEGE, "College")(BELOWDEGREE, "Below Degree")(UNIVERSITY, "University")(NA, "N/A");

//Forward declare Location class
class Location;
//Declare simulation class
class Agent : public SIR {
    public:
    AgentInfo getAgentInfo();
    string getEthnicity();
    string agentToString();


    /**
     * Agent
     * 
     * This is the constructor for the agent class it takes in the the gender/age enum and gives it 
     * a race, income, education, and marital status
     * 
     * @param agentInfo, the enum of the gender/Age based on the AgentInfo enum
     */
    Agent(AgentInfo agentInfo);

    /**
     * goGrocery
     * 
     * This tells the specific agent to go to the closest grocery store
     */
    void goGrocery();

    /**
     * goWork
     * 
     * This tells the agent to go to its job so its not a freeloading hippie
     */
    void goWork();

    /**
     * goSchool
     * 
     * This tells the agent to go to school
     */
    void goSchool();

    /**
     * goHome
     * 
     * This tells the agent to go to its house
     */
    void goHome();

    //To be implemented later
    void quarantineTime();
    void goodHygiene();
    void followWearMask();
    void followSocialDistancing();

    bool agentHygiene;
    bool wearingMask;
    
    private:
    HouseholdIncome income;
    string ethnicity;
    string maritalStatus;
    Location* address;
    Education education;
    string major;
    bool employment;
    string sector;
    Location* currLocation;

    /**
     * DecideEthnicity
     * 
     * Decides the agents ethnicity based on the stats collected from
     * the canadian census
     */
    void DecideEthnicity();

    /**
     * DecideMartialStatus
     * 
     * Decides the agents MartialStatus based on the status collected
     * from the canadian census
     */
    void DecideMartialStatus();

    /**
     * DecideHouseholdIncome
     * 
     * Decides the agents household income based on the stats
     * collected from the canadian census
     */
    void DecideHouseholdIncome();

    /**
     * DecideEducation
     * 
     * Decides the agents education based on the stats
     * collected from the canadian census
     */
    void DecideEducation();

    /**
     * DecideMigitationStrategy
     * 
     * Decides the agents chance of wearing a mask and following appropriate hygiene
     * 
     */
    void DecideMigitationStrategy();
};

#endif
