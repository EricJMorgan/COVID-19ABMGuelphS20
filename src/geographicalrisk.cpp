/****************
 * COVID-19ABMGuelphS20
 * 30/06/20
 * ver 0.01
 * 
 * This is the class file for the geographical risk class
 ***************/


#include "geographicalrisk.hh"
#include <iostream>

// Constructor
GeographicalRisk::GeographicalRisk() {
    // x agent is infected AgentInfected()
}



void GeographicalRisk::updateAvgCountsAndRisk() {
    //idk if this will affect stuff
    //avgAgentAge = (double)sirTotalLocation.getMaskWearer() / (double)population;

    avgSymptomaticCarriers = 
    avgMaskWearer = (double)sirTotalLocation.getMaskWearer() / (double)population;
    avgHygiene = (double)sirTotalLocation.getMaskWearer() / (double)population;
    sexRatioMale = (double)sirTotalLocation.getMaleCount() / (double)population;



}
