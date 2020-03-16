#ifndef CAR_H
#define CAR_H
#include <iostream>
using std::string;

class Car
{
private:
    string name;
    int CV;
public:
    Car(string ="private", int =50);
    virtual Car* clone() const=0;
    virtual ~Car() =default;
    virtual string environment() const =0;
    bool operator==(const Car&) const;
    int getCV() const;
    string getName() const;
    void setCV(const int&);
    void setName(const string&);
};

#endif // CAR_H
