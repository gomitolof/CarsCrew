#include "rally.h"

Rally::Rally(string s, int ca, double sp, string d, bool ge):Sport(s,ca,sp,d), manual_gearbox(ge){}

Rally* Rally::clone() const{
    return new Rally(*this);
}

bool Rally::isManualGearbox() const{
    return manual_gearbox;
}

void Rally::setManualGearbox(const bool & c){
    manual_gearbox=c;
}

string Rally::environment() const{
    return manual_gearbox && (Sport::environment()=="circuito") ? "circuito" : "terreno irregolare";
}
