/****************
 * COVID-19ABMGuelphS20
 * 06/07/20
 * ver 0.01
 * 
 * This is the header file for the postalCode classes
 ***************/

#ifndef POSTALCODE_H_
#define POSTALCODE_H_

#include <string>
#include <map>
#include <boost/assign/list_of.hpp>

using namespace std;

//An enum representing every possible location that the google places API allows us to use
enum locationType {accounting, airport, amusement_park, aquarium, art_gallery, atm, bakery, bank, bar, beauty_salon,
            bicycle_store, book_store, bowling_alley, bus_station, cafe, campground, car_dealer, car_rental, car_repair,
            car_wash, casino, cemetery, church, city_hall, clothing_store, convenience_store, courthouse, dentist, department_store,
            doctor, drugstore, electrician, electronics_store, embassy, fire_station, florist, funeral_home, furniture_store, gas_station,
            gym, hair_care, hardware_store, hindu_temple, home_goods_store, hospital, insurance_agency, jewelry_store, laundry, lawyer,
            library, light_rail_station, liquor_store, local_government_office, locksmith, lodging, meal_delivery, meal_takeaway, mosque,
            movie_rental, movie_theater, moving_company, museum, night_club, painter, park, parking, pet_store, pharmacy, physiotherapist,
            plumber, police, post_office, primary_school, real_estate_agency, restaurant, roofing_contractor, rv_park, school, secondary_school,
            shoe_store, shopping_mall, spa, stadium, storage, store, subway_station, supermarket, synagogue, taxi_stand, tourist_attraction,
            train_station, transit_station, travel_agency, university, veterinary_care, zoo};

//A map allowing the convertion of the location string into an enum to place it in the array
static std::map<std::string, locationType> locationTypeMap = boost::assign::map_list_of("accounting", accounting)("airport", airport)("amusement_park", amusement_park)
("aquarium", aquarium)("art_gallery", art_gallery)("atm", atm)("bakery", bakery)("bank", bank)("bar", bar)("beauty_salon", beauty_salon)("bicycle_store", bicycle_store)
("book_store", book_store)("bowling_alley", bowling_alley)("bus_station", bus_station)("cafe", cafe)("campground", campground)("car_dealer", car_dealer)
("car_rental", car_rental)("car_repair", car_repair)("car_wash", car_wash)("casino", casino)("cemetery", cemetery)("church", church)("city_hall", city_hall)("clothing_store", clothing_store)
("convenience_store", convenience_store)("courthouse", courthouse)("dentist", dentist)("department_store", department_store)("doctor", doctor)("drugstore", drugstore)
("electrician", electrician)("electronics_store", electronics_store)("embassy", embassy)("fire_station", fire_station)("florist", florist)("funeral_home", funeral_home)
("furniture_store", furniture_store)("gas_station", gas_station)("gym", gym)("hair_care", hair_care)("hardware_store", hardware_store)("hindu_temple", hindu_temple)
("home_goods_store", home_goods_store)("hospital", hospital)("insurance_agency", insurance_agency)("jewelry_store", jewelry_store)("laundry", laundry)("lawyer", lawyer)
("library", library)("light_rail_station", light_rail_station)("liquor_store", liquor_store)("local_government_office", local_government_office)("locksmith", locksmith)
("lodging", lodging)("meal_delivery", meal_delivery)("meal_takeaway", meal_takeaway)("mosque", mosque)("movie_rental", movie_rental)("movie_theater", movie_theater)
("moving_company", moving_company)("museum", museum)("night_club", night_club)("painter", painter)("park", park)("parking", parking)("pet_store", pet_store)
("pharmacy", pharmacy)("physiotherapist", physiotherapist)("plumber", plumber)("police", police)("post_office", post_office)("primary_school", primary_school)
("real_estate_agency", real_estate_agency)("restaurant", restaurant)("roofing_contractor", roofing_contractor)("rv_park", rv_park)("school", school)
("secondary_school", secondary_school)("shoe_store", shoe_store)("shopping_mall", shopping_mall)("spa", spa)("stadium", stadium)("storage", storage)
("store", store)("subway_station", subway_station)("supermarket", supermarket)("synagogue", synagogue)("taxi_stand", taxi_stand)("tourist_attraction", tourist_attraction)
("train_station", train_station)("transit_station", transit_station)("travel_agency", travel_agency)("university", university)("veterinary_care", veterinary_care)
("zoo", zoo);

class PostalCodeData{
    public:
    string postalCode;
    int locationCount[96];//each index is counted using the enum i.e the amount of accounting locations in the postal code would be at [0]
    PostalCodeData();
    PostalCodeData(string newPostalCode);
};

class PostalCodeHash{
    private:
    string getPostalCode(string fullAddress);

    public:
    PostalCodeHash(string tsvFile, int hashSize);
    PostalCodeData *hashTable;
    static int getPostalHash(int hashSize, string postalTSVToHash);
    
};
//hello
#endif
