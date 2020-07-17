/****************
 * COVID-19ABMGuelphS20
 * 17/07/20
 * ver 0.08
 * 
 * This is the header file for the location class
 ***************/


#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <boost/assign/list_of.hpp>
#include <algorithm>
#include "SIRtotals.hh"
#include "transportation.hh"
#include "geographicalrisk.hh"

using namespace std;

static std::map<std::string, condenseLocationType> locationTypeMap = boost::assign::map_list_of("accounting", SERVICES)("airport", TRANSPORT)("amusement_park", PARKSANDREC)
("aquarium", ENTERTAINMENT)("art_gallery", ENTERTAINMENT)("atm", UNNEEDED)("bakery", GENSTORE)("bank", SERVICES)("bar", ENTERTAINMENT)("beauty_salon", SERVICES)("bicycle_store", GENSTORE)
("book_store", GENSTORE)("bowling_alley", ENTERTAINMENT)("bus_station", TRANSPORT)("cafe", ENTERTAINMENT)("campground", PARKSANDREC)("car_dealer", SERVICES)
("car_rental", SERVICES)("car_repair", SERVICES)("car_wash", SERVICES)("casino", ENTERTAINMENT)("cemetery", PARKSANDREC)("church", PLACEOFWORSHIP)("city_hall", SERVICES)
("clothing_store", GENSTORE)("convenience_store", GENSTORE)("courthouse", SERVICES)("dentist", HEALTH)("department_store", GENSTORE)("doctor", HEALTH)("drugstore", GENSTORE)
("electrician", SERVICES)("electronics_store", GENSTORE)("embassy", SERVICES)("fire_station", SERVICES)("florist", SERVICES)("funeral_home", PLACEOFWORSHIP)
("furniture_store", GENSTORE)("gas_station", GENSTORE)("gym", ENTERTAINMENT)("hair_care", SERVICES)("hardware_store", GENSTORE)("hindu_temple", PLACEOFWORSHIP)
("home_goods_store", GENSTORE)("hospital", HEALTH)("insurance_agency", SERVICES)("jewelry_store", GENSTORE)("laundry", SERVICES)("lawyer", SERVICES)
("library", ENTERTAINMENT)("light_rail_station", TRANSPORT)("liquor_store", GENSTORE)("local_government_office", SERVICES)("locksmith", SERVICES)
("lodging", PARKSANDREC)("meal_delivery", GENSTORE)("meal_takeaway", GENSTORE)("mosque", PLACEOFWORSHIP)("movie_rental", SERVICES)("movie_theater", ENTERTAINMENT)
("moving_company", SERVICES)("museum", ENTERTAINMENT)("night_club", ENTERTAINMENT)("painter", SERVICES)("park", PARKSANDREC)("parking", TRANSPORT)("pet_store", GENSTORE)
("pharmacy", HEALTH)("physiotherapist", HEALTH)("plumber", SERVICES)("police", SERVICES)("post_office", SERVICES)("primary_school", SCHOOL)
("real_estate_agency", SERVICES)("restaurant", ENTERTAINMENT)("roofing_contractor", SERVICES)("rv_park", PARKSANDREC)("school", SCHOOL)
("secondary_school", SCHOOL)("shoe_store", GENSTORE)("shopping_mall", ENTERTAINMENT)("spa", HEALTH)("stadium", ENTERTAINMENT)("storage", SERVICES)
("store", GENSTORE)("subway_station", TRANSPORT)("supermarket", GENSTORE)("synagogue", PLACEOFWORSHIP)("taxi_stand", TRANSPORT)("tourist_attraction", ENTERTAINMENT)
("train_station", TRANSPORT)("transit_station", TRANSPORT)("travel_agency", SERVICES)("university", SCHOOL)("veterinary_care", SERVICES)("zoo", ENTERTAINMENT)
("residential", RESIDENTIAL);


//Forward declarations
class Agent;

//Declare simulation class
class Location {
    public:
    /**
     * Location
     * 
     * This is the defual constructor for the location obect
     */
    Location();

    /**
     * Location
     * 
     * This is the constructor for the location object that takes in data
     * 
     * @param postalCode, a string of the postalCode
     * @param shopData, an array of size 9 of ints that holds each type of shop based on the enum condenseLocationType
     */
    Location(string postalCode, int shopData[LOCATIONTYPESIZE]);

    /**
     * getPopulation
     * 
     * This function gets the population of the location
     * 
     * @return the amount of agents in a given location
     */
    int getPopulation();

    /**
     * getSusceptible
     * 
     * This function gets the array of susceptible agents in the location
     * 
     * @return the array of Suseptible agents in the location
     */
    std::vector<Agent *> getSusceptible();

    /**
     * getInfected
     * 
     * This function gets the array of Infected agents in the location
     * 
     * @return the array of Infected agents in the location
     */
    std::vector<Agent *> getInfected();

    /**
     * setPostalCodeGrouping
     * 
     * This function sets a locations grouping string. For now this
     * can be changed multiple times but in the future it should change to
     * only be able to change once
     * 
     * @param newPostalCodeGrouping, this is the first 5 chars of the postalcode ie N1G 7J
     */
    void setPostalCodeGrouping(string newPostalCodeGrouping);

    /**
     * getPostalCodeGrouping
     * 
     * This function gets the locations postal code grouping
     * 
     * @return a string of the postal code grouping
     */
    string getPostalCodeGrouping();

    /**
     * increaseLocationCountAt
     * 
     * This function will take a index of the wanted location
     * index in the locationCount array and increment it by one
     * 
     * @param index, must be in range 0 <= index < LOCATIONTYPESIZE
     */
    void increaseLocationCountAt(int index);

    /**
     * increaseLocationCountAt
     * 
     * This function will take a index of the wanted location
     * index in the locationCount array and increment it by one
     * 
     * @param index, must be in range 0 <= index < LOCATIONTYPESIZE
     */
    void increaseLocationCountAt(condenseLocationType index);

    /**
     * addPostalCodeToList
     * 
     * This function adds a full postal code to the location groupings
     * list of postalCodes. It will not add dup postalCodes
     * 
     * @param postalCode, the postal code to add to the list
     */
    void addPostalCodeToList(string postalCode);

    /**
     * getPostalCodeListLength
     * 
     * This gets the length of the vector of the postal codes
     * int a postal code grouping
     * 
     * @return a int of the size of the vector of postalCodes
     */
    int getPostalCodeListLength();

    /**
     * getPostalCodeAt
     * 
     * This gets the postal code in the vector at a specified location
     * 
     * @param index, must be in range of the list length
     * @return the string of the postal code at the index
     */
    string getPostalCodeAt(int index);

    /**
     * postalCodeListContainsDup
     * 
     * THis is a helper function that makes sure there
     * is no dups in the vector of postal codes before
     * adding it into the list
     * 
     * @param newPostalCode, the postal code to check if it has a dup
     * @return a bool true if it contains a dup false if it dosent
     */
    bool postalCodeListContainsDup(string newPostalCode);

    /**
     * addAgentToSusceptible
     * 
     * This takes in an agent pointer and adds it to the locations 
     * susceptible vector
     * 
     * @param toAdd, the agent pointer
     */
    void addAgentToSusceptible(Agent *toAdd);

    /**
     * addAgentToInfected
     * 
     * This takes in an agent pointer and adds it to the locations
     * infected vector
     * 
     * @param toAdd, the agent pointer
     */
    void addAgentToInfected(Agent *toAdd);

    /**
     * removeSusceptibleAgent
     * 
     * This takes in an index and removes an agent at the the wanted 
     * index from the susceptible vector and returns its pointer
     * 
     * @param index, the index to remove from
     * @return the pointer to the removed agent
     */
    Agent *removeSusceptibleAgent(int index);

    /**
     * removeInfectedAgent
     * 
     * This takes in an index and removes an agent at the wanted
     * index from the infected vector and returns its pointer
     * 
     * @param index, the index to remove from
     * @return the pointer to the removed agent
     */
    Agent *removeInfectedAgent(int index);

    /**
     * getSusceptibleAgentAt
     * 
     * This takes in an index and returns the agent
     * at the wanted index from the sus vector
     * 
     * @param index, the index to get the agent from
     * @return a pointer to the agent
     */
    Agent *getSusceptibleAgentAt(int index);

    /**
     * getInfectedAgentAt
     * 
     * This takes in an index and returns the agent
     * at the wanted index from the infected vector
     * 
     * @param index, the index to get the agent from
     * @return a pointer to the agent
     */
    Agent *getInfectedAgentAt(int index);

    /**
     * getSusceptibleSize
     * 
     * This returns the size of the Susceptible vector
     * 
     * @return size of sus vector
     */
    int getSusceptibleSize();

    /**
     * getInfectedSize
     * 
     * This returns the size of the infected vector
     * 
     * @return size of infected vector
     */
    int getInfectedSize();


    private:
    int population;
    int pplDensity;
    int avgTimeSpent;
    int avgAgentInteraction;
    Transportation* transportaionRoutesFromLocation;
    SIRtotals sirTotalLocation;
    string postalCodeGrouping;
    std::vector<string> postalCodes;
    std::vector<Agent *> susceptible;
    std::vector<Agent *> infected;
};

#endif