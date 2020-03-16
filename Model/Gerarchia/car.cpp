#include "car.h"

Car::Car(string n, int c):name(n),CV(c){}

int Car::getCV() const{
    return CV;
}

string Car::getName() const{
    return name;
}

void Car::setCV(const int& c){
    CV=c;
}

void Car::setName(const string& n){
    name=n;
}

bool Car::operator==(const Car& c) const{
    return name==c.getName() && CV==c.getCV();
}
