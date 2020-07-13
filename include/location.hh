/****************
 * COVID-19ABMGuelphS20
 * 09/07/20
 * ver 0.03
 * 
 * This is the header file for the location class
 ***************/


#ifndef LOCATION_H_
#define LOCATION_H_

#include <string>
#include <iostream>
#include <map>
#include <boost/assign/list_of.hpp>
#include "SIRtotals.hh"
#include "transportation.hh"
#include "geographicalrisk.hh"

using namespace std;
enum condenseLocationType {GENSTORE, TRANSPORT, SCHOOL, PARKSANDREC, SERVICES, ENTERTAINMENT, HEALTH, PLACEOFWORSHIP, UNNEEDED};

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
("train_station", TRANSPORT)("transit_station", TRANSPORT)("travel_agency", SERVICES)("university", SCHOOL)("veterinary_care", SERVICES)
("zoo", ENTERTAINMENT);


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
    Location(string postalCode, int shopData[9]);

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
    Agent* getSusceptible();

    /**
     * getInfected
     * 
     * This function gets the array of Infected agents in the location
     * 
     * @return the array of Infected agents in the location
     */
    Agent* getInfected();

    /**
     * getRecovered
     * 
     * This function gets the array of Recoverd agents in the location
     * 
     * @return the array of Recovered agents in the location
     */
    Agent* getRecovered();
    
    string postalCode;
    int locationCount[9];

    private:
    int population;
    int pplDensity;
    int avgTimeSpent;
    int avgAgentInteraction;
    Agent* currentAgents;
    Transportation* transportaionRoutesFromLocation;
    GeographicalRisk avgLocationRisk;
    SIRtotals sirTotalLocation;
};

#endif