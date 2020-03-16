#include "sport.h"

Sport::Sport(string n, int c, double s, string dr):Car(n,c),speed(s),dri(dr=="Posteriore"? rearWheel : (dr=="Integrale" ?
                                                                                               fourWheel : frontWheel)){}

string Sport::environment() const{
    return speed > 250 && getCV() > 80 && dri!=frontWheel ? "circuito" : "città";
}

Sport* Sport::clone() const{
    return new Sport(*this);
}

string Sport::getDrive() const{
    string str;
    if(dri==fourWheel)
        str="Integrale";
    if(dri==rearWheel)
        str="Posteriore";
    if(dri==frontWheel)
        str="Anteriore";
    return str;
}

double Sport::getSpeed() const{
    return speed;
}

void Sport::setSpeed(const double& s){
    speed=s;
}

void Sport::setDrive(const string& d){
    if(d=="Integrale")
        dri=fourWheel;
    else if(d=="Posteriore")
        dri=rearWheel;
    else if(d=="Anteriore")
        dri=frontWheel;
}
