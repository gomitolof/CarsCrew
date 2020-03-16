#ifndef RALLY_H
#define RALLY_H

#include "sport.h"

class Rally: public Sport
{
private:
    bool manual_gearbox; //cambio manuale
public:
    Rally(string ="private", int =50, double =180.0, string ="Posteriore", bool =true);
    virtual string environment() const override;
    virtual Rally* clone() const override;
    bool isManualGearbox() const;
    void setManualGearbox(const bool&);
};

#endif // RALLY_H
