#ifndef VINTAGE_H
#define VINTAGE_H
#include "car.h"

class Vintage:public Car
{
private:
    int year;
public:
    Vintage(string ="private", int =50, int =1980);
    virtual string environment() const override;
    virtual Vintage* clone() const override;
    int getProductionYear() const;
    void setYear(const int&);
};

#endif // VINTAGE_H
