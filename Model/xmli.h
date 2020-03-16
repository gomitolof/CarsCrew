#ifndef XMLI_H
#define XMLI_H

#include <QString>

#include "container.h"
#include "deeptr.h"
#include "Gerarchia/car.h"

class XmlI {
private:
    string filename;
public:
    XmlI(const string&);
    Container<DeepPtr<Car>> read() const;
};

#endif // XMLI_H
