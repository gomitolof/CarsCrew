#ifndef SPORT_H
#define SPORT_H
#include "car.h"

enum drive{ //trazione
    fourWheel, //trazione integrale
    rearWheel, //trazione posterire
    frontWheel, //trazione anteriore
};

class Sport:public Car
{
private:
    double speed;
    drive dri;
public:
    Sport(string ="private", int =50, double =180.0, string ="Posteriore");
    virtual string environment() const override;
    virtual Sport* clone() const override;
    string getDrive() const;
    double getSpeed() const;
    void setSpeed(const double&);
    void setDrive(const string&);
};

#endif // SPORT_H
