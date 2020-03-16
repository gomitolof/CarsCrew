#include "vintage.h"

Vintage::Vintage(string n, int c, int y):Car(n,c),year(y){}

string Vintage::environment() const{
    return getCV() > 80 && year > 1982 ? "circuito" : "città";
}

Vintage* Vintage::clone() const{
    return new Vintage(*this);
}

int Vintage::getProductionYear() const{
    return year;
}

void Vintage::setYear(const int& y){
    year=y;
}
