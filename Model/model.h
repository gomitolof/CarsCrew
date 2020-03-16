#ifndef MODEL_H
#define MODEL_H
#include <vector>
#include "container.h"
#include "deeptr.h"
#include "Gerarchia/car.h"
#include "Controller/anomalia.h"
using std::vector;

class Model
{
private:
    Container<DeepPtr<Car>> vehicles;
public:
    Model() =default;
    ~Model() =default;
    DeepPtr<Car> getDptCar(unsigned int) const throw(Anomalia);
    int count() const;
    void add(Car*);
    int correctPosition(unsigned int, const vector<int>&);
    void remove(const int&) throw(Anomalia);
    void clear() throw(Anomalia);
    void saveAs(const string&) const throw(Anomalia);
    void loadFile(const string&) throw(Anomalia);
    void changeSportCar(const int&, const string& ="\0",const int& =0, const double& =0.0, const string& ="\0") throw(Anomalia);
    void changeOffRoadCar(const int&, const string& ="\0", const int& =0, const double& =0.0) throw(Anomalia);
    void changeVintageCar(const int&, const string& ="\0", const int& =0, const int& =0) throw(Anomalia);
    void changeRallyCar(const int&, const string& ="\0",const int& =0, const double& =0.0, const string& ="\0", const bool& =true) throw(Anomalia);
    vector<int> searchCarType(string) throw(Anomalia);
    vector<int> searchCarName(string) throw(Anomalia);
    vector<int> searchCV(const int&, bool =true) throw(Anomalia);
    vector<int> searchSpeed(const double&, bool =true) throw(Anomalia);
    vector<int> searchYear(const int&) throw(Anomalia);
    vector<int> searchEnvironment(string);
};

#endif // MODEL_H
