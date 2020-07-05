/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the header file for the GUI output class
 ***************/


#ifndef TRANSPORTATION_H_
#define TRANSPORTATION_H_

#include <iostream>

using namespace std;

class Location;
//Declare simulation class
class GUIOutput {
    private:
    Location* GuelphMap;

    public:
    GUIOutput();
    void updateDisplay();
};


#endif
