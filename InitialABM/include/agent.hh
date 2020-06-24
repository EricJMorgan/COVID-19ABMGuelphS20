#ifndef AGENT_H_
#define AGENT_H_

#include <string>
#include <iostream>
#include "../include/location.hh"

using namespace std;

//Declare simulation class
class Agent{
    private:
    int age;
    string ethnicity;
    string gender;
    string maritalStatus;
    string maritalStatus;

    public:
    int getAge();
};

#endif