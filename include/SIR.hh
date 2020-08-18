/****************
 * COVID-19ABMGuelphS20
 * 13/08/20
 * ver 1.01
 * 
 * This is the header file for the SIR class
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

enum SIRSeverity { SUSCEPTIBLE, INFECTED, ISOLATED, HOSPITALIZED, ICU, RECOVERED, DECEASED };

//Declare SIR class
class SIR {
    public:

    /**
     * SIR
     * 
     * This is the constructor for the agent class it sets the current severity to susceptible
     * 
     */
    SIR();

    /**
     * AgentInfected
     * 
     * This infects an Agent with the COVID19 virus. The function decides the severity of the case and whether
     * the case will be fatal or not. 
     * 
     */
    void AgentInfected();

    /**
     * SIRTimeStep
     * 
     * This progresses agents through their various SIR model paths. An agent can be in any of the severity stages.
     * As time progresses the function decides what happens to the agent with COVID-19 next until the
     * agent has either recovered or passed away from the virus.
     * 
     * @param info the timestep of the overall simulation in hours
     * @return string indicate if any update took place
     */
    string SIRTimeStep(double timeStep);

    /**
     * DetermineSeverity
     * 
     * Function returns the current severity stage of the SIR case. 
     * 
     */
    SIRSeverity DetermineSeverity();

    /**
     * setQuarantineCases
     * 
     * Set chance of agent being quaratined
     * 
     * @param value to set chance of quarantine
     */
    void setQuarantineCases(double val);

    AgentInfo info;

    /**
     * getSymptoms
     * 
     * This returns if the agent is showing any symptoms
     * based on the SIR model
     * 
     * @return true if showing symptoms false if not
     */
    bool getSymptoms();

    private:
    // current state
    SIRSeverity currentSeverity;

    // various possible stages
    bool fatalCase;
    bool showsSymptoms;
    bool needHospital;
    bool needIcu;
    bool isIncubating;

    double quarantineCases;

    // time periods of various cases, user inputs
    double incubationPeriod; // time take to incubate virus
    double timeTilHospital; // time taken to get admitted to hospital after incubation, assuming hospital case
    double timeTilICU; // time taken to get admitted to icu after hospitilization, assuming icu case
    double timeTilDeath; // time taken to til death after icu, assuming fatal case
    double timeTilRecovery; // time taken to til recovery after recovery starts at any stage, assuming non-fatal case
                            // time til recovery will differ depending on which path to recovery is decided


    /**
     * QuarantineAgent
     * 
     * Move the agent's current SIR severity to isolated
     * 
     */
    void QuarantineAgent();

    /**
     * HospitalAgent
     * 
     * Move the agent's current SIR severity to hospitalized and indicate they are no longer waiting for hospital
     * 
     */
    void HospitalAgent();

    /**
     * PlaceAgentInICU
     * 
     * Move the agent's current SIR severity to ICU and indicate they are no longer waiting for ICU
     * 
     */
    void PlaceAgentInICU();

    /**
     * RecoverAgent
     * 
     * Move the agent's current SIR severity to recovered
     * 
     */
    void RecoverAgent();

    /**
     * AgentDeceased
     * 
     * Move the agent's current SIR severity to deceased
     * 
     */
    void AgentDeceased();

    /**
     * DecideSIRCase
     * 
     * This function takes in parameters to decide whether the infected agent's COVID19 condition will
     * be fatal. If the case is fatal the agent will progress down the SIR pipeline from infected to
     * hospital to ICU and then to deceased. If the agent's case is not fatal a path of recovery will be 
     * assigned to the agent based on the probabilities of being symptomatic admitted to hospital and
     * admitted to ICU.
     * 
     * @param infectedNumb the agent's odds of having the virus
     * @param infectedChance the chance of being infected based on Worldometer death rates
     */
    void DecideSIRCase(double infectedNumb, double infectedChance);
};


#endif