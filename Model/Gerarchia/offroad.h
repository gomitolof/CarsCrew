#ifndef OFFROAD_H
#define OFFROAD_H
#include "car.h"

class OffRoad: public Car
{
private:
    double heightFTG; //Height From The Ground: altezza dal terreno
public:
    OffRoad(string ="private", int =50, double =12.0);
    virtual string environment() const override;
    virtual OffRoad* clone() const override;
    double getHeightFromTheGround() const;
    void setHeightFromTheGround(const double&);
};

#endif // OFFROAD_H
