#!/usr/bin/env python3

import googlemaps
import pprint
import time
import csv
from googleAPIKey import getAPIKey

#must have google API key for this to run.
API_KEY = getAPIKey()
gmaps = googlemaps.Client(key = API_KEY)

#All possible search terms (May get dups)
typeList = ['accounting', 'airport', 'amusement_park', 'aquarium', 'art_gallery', 'atm', 'bakery', 'bank', 'bar', 'beauty_salon',
            'bicycle_store', 'book_store', 'bowling_alley', 'bus_station', 'cafe', 'campground', 'car_dealer', 'car_rental', 'car_repair',
            'car_wash', 'casino', 'cemetery', 'church', 'city_hall', 'clothing_store', 'convenience_store', 'courthouse', 'dentist', 'department_store',
            'doctor', 'drugstore', 'electrician', 'electronics_store', 'embassy', 'fire_station', 'florist', 'funeral_home', 'furniture_store', 'gas_station',
            'gym', 'hair_care', 'hardware_store', 'hindu_temple', 'home_goods_store', 'hospital', 'insurance_agency', 'jewelry_store', 'laundry', 'lawyer',
            'library', 'light_rail_station', 'liquor_store', 'local_government_office', 'locksmith', 'lodging', 'meal_delivery', 'meal_takeaway', 'mosque',
            'movie_rental', 'movie_theater', 'moving_company', 'museum', 'night_club', 'painter', 'park', 'parking', 'pet_store', 'pharmacy', 'physiotherapist',
            'plumber', 'police', 'post_office', 'primary_school', 'real_estate_agency', 'restaurant', 'roofing_contractor', 'rv_park', 'school', 'secondary_school',
            'shoe_store', 'shopping_mall', 'spa', 'stadium', 'storage', 'store', 'subway_station', 'supermarket', 'synagogue', 'taxi_stand', 'tourist_attraction',
            'train_station', 'transit_station', 'travel_agency', 'university', 'veterinary_care', 'zoo']

#open file
with open('placeData.tsv', 'w') as tsvfile:
    writer = csv.writer(tsvfile, delimiter='\t')

    #Loop through all search terms
    for j in range(0, len(typeList)):
        #get inital search quary
        placesNear = gmaps.places_nearby(location = '43.549999,-80.250000', radius = 20000, open_now = False, type = typeList[j])

        #loop through all data given from search(including other pages) using do while loop... sort of, python is weird
        while True:
            #loop through each place and get information
            for place in placesNear['results']:
                placeID = place['place_id']
                name = place['name']
                location = place['geometry']['location']

                searchFeilds = ['formatted_address','opening_hours']
                data = gmaps.place(place_id = placeID, fields = searchFeilds)

                #get info about open hours
                #This takes the first open day starting on monday 
                hours = ''
                if 'opening_hours' in data['result']:
                    hourInfo = data['result']['opening_hours']['periods']
                    for i in range(1,len(hourInfo)):
                        if 'open' not in hourInfo[i]:
                            continue
                        elif 'close' not in hourInfo[i]:#case for 24/7 places
                            hours = '0000 - 2359'
                            break
                        else:
                            hours = hourInfo[i]['open']['time'] + '-' + hourInfo[i]['close']['time']
                            break
                    
                    if hours == '':#edge case
                        hours = 'Unknown'
                else:
                    hours = 'Unknown'
                    
                #Write all data to file in tsv format
                writer.writerow([name, data['result']['formatted_address'], hours, str(location['lat']), str(location['lng']), typeList[j]])

                #print data to console  
                print(name + ',' + data['result']['formatted_address'] + ',' + hours + ',' + str(location['lat']) + ',' + str(location['lng']) + ',' + typeList[j])
            
            #pause before requesting more data to let google DB catch up
            time.sleep(3)
            #gets next token for search results if it exists
            if 'next_page_token' in placesNear:
                placesNear = gmaps.places_nearby(page_token = placesNear['next_page_token'])
            else:
                print('No More tokens')
                break;#exit for do While 
