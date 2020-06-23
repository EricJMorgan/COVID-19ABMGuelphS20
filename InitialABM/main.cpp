#include "PetData.h"

/********Pet data*****************/
void Pets::printData(){
    cout<< name << " " << age << " ";
}

void Pets::setAge(int newAge){
    age = newAge;
}

void Pets::setName(string newName){
    name = newName;
}

int Pets::getAge(){
    return age;
}

string Pets::getName(){
    return name;
}


/************Dog data*************/
Dog::Dog(string newName, string newBreed, int newAge){
    setAge(newAge);
    setName(newName);
    setBreed(newBreed);
}

void Dog::setBreed(string newBreed){
    breed = newBreed;
}

void Dog::printDogData(){
    printData();
    cout << breed << "\n";
}