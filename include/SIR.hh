/****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
 * 
 * This is the header file for the SIR class. This is the pipline that moves
 * agents from Susceptible to infected to recoverd. It looks at the agents current infection
 * status and moves them through at the appropriate times. It also decides when an agent dies.
 ***************/


#ifndef SIR_H_
#define SIR_H_

#include <string>
#include <iostream>
#include <map>
#include <boost/assign/list_of.hpp>

using namespace std;

// Various possible age and sex groups 
enum AgentInfo { MALE0TO4, MALE5TO9, MALE10TO14, MALE15TO19, MALE20TO24, MALE25TO29, MALE30TO34, MALE35TO39, MALE40TO44, MALE45TO49,
                MALE50TO54, MALE55TO59, MALE60TO64, MALE65TO69, MALE70TO74, MALE75TO79, MALE80TO84, MALE85, FEMALE0TO4, FEMALE5TO9, 
                FEMALE10TO14, FEMALE15TO19, FEMALE20TO24, FEMALE25TO29, FEMALE30TO34, FEMALE35TO39, FEMALE40TO44, FEMALE45TO49,
                FEMALE50TO54, FEMALE55TO59, FEMALE60TO64, FEMALE65TO69, FEMALE70TO74, FEMALE75TO79, FEMALE80TO84, FEMALE85 };

// assigning age and sex groups to just age groups
static std::map<int, AgentInfo> AgentAgeGroup = boost::assign::map_list_of(0, MALE0TO4)(0, FEMALE0TO4)(1, MALE5TO9)(1, FEMALE5TO9)
(2, MALE10TO14)(2, FEMALE10TO14)(3, MALE15TO19)(3, FEMALE15TO19)(4, MALE20TO24)(4, FEMALE20TO24)(5, MALE25TO29)(5, FEMALE25TO29)
(6, MALE30TO34)(6, FEMALE30TO34)(7, MALE35TO39)(7, FEMALE35TO39)(8, MALE40TO44)(8, FEMALE40TO44)(9, MALE45TO49)(9, FEMALE45TO49)
(10, MALE50TO54)(10, FEMALE50TO54)(11, MALE55TO59)(11, FEMALE55TO59)(12, MALE60TO64)(12, FEMALE60TO64)(13, MALE65TO69)(13, FEMALE65TO69)
(14, MALE70TO74)(14, FEMALE70TO74)(15, MALE75TO79)(15, FEMALE75TO79)(16, MALE80TO84)(16, FEMALE80TO84)(17, MALE85)(17, FEMALE85);

static std::map<AgentInfo, int> AgentAgeGroupReverse = boost::assign::map_list_of(MALE0TO4, 0)(FEMALE0TO4, 0)(MALE5TO9, 1)(FEMALE5TO9, 1)
(MALE10TO14, 2)(FEMALE10TO14, 2)(MALE15TO19, 3)(FEMALE15TO19, 3)(MALE20TO24, 4)(FEMALE20TO24, 4)(MALE25TO29, 5)(FEMALE25TO29, 5)
(MALE30TO34, 6)(FEMALE30TO34, 6)(MALE35TO39, 7)(FEMALE35TO39, 7)(MALE40TO44, 8)(FEMALE40TO44, 8)(MALE45TO49, 9)(FEMALE45TO49, 9)
(MALE50TO54, 10)(FEMALE50TO54, 10)(MALE55TO59, 11)(FEMALE55TO59, 11)(MALE60TO64, 12)(FEMALE60TO64, 12)(MALE65TO69, 13)(FEMALE65TO69, 13)
(MALE70TO74, 14)(FEMALE70TO74, 14)(MALE75TO79, 15)(FEMALE75TO79, 15)(MALE80TO84, 16)(FEMALE80TO84, 16)(MALE85, 17)(FEMALE85, 17);

//converting strings to enums and vice versa
static std::map<std::string, AgentInfo> AgentInfoMap = boost::assign::map_list_of("Male 0-4", MALE0TO4)("Male 5-9", MALE5TO9)("Male 10-14", MALE10TO14)
("Male 15-19", MALE15TO19)("Male 20-24", MALE20TO24)("Male 25-29", MALE25TO29)("Male 30-34", MALE30TO34)("Male 35-39", MALE35TO39)
("Male 40-44", MALE40TO44)("Male 45-49", MALE45TO49)("Male 50-54", MALE50TO54)("Male 55-59", MALE55TO59)("Male 60-64", MALE60TO64)("Male 65-69", MALE65TO69)
("Male 70-74", MALE70TO74)("Male 75-79", MALE75TO79)("Male 80-84", MALE80TO84)("Male 85", MALE85)("Female 0-4", FEMALE0TO4)("Female 5-9", FEMALE5TO9)
("Female 10-14", FEMALE10TO14)("Female 15-19", FEMALE15TO19)("Female 20-24", FEMALE20TO24)("Female 25-29", FEMALE25TO29)("Female 30-34", FEMALE30TO34)
("Female 35-39", FEMALE35TO39)("Female 40-44", FEMALE40TO44)("Female 45-49", FEMALE45TO49)("Female 50-54", FEMALE50TO54)("Female 55-59", FEMALE55TO59)
("Female 60-64", FEMALE60TO64)("Female 65-69", FEMALE65TO69)("Female 70-74", FEMALE70TO74)("Female 75-79", FEMALE75TO79)("Female 80-84", FEMALE80TO84)
("Female 85", FEMALE85);

static std::map<AgentInfo, std::string> AgentInfoMapReverse = boost::assign::map_list_of(MALE0TO4, "Male 0-4")(MALE5TO9, "Male 5-9")(MALE10TO14, "Male 10-14")
(MALE15TO19, "Male 15-19")(MALE20TO24, "Male 20-24")(MALE25TO29, "Male 25-29")(MALE30TO34, "Male 30-34")(MALE35TO39, "Male 35-39")(MALE40TO44, "Male 40-44")
(MALE45TO49, "Male 45-49")(MALE50TO54, "Male 50-54")(MALE55TO59, "Male 55-59")(MALE60TO64, "Male 60-64")(MALE65TO69, "Male 65-69")(MALE70TO74, "Male 70-74")
(MALE75TO79, "Male 75-79")(MALE80TO84, "Male 80-84")(MALE85, "Male 85")(FEMALE0TO4, "Female 0-4")(FEMALE5TO9, "Female 5-9")(FEMALE10TO14, "Female 10-14")
(FEMALE15TO19, "Female 15-19")(FEMALE20TO24, "Female 20-24")(FEMALE25TO29, "Female 25-29")(FEMALE30TO34, "Female 30-34")(FEMALE35TO39, "Female 35-39")
(FEMALE40TO44, "Female 40-44")(FEMALE45TO49, "Female 45-49")(FEMALE50TO54, "Female 50-54")(FEMALE55TO59, "Female 55-59")(FEMALE60TO64, "Female 60-64")
(FEMALE65TO69, "Female 65-69")(FEMALE70TO74, "Female 70-74")(FEMALE75TO79, "Female 75-79")(FEMALE80TO84, "Female 80-84")(FEMALE85, "Female 85");

enum SIRSeverity { SUSCEPTIBLE, INCUBATION, INFECTED, ICU, RECOVERED, DECEASED };

//Declare SIR class
class SIR {
    public:

    AgentInfo info;

    /**
     * SIR
     * 
     * This is the constructor for the agent class it sets the current severity to susceptible
     * 
     */
    SIR();

    /**
     * incubateAgent
     * 
     * used to push agent into the incubation stage
     */
    void incubateAgent();

    /**
     * infectAgent
     * 
     * used to push agent into symptoms stage
     */
    void infectAgent();

    /**
     * recoverAgent
     * 
     * used to push agent into recoverd stage
     */
    void recoverAgent();

    /**
     * ICUAgent
     * 
     * used to push agent into the ICU
     */
    void ICUAgent();

    /**
     * killAgent
     * 
     * used to push agent into death stage
     */
    void killAgent();

    int timeInfected;

    /**
     * getSeverity
     * 
     * Function returns the current severity stage of the SIR case. 
     * 
     * @return The current stage of the SIR case (Infected, recoverd, etc)
     */
    SIRSeverity getSeverity();

    private:

    SIRSeverity currentSeverity;

};


#endif