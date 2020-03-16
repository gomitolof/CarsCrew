#ifndef XMLO_H
#define XMLO_H

#include <QString>

#include "container.h"
#include "deeptr.h"
#include "Gerarchia/car.h"

class XmlO {
private:
    string filename;
public:
    XmlO(const string&);
    void write(const Container<DeepPtr<Car>>&) const;
};

#endif // XMLO_H
