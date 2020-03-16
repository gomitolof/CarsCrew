#include "model.h"
#include "Gerarchia/sport.h"
#include "Gerarchia/offroad.h"
#include "Gerarchia/vintage.h"
#include "Gerarchia/rally.h"
#include "xmli.h"
#include "xmlo.h"
#include "Controller/anomalia.h"

void Model::add(Car* c){
    Car* pc=const_cast<Car*>(c);
    DeepPtr<Car> d(pc);
    vehicles.push_back(d);
}

int Model::correctPosition(unsigned int pos, const vector<int>& results){
    return results[pos];
}

void Model::remove(const int& n) throw(Anomalia){
    auto ci=vehicles.begin();
    int i=0;
    for(; ci!=vehicles.end() && i<n; ++ci){
        ++i;
    }
    try{
        vehicles.erase(ci);
    }
    catch(Anomalia){
        throw;
    }
}

void Model::clear() throw(Anomalia){
    try{
        vehicles.clear();
    }
    catch(Anomalia){
        throw;
    }
}

void Model::changeSportCar(const int& n, const string& nome,const int& cav, const double& sp, const string& dr) throw(Anomalia){
    DeepPtr<Car> dpt=getDptCar(static_cast<const unsigned int>(n));
    Car* car=dpt.operator->();
    if(dynamic_cast<Sport*>(car)){
        Container<DeepPtr<Car>>::iterator it=vehicles.begin()+=n;
        try{
            it=vehicles.erase(it);
            Sport* sport=static_cast<Sport*>(car);
            sport->setName(nome);
            sport->setCV(cav);
            sport->setSpeed(sp);
            sport->setDrive(dr);
            dpt=DeepPtr<Car>(sport);
            vehicles.insert(it,dpt);
        }
        catch(Anomalia){
            throw;
        }
    }
}

void Model::changeOffRoadCar(const int& r, const string& n, const int& c, const double& h) throw(Anomalia){
    DeepPtr<Car> dpt=getDptCar(static_cast<const unsigned int>(r));
    Car* car=dpt.operator->();
    if(dynamic_cast<OffRoad*>(car)){
        Container<DeepPtr<Car>>::iterator it=vehicles.begin()+=r;
        try{
            it=vehicles.erase(it);
            OffRoad* off=static_cast<OffRoad*>(car);
            off->setName(n);
            off->setCV(c);
            off->setHeightFromTheGround(h);
            dpt=DeepPtr<Car>(off);
            vehicles.insert(it,dpt);
        }
        catch(Anomalia){
            throw;
        }
    }
}

void Model::changeVintageCar(const int& r, const string& n, const int& c, const int& y) throw(Anomalia){
    DeepPtr<Car> dpt=getDptCar(static_cast<const unsigned int>(r));
    Car* car=dpt.operator->();
    if(dynamic_cast<Vintage*>(car)){
        Container<DeepPtr<Car>>::iterator it=vehicles.begin()+=r;
        try{
            it=vehicles.erase(it);
            Vintage* v=static_cast<Vintage*>(car);
            v->setName(n);
            v->setCV(c);
            v->setYear(y);
            dpt=DeepPtr<Car>(v);
            vehicles.insert(it,dpt);
        }
        catch(Anomalia){
            throw;
        }
    }
}

void Model::changeRallyCar(const int& ri, const string& n, const int& c, const double& s, const string& d, const bool& m) throw(Anomalia){
    DeepPtr<Car> dpt=getDptCar(static_cast<const unsigned int>(ri));
    Car* car=dpt.operator->();
    if(dynamic_cast<Rally*>(car)){
        Container<DeepPtr<Car>>::iterator it=vehicles.begin()+=ri;
        try{
            it=vehicles.erase(it);
            Rally* r=static_cast<Rally*>(car);
            r->setName(n);
            r->setCV(c);
            r->setSpeed(s);
            r->setDrive(d);
            r->setManualGearbox(m);
            dpt=DeepPtr<Car>(r);
            vehicles.insert(it,dpt);
        }
        catch(Anomalia){
            throw;
        }
    }
}

DeepPtr<Car> Model::getDptCar(unsigned int n) const throw(Anomalia){
    try {
        return vehicles[n];
    } catch (Anomalia) {
        throw;
    }

}

int Model::count() const{
    int n=0;
    for(auto it=vehicles.begin(); it!=vehicles.end(); ++it){
        ++n;
    }
    return n;
}

void Model::saveAs(const string& path) const throw(Anomalia){
    // Metodo di salvataggio della lista nel file indicato
    XmlO xmlo(path);
    try{
        xmlo.write(vehicles);
    }
    catch(Anomalia){
        throw;
    }
}

void Model::loadFile(const string& file) throw(Anomalia){
    XmlI xmli(file);
    try {
        vehicles = xmli.read();
    } catch (Anomalia) {
        throw;
    }

}

vector<int> Model::searchCarType(string type) throw(Anomalia){
    vector<int> results;
    for(string::size_type i=0; i < type.size(); ++i){
        char c=type[i];
        type[i]=tolower(c);
    }
    int i=0;
    for(auto cit=vehicles.begin(); cit!=vehicles.end(); ++cit){
        if(type == "rally" && dynamic_cast<Rally*>(&(**cit)))
            results.push_back(i);
        else if(type == "sport" && dynamic_cast<Sport*>(&(**cit)))
            results.push_back(i);
        else if(type == "fuoristrada" && dynamic_cast<OffRoad*>(&(**cit)))
            results.push_back(i);
        else if(type == "vintage" && dynamic_cast<Vintage*>(&(**cit)))
            results.push_back(i);
        ++i;
    }
    if(results.empty())
        throw(Anomalia('v'));
    return results;
}

vector<int> Model::searchCarName(string value) throw(Anomalia){
    vector<int> results;
    for(string::size_type i=0; i < value.size(); ++i){
        char c=value[i];
        value[i]=tolower(c);
    }
    int i=0;
    for(auto cit=vehicles.begin(); cit!=vehicles.end(); ++cit){
        string data=(*cit)->getName();
        for(string::size_type i=0; i < data.size(); ++i){
            char c=data[i];
            data[i]=tolower(c);
        }
        if(data == value)
            results.push_back(i);
        ++i;
    }
    if(results.empty())
        throw(Anomalia('v'));
    return results;
}

vector<int> Model::searchCV(const int& value, bool min) throw(Anomalia){
    vector<int> results;
    int i=0;
    for(auto cit=vehicles.begin(); cit!=vehicles.end(); ++cit){
        if((*cit)->getCV() >= value && min==true)
            results.push_back(i);
        else if((*cit)->getCV() <= value && min==false)
            results.push_back(i);
        ++i;
    }
    if(results.empty())
        throw(Anomalia('v'));
    return results;
}

vector<int> Model::searchSpeed(const double& value, bool min) throw(Anomalia){
    vector<int> results;
    int i=0;
    for(auto cit=vehicles.begin(); cit!=vehicles.end(); ++cit){
        if(dynamic_cast<Sport*>(&(**cit))){
            Sport* sport=static_cast<Sport*>(&(**cit));
            if(sport->getSpeed() >= value && min==true)
                results.push_back(i);
            else if(sport->getSpeed() <= value && min==false )
                results.push_back(i);
        }
        ++i;
    }
    if(results.empty())
        throw(Anomalia('v'));
    return results;
}

vector<int> Model::searchYear(const int& y) throw(Anomalia){
    vector<int> results;
    int i=0;
    for(auto cit=vehicles.begin(); cit!=vehicles.end(); ++cit){
        if(dynamic_cast<Vintage*>(&(**cit))){
            Vintage* vin=static_cast<Vintage*>(&(**cit));
            if(vin->getProductionYear() == y)
                results.push_back(i);
        }
        ++i;
    }
    if(results.empty())
        throw(Anomalia('v'));
    return results;
}

vector<int> Model::searchEnvironment(string value){
    vector<int> results;
    for(string::size_type i=0; i < value.size(); ++i){
        char c=value[i];
        value[i]=tolower(c);
    }
    int i=0;
    for(auto it=vehicles.begin(); it!=vehicles.end(); ++it){
        if(value == (*it)->environment())
            results.push_back(i);
        ++i;
    }
    if(results.empty())
        throw(Anomalia('v'));
    return results;
}
