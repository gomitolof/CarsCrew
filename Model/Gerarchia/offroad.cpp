#include "offroad.h"

OffRoad::OffRoad(string n, int c, double h):Car(n,c),heightFTG(h){}

string OffRoad::environment() const{
    return heightFTG < 25.0 ? "montagna" : (getCV() > 85 ? "deserto"  : "terreno irregolare");
}

OffRoad* OffRoad::clone() const{
    return new OffRoad(*this);
}

void OffRoad::setHeightFromTheGround(const double& h){
    heightFTG=h;
}

double OffRoad::getHeightFromTheGround() const{
    return heightFTG;
}
