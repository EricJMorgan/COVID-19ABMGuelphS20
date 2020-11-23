/****************
 * COVID-19ABMGuelphS20
 * 12/11/20
 * ver 2.02
 * 
 * This is the header file for the simulation class. This is where all of the classes come together
 * to run the actual simulation. This is in charge of setting up all the objects, and running each timestep
 * for the simulation, along with giving the results as outputs to both the frontend and the console.
 ***************/

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include <string>
#include <iostream>
#include <vector>
#include "SIRtotals.hh"
#include "transportation.hh"
#include "agent.hh"
#include "location.hh"
#include "hospital.hh"
#include "isolationcompartment.hh"

using namespace std;

//Declare simulation class
class Simulation
{
public:
    /**
     * Simulation
     * 
     * This is the constructor for the simulation class it takes
     * in a file name of the csv file of the demographic data and creates
     * all the needed data to start the simulation
     * 
     * @param fileName the file name of the census data
     */
    Simulation(string fileName);

    /**
     * ~Simulation
     * 
     * This is the deconstructor for the simlation class
     */
    ~Simulation(); //Destructor

    /**
     * simulateTimeStep
     * 
     * when called this will simulate one time step in the simulation
     * it will do everything for agent movement infection spread and time
     * and date.
     */
    void simulateTimeStep();

    /**
     * getAgentAt
     * 
     * This function gets a specific agent from the internal data for 
     * what ever reason. It returns a copy of the agent instead of the original pointer
     * 
     * @param index the index in the internal array must be in range of 0 <= index < population
     */
    Agent *getAgentAt(int index);

    /**
     * getPopulation
     * 
     * This gets the population of the simulation based on
     * the amount of agents in the simulation
     * 
     * @return the amount of agents in the internal array
     */
    int getPopulation();

    /**
     * runSim
     * 
     * This function is called to indefinitly run the sim
     * currently it is not used all too much as the front end calls
     * simulate time step over and over
     */
    void runSim();

    /**
     * getInfectedCurrent
     * 
     * This get the current number of infected agents
     */
    int getInfectedCurrent();

    /**
     * getInfectedTotal
     * 
     * This get the current number of infected agents
     */
    int getInfectedTotal();

    /**
     * getDeceasedTotal
     * 
     * This get the current number of deceased agents
     * 
     * @return number of total deceased agents
     */
    int getDeceasedTotal();

    /**
     * getRecoveredTotal
     * 
     * This get the current number of recovered agents
     * 
     * @return number of total recovered agents
     */
    int getRecoveredTotal();

    /**
     * getHospitalTotal
     * 
     * This get the current number of total agents ever hospitilized
     * 
     * @return number of total hospitalized agents
     */
    int getHospitalTotal();

    /**
     * getHospitalCurrent
     * 
     * This get the current number of current hospital agents
     * 
     * @return number of current hospitalized agents
     */
    int getHospitalCurrent();

    /**
     * getICUtotal
     * 
     * This get the current number of total ICU agents
     * 
     * @return number of total ICU agents
     */
    int getICUtotal();

    /**
     * getICUCurrent
     * 
     * This get the current number of current ICU agents
     * 
     * @return number of current ICU agents
     */
    int getICUCurrent();

    /**
     * getNewlyInfected
     * 
     * This get the newly infected agents during timestep
     * 
     * @return number of newly infected agents
     */
    int getNewlyInfected();

    /**
     * setInputs
     * 
     * Takes inputs from front end sends them to the associated classes
     */
    // void setInputs();

    //user input setters
    /**
     * setSocialDistancingSeverity
     * 
     * setter for SocialDistancingSeverity
     * @param val the value to set
     */
    void setSocialDistancingSeverity(int val);

    /**
     * setMaskCompliance
     * 
     * setter for MaskCompliance
     * @param val the value to set
     */
    void setMaskCompliance(double val);

    /**
     * setHygieneMaintainence
     * 
     * setter for HygieneMaintainence
     * @param val the value to set
     */
    void setHygieneMaintainence(double val);

    /**
     * setAgentMitagationChance
     * 
     * This is responsible for setting each age groups chance of
     * following each mitigation strategy. ageGroup 0 = 0 to 4, ageGroup 1 = 5 to 9 etc
     * strategy is 0 = social distancing, 1 = maskwearing, 2 = hygine, 3 = isolation, 4 = vaccine
     * 
     * @param the age group the set of agents are in range 0 - 17
     * @param the mitigation strategy used in range 0 - 3
     */
    void setAgentMitagationChance(int ageGroup, int strategy, double value);

    /**
     * getAgentMitagationChance
     * 
     * This gets the ageGroups mitagation chance for the wanted
     * strategy. where ageGroup: 0 = 0 - 4, 1 = 5 - 9 etc and 
     * strategy: 0 = social distancing, 1 = maskwearing, 2 = hygiene, 3 = isolation, 4 = vaccine
     * 
     * @param ageGroup is the age group in range 0 - 17.
     * @param strategy is the wanted strategy in range 0 - 3.
     */
    double getAgentMitagationChance(int ageGroup, int strategy);

    /**
     * setMitagationEffectivness
     * 
     * This sets each mitigation strategys effectivness with a value 
     * between 0 and 1.0. 0 = social distancing, 1 = maskwearing, 2 = hygine, 3 = isolation
     * 
     * @param int strategy this is the strategy too be used in range 0 - 3
     * @param double value in range 0 - 1.0
     */
    void setMitagationEffectivness(int strategy, double value);

    /**
     * getMitagationEffectivness
     * 
     * This gets the mitagation strategys given effectivness
     * where 0 = social distancing, 1 = maskwearing, etc.
     * 
     * @param strategy is the wanted strategy in range 0 - 3.
     */
    double getMitagationEffectivness(int strategy);

    /**
     * setLocationRisk
     * 
     * This sets each locations risk with a value
     * between 0 and 1.0. 0 = genstore, 1 = transportation, etc
     * 
     * @param int location is the location to be checked in range 0 - 8
     * @param double value in range 0 - 1.0
     */
    void setLocationRisk(int location, double value);

    /**
     * getLocationRisk
     * 
     * This gets each locations given risk where
     * 0 = genreal store, 1 = transport, etc
     * 
     * @param the wanted location in range 0 - 8
     */
    double getLocationRisk(int location);

    /**
     * setAgentIncubationPeriod
     * 
     * This method will set each age groups incubation period with the virus
     * 
     * @param the ageGroup that you want to assign the value too 0 <= ageRange <= 17
     * @param the length of the incubation period 0 <= value <= 127
     */
    void setAgentIncubationPeriod(int ageRange, short value);

    /**
     * getAgentIncubationPeriod
     * 
     * This method gets the specific age groups incubation period
     * 
     * @param the ageGroup that you want to get the incubation period for
     * @return the length of the incubation period for the wanted ageGroup
     */
    short getAgentIncubationPeriod(int ageRange);

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
     * getAgentDeathChance
     * 
     * This will get the given ages chance of death where
     * ageRange is 0 = 0 - 4, 1 = 5 - 9, etc.
     * 
     * @param ageRange the age of the wanted death chance in range 0 - 17.
     * @return a double of the chance of death
     */
    double getAgentDeathChance(int ageRange);

    /**
     * setAgentChanceOfMovment
     * 
     * This is used to set the array of agentChanceOfMovment
     * 
     * @param int ageGroup in range 0-17 where 0 is 0-4 1 is 5-9 etc
     * @param int day in range 0-1 where 0 is a weekday and 1 is a weekend
     * @param int time in range 0 <= time * timeStep < 24
     * @param int location in range 0 - 9 where the number corisponds to the condenseLocationType enum
     * @param double the percent chance of someone moving to the given location in range 0 - 1.0
     */
    void setAgentChanceOfMovment(int ageGroup, int day, int time, int location, double value);

    /**
     * getAgentChanceOfMovment
     * 
     * This is used to get the agents chance of movement based on ageGroup, day of the week,
     * time of the day, and location.
     * 
     * @param int ageGroup in range 0-17 where 0 is 0-4 1 is 5-9 etc
     * @param int day in range 0-1 where 0 is a weekday and 1 is a weekend
     * @param int time in range 0 <= time * timeStep < 24
     * @param int location in range 0 - 9 where the number corisponds to the condenseLocationType enum
     * @return the percent chance of someone moving to the given location
     */
    double getAgentChanceOfMovment(int ageGroup, int day, int time, int location);

    /**
     * setAgentNeedsHospital
     * 
     * This is used to set each ageGroups chance of needing the hospital
     * after getting infected
     * 
     * @param int ageGroup in range 0-17
     * @param the chance of needing the hospial 0 <= chance <= 1
     */
    void setAgentNeedsHospital(int ageGroup, double chance);

    /**
     * getAgentNeedsHospital
     * 
     * This method gets the ageGroups chance of needing the hospital
     * 
     * @param int ageGroup in range 0-17
     * @return the chance of the ageGroup needs the hospital
     */
    double getAgentNeedsHospital(int ageGroup);

    /**
     * setLocationRisks
     * 
     * This method is used to set each locations inherite risk
     * location 0 = 
     * 
     * @param the type of location to edit 0 <= locaiton <= 8
     * @param the risk of the wanted location 0 <= value <= 1
     */
    void setLocationRisks(int location, double value);

    /**
     * getLocationRisks
     * 
     * This method takes a location type and returns its risk
     * 
     * @param the type of location 0 <= location <= 8
     * @return the risk of the wanted location
     */
    double getLocationRisks(int location);

    /**
     * setAgentChanceOfICU
     * 
     * This method sets each ageGroups chance of needing the ICU
     * 
     * @param the ageGroup wanted to set the chance of ICU for 0 <= ageGroup <= 17
     * @param the chance of an agent needing the ICU 0 <= value <= 1.0
     */
    void setAgentChanceOfICU(int ageGroup, double value);

    /**
     * getAgentChanceOfICU
     * 
     * This method gets the ageGroups chance of needing the ICU
     * 
     * @param the ageGroup wanted to get the chance of ICU where 0 <= ageGroup <= 17
     * @return the chance of the ageGroup needing the ICU
     */
    double getAgentChanceOfICU(int ageGroup);

    /**
     * setAgentIncubationTime
     * 
     * This method sets an ageGroups virus incubation time
     * 
     * @param the ageGroup wanted to set the incubation time where 0 <= ageGroup <= 17
     * @param the time it takes for the virus to incubate where 0 <= value <= 127
     */
    void setAgentIncubationTime(int ageGroup, short value);

    /**
     * getAgentIncubationTime
     * 
     * This method gets an ageGroups virus incubation time
     * 
     * @param the ageGroup which the incubation time is wanted where 0 <= ageGroup <= 17
     * @return a short of the time of the virus incubating
     */
    short getAgentIncubationTime(int ageGroup);

    /**
     * simDayTimeStep
     * 
     * This method simulates a full day of timesteps
     * instead of a singular 4 hour time step. This is so
     * the front end does not need to take on as much work for each timestep and
     * can update only once per simulation day
     */
    void simDayTimeStep();

    void setPresets(int preset);
    
    SIRtotals totalSimSIRStats;
    
    Transportation *locationInfo = NULL;

    std::vector<Agent *> recoveredAgents;
    std::vector<Agent *> deceasedAgents;

    private:
    Agent** simAgents;
    Hospital guelphHospital;
    IsolationCompartment isoCompartment;
    int timeStep;
    int currTime;
    DayOfWeek currDay;
    int timeQuarantined;
    int agentCount;
    int population;
    int newlyInfected;
    double sirTimeStep;
    

    // user inputs
    double agentMitagationChance[18][5];
    double mitagationEffectivness[5];
    double locationRisks[9];//done
    short agentRecoveryTime[18];//done
    short agentIncubationTime[18];//done
    double agentNeedsHospital[18];//done
    double agentDeathChance[18];//done
    double agentChanceOfICU[18];//done
    double agentChanceOfMovment[18][2][6][9];

    //outputs for Front End graph
    int infectedCurrent;
    int infectedTotal;
    int deceasedTotal;
    int recoveredTotal;
    int hospitalCurrent;
    int hospitalTotal;
    int icuCurrent;
    int icuTotal;
    int timeElapsed;

    double initiallyInfectedChance;
    int initiallyInfected;


    /**
     * addNewAgent
     * 
     * This function takes in the agents info and the amount of said
     * agent and adds that amount to the array of people
     * 
     * @param personInfo this is a string in the fomat GENDER N-N where N is the age range
     * @param amountToAdd this is a int of how many of that agent there are for the area i.e there are 3875 males 0-4 in guelph
     */
    void addNewAgent(string personInfo, int amountToAdd);

    /**
     * setUpAgents
     * 
     * This function takes in the file name of the demographic file
     * of an area in the format typeOfDataDataInfoAmountOfPeople
     * 
     * @param filename must be in the above format
     */
    void setUpAgents(string filename);

    /**
     * stepTime
     * 
     * This function is a helper function to push the time and day
     * forward on every iteration of the timesetp
     */
    void stepTime();

    /**
     * getNextDay
     * 
     * This is a helper function to increment the currDay counter
     * int the program
     * 
     * @param the current day of the week
     * @return the next day in line
     */
    DayOfWeek getNextDay(DayOfWeek currDay);

    /**
     * setAnarchyPreset
     * 
     * This is essintally the crank it up to 11
     * setting everything to the max chance, meaning everything
     * from each locations risk to death chances are at 100%
     */
    void setAnarchyPreset();

    /**
     * setRealWorldPreset
     * 
     * This is what the program will defualt too.
     * It is meant to represt our current world and what is going on
     */
    void setRealWorldPreset();

    /**
     * setTotalIsolation
     * 
     * This is an extreme preset in which pretty much no one leaves their house.
     * They stay in total isolation and never come into contact with another person
     * if they can avoid it
     */
    void setTotalIsolation();

    /**
     * setInformedPopulation
     * 
     * This is what we as a society should be aiming for.
     * The informed population while not perfect does its best.
     * They do things such as wearing masks, staying in when they can, etc
     */
    void setInformedPopulation();

    /**
     * setConspiracyPopulation
     * 
     * This is meant to represet the 5G is mind control,
     * the lizard people are in the sewers, illumanti, flat earth kind
     * of people that cant seem to grasp basic concepts. They think this is some
     * goverment way of taking away their freedoms. The kinda people to say STOP THE COUNT
     */
    void setConspiracyPopulation();

    /**
     * setRealWorldNoSchool
     * 
     * This uses the default settings but imagines if all school was
     * online instead of in person.
     */
    void setRealWorldNoSchool();

    /**
     * setRealWorldNoVaccine
     * 
     * This uses the default settings but imagines if there is no vaccine
     */
    void setRealWorldNoVaccine();

    /**
     * setDefaultLocationRisks
     * 
     * This is a helper function to set all location risks to default risks
     * to where it seems like they belong
     */
    void setDefaultLocationRisks();

    /**
     * setDefaultHospitalData
     * 
     * This is a helper function to set all the hospital varibles
     * to what the default should be
     */
    void setDefaultHospitalData();

    /**
     * setDefaultMitagationEffectivness
     * 
     * This is a helper function to set each mitagation strategys effectivness
     */
    void setDefaultMitagationEffectivness();

    void setDefaultMovementData();
};

//for python binding
extern "C"
{
    Simulation *Simulation_new() { return new Simulation("demographicGuelph.csv"); }
    void simTimeStep(Simulation *sim) { sim->simulateTimeStep(); }
    int newlyInfected(Simulation *sim) { return sim->getNewlyInfected(); }
    int infectedCurrent(Simulation *sim) { return sim->getInfectedCurrent(); }
    int infectedTotal(Simulation *sim) { return sim->getInfectedTotal(); }
    int deceasedTotal(Simulation *sim) { return sim->getDeceasedTotal(); }
    int recoveredTotal(Simulation *sim) { return sim->getRecoveredTotal(); }
    int hospitalTotal(Simulation *sim) { return sim->getHospitalTotal(); }
    int hospitalCurrent(Simulation *sim) { return sim->getHospitalCurrent(); }
    int ICUtotal(Simulation *sim) { return sim->getICUtotal(); }
    int ICUCurrent(Simulation *sim) { return sim->getICUCurrent(); }
    void setAgentMitagationChance(Simulation *sim, int ageGroup, int strategy, double value) { sim->setAgentMitagationChance(ageGroup, strategy, value); }
    double getAgentMitagationChance(Simulation *sim, int ageGroup, int strategy) { return sim->getAgentMitagationChance(ageGroup, strategy); }
    void setMitagationEffectivness(Simulation *sim, int strategy, double value) { sim->setMitagationEffectivness(strategy, value); }
    double getMitagationEffectivness(Simulation *sim, int strategy) { return sim->getMitagationEffectivness(strategy); }
    void setAgentRecoveryTime(Simulation *sim, int ageRange, short val) { sim->setAgentRecoveryTime(ageRange, val); }
    short getAgentRecoveryTime(Simulation *sim, int ageRange) { return sim->getAgentRecoveryTime(ageRange); }
    void setAgentDeathChance(Simulation *sim, int ageRange, double val) { sim->setAgentDeathChance(ageRange, val); }
    double getAgentDeathChance(Simulation *sim, int ageRange) { return sim->getAgentDeathChance(ageRange); }
    void setAgentChanceOfMovment(Simulation *sim, int ageGroup, int day, int time, int location, double value) { sim->setAgentChanceOfMovment(ageGroup, day, time, location, value); }
    double getAgentChanceOfMovment(Simulation *sim, int ageGroup, int day, int time, int location) { return sim->getAgentChanceOfMovment(ageGroup, day, time, location); }
    void setAgentNeedsHospital(Simulation *sim, int ageGroup, double chance) { sim->setAgentNeedsHospital(ageGroup, chance); }
    double getAgentNeedsHospital(Simulation *sim, int ageGroup) { return sim->getAgentNeedsHospital(ageGroup); }
    void setLocationRisks(Simulation *sim, int location, double value) { sim->setLocationRisks(location, value); }
    double getLocationRisks(Simulation *sim, int location) { return sim->getLocationRisks(location); }
    void setAgentChanceOfICU(Simulation *sim, int ageGroup, double value) { sim->setAgentChanceOfICU(ageGroup, value); }
    double getAgentChanceOfICU(Simulation *sim, int ageGroup) { return sim->getAgentChanceOfICU(ageGroup); }
    void setAgentIncubationTime(Simulation *sim, int ageGroup, short value) { sim->setAgentIncubationTime(ageGroup, value); }
    short getAgentIncubationTime(Simulation *sim, int ageGroup) { return sim->getAgentIncubationTime(ageGroup); }
    void simDayTimeStep(Simulation *sim) {sim->simDayTimeStep();}
}

#endif