/****************
 * COVID-19ABMGuelphS20
 * 27/10/20
 * ver 2.00
 * 
 * This is the class file for the SIR class. This is the pipline that moves
 * agents from Susceptible to infected to recoverd. It looks at the agents current infection
 * status and moves them through at the appropriate times. It also decides when an agent dies.
 ***************/


#include "SIR.hh"
#include <iostream>

// Constructor
SIR::SIR() {
    currentSeverity = SUSCEPTIBLE;
}

void SIR::incubateAgent(){
    currentSeverity = INCUBATION;
}

void SIR::infectAgent(){
    currentSeverity = INFECTED;
}

void SIR::recoverAgent() {
    currentSeverity = RECOVERED;
} 

void SIR::killAgent() {
    currentSeverity = DECEASED;
}

void SIR::ICUAgent() {
    currentSeverity = ICU;
}

SIRSeverity SIR::getSeverity() {
    return currentSeverity;
}




