/****************
 * COVID-19ABMGuelphS20
 * 26/06/20
 * ver 0.01
 * 
 * This is the class file for the agent class
 ***************/


#include <iostream>
#include "agent.hh"

// Constructor
Agent::Agent(AgeGroup agegroup, string agentGender) {
    age = agegroup;
    gender = agentGender;
}