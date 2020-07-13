/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the class file for the SIR class
 ***************/


#include "SIR.hh"
#include <iostream>

// Constructor
SIR::SIR() {
    //
}

string SIR::DetermineSeverity() {
    switch(currentSeverity){
        case SUSCEPTIBLE : return "SUSCEPTIBLE";
        case INFECTED : return "INFECTED";
        default: return "NA";
    }
}