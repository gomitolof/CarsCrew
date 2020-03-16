#include "anomalia.h"

Anomalia::Anomalia(char x): err(x) {}

char Anomalia::getError() const{
    return err;
}
