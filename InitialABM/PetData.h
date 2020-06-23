#ifndef PETDATA_H_
#define PETDATA_H_

#include <string>
#include <iostream>

using namespace std;

//Declare pets class
class Pets{
    private:
    string name;
    int age;

    public:
    void printData();
    void setAge(int age);
    void setName(string name);
    int getAge();
    string getName();
};

//Declare Dog class with parent Pets
class Dog : private Pets{
    private:
    string breed;

    public:
    Dog(string name, string breed, int age);
    void setBreed(string breed);
    void printDogData();
};

#endif