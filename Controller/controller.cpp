#include <QListWidget>
#include "controller.h"
#include "View/carsview.h"
#include "Model/Gerarchia/car.h"
#include "Model/Gerarchia/sport.h"
#include "Model/Gerarchia/offroad.h"
#include "Model/Gerarchia/vintage.h"
#include "Model/Gerarchia/rally.h"
#include "View/cardetail.h"
#include "View/insertcar.h"
#include "View/researchingcars.h"

Controller::Controller(CarsView *v, QObject *parent)
        : QObject(parent), model(new Model()), view(v){}

Controller::~Controller() {
    if (model)
        delete model;
}

// SLOT che indica al modello di aggiungere un elemento alla lista
void Controller::addItem() const throw(Anomalia){
    string tipo = view->getForm()->getCarType().toStdString();
    try{
        string nome = view->getForm()->getCarName().toStdString();
        int cv = view->getForm()->getCV();
        if(tipo=="Sport"){
            double speed=view->getForm()->getSpeed();
            string drive=view->getForm()->getDrive().toStdString();
            Sport* s=new Sport(nome,cv,speed,drive);
            model->add(s);
        }
        else if(tipo=="Fuoristrada") {
            double h=view->getForm()->getHFG();
            OffRoad* o=new OffRoad(nome,cv,h);
            model->add(o);
        }
        else if(tipo=="Vintage"){
            int y=view->getForm()->getYear();
            Vintage* v=new Vintage(nome,cv,y);
            model->add(v);
        }
        else if(tipo=="Rally"){
            double speed=view->getForm()->getSpeed();
            string drive=view->getForm()->getDrive().toStdString();
            string gear=view->getForm()->getGearbox().toStdString();
            bool manual=true;
            if(gear=="Sequenziale")
                manual=false;
            Rally* r=new Rally(nome,cv,speed,drive,manual);
            model->add(r);
        }
        view->add();
    }
    catch(Anomalia e){
        checkFields(e);
    }
}

void Controller::removeAllResults() const throw(Anomalia){
    try {
        vector<int> v=research();
        for(unsigned long pos=v.size(); pos>0; --pos){
            int p=model->correctPosition(static_cast<unsigned int>(pos-1), v);
            model->remove(p);
            view->remove(p);
        }
    } catch (Anomalia) {
        view->errorMessage("Cancellazione annullata","Impossibile eliminare le auto selezionate");
    }

}

void Controller::removeAll() const throw(Anomalia){
    try {
        model->clear();
        view->removeAll();
    } catch (Anomalia) {
        view->errorMessage("Cancellazione annullata","Impossibile eliminare le auto selezionate");
    }
}

void Controller::removeItemResults() const throw(Anomalia){
    try {
        unsigned int pos=static_cast<unsigned int>(view->getResults()->itemRow());
        int p=model->correctPosition(pos, research());
        model->remove(p);
        view->remove(p);
    } catch (Anomalia){
        view->errorMessage("Cancellazione annullata","Impossibile eliminare le auto selezionate");
    }

}

void Controller::removeItem() const throw(Anomalia){
    try {
        int pos=view->itemRow();
        model->remove(pos);
        view->remove();
    }
    catch(Anomalia){
        view->errorMessage("Cancellazione annullata","Nessun elemento selezionato");
    }
}

void Controller::seeDetail(){
    try{
        int pos=0;
        if(view->getResults()->isVisible()){
            if(view->getResults()->itemRow()!=-1)
                pos=model->correctPosition(static_cast<unsigned int>(view->getResults()->itemRow()), research());
        }
        else{
            pos=view->itemRow();
        }
        if (pos!=-1){
            DeepPtr<Car> dpt=model->getDptCar(static_cast<unsigned int>(pos));
            Car* f=dpt.operator->();
            string na=f->getName();
            string env=f->environment();
            int cv=f->getCV();
            QString name=QString::fromStdString(na);
            if(dynamic_cast<Rally*>(f)){
                Rally* ral=static_cast<Rally*>(f);
                string dr=ral->getDrive();
                QString drive=QString::fromStdString(dr);
                double r=ral->getSpeed();
                bool seq=!(ral->isManualGearbox());
                view->openRallyCar(name, QString::fromStdString(env), cv, r, drive, seq);
            }
            else if(dynamic_cast<Sport*>(f)){
                Sport* s=static_cast<Sport*>(f);
                string dr=s->getDrive();
                string env=s->environment();
                QString drive=QString::fromStdString(dr);
                view->openSportCar(name,QString::fromStdString(env),cv,s->getSpeed(),drive);
            }
            else if(dynamic_cast<OffRoad*>(f)){
                OffRoad* off=static_cast<OffRoad*>(f);
                double o=off->getHeightFromTheGround();
                string env=off->environment();
                view->openOffRoadCar(name, QString::fromStdString(env), cv, o);
            }
            else if(dynamic_cast<Vintage*>(f)){
                Vintage* vin=static_cast<Vintage*>(f);
                string env=vin->environment();
                view->openVintageCar(name, QString::fromStdString(env), cv, vin->getProductionYear());
            }
        }
    }
    catch(Anomalia e){
        checkFields(e);
    }
}

void Controller::changeCar() const throw(Anomalia){
    try{
        int pos=view->itemRow();
        QString tipo=view->getCarDetail()->getCarType();
        QString no=view->getCarDetail()->getCarName();
        string nome=no.toStdString();
        int cv=view->getCarDetail()->getCV();
        if(tipo=="Sportiva"){
            double sp=view->getCarDetail()->getSpeed();
            QString d=view->getCarDetail()->getDrive();
            string dr=view->getCarDetail()->getDrive().toStdString();
            model->changeSportCar(pos,nome,cv,sp,dr);
        }
        else if(tipo=="Fuoristrada"){
            double h=view->getCarDetail()->getHFG();
            model->changeOffRoadCar(pos,nome,cv,h);
        }
        else if(tipo=="Vintage"){
            int y=view->getCarDetail()->getYear();
            model->changeVintageCar(pos,nome,cv,y);
        }
        else if(tipo=="Rally"){
            double sp=view->getCarDetail()->getSpeed();
            QString d=view->getCarDetail()->getDrive();
            bool c=view->getCarDetail()->isManualGearbox();
            model->changeRallyCar(pos,nome,cv,sp,d.toStdString(),c);
        }
        view->setCarName(no);
    }
    catch(Anomalia e){
        checkFields(e);
    }
}

void Controller::buildResearchList() const{
    vector<int> pos=research();
    if(!pos.empty()){
        QListWidget* searchlist=new QListWidget();
        QListWidget* list=view->getList();
        for(unsigned long j=0; j<pos.size(); ++j){
            int p=pos[j];
            QListWidgetItem* item=list->item(p);
            searchlist->addItem(item->text());
        }
        view->openResearchWindow(searchlist);
    }
}

vector<int> Controller::research() const{
    QString rule=view->getResearchAttribute();
    QString value=view->getResearchKey();
    vector<int> pos;
    if(!rule.isEmpty() && !value.isEmpty()){
        try {
            if(rule == "Nome")
                pos=model->searchCarName(value.toStdString());
            else if(rule == "Tipo auto")
                pos=model->searchCarType(value.toStdString());
            else if(rule == "CV maggiori di")
                pos=model->searchCV(value.toInt());
            else if(rule == "CV minori di")
                pos=model->searchCV(value.toInt(),false);
            else if(rule == "Velocità minore di")
                pos=model->searchSpeed(value.toDouble(),false);
            else if(rule == "Velocità maggiore di")
                pos=model->searchSpeed(value.toDouble());
            else if(rule == "Anno produzione")
                pos=model->searchYear(value.toInt());
            else if(rule == "Ambiente")
                pos=model->searchEnvironment(value.toStdString());
        }
        catch(Anomalia){
            view->errorMessage("Nessun risultato", "La ricerca non ha portato ad alcun risultato");
        }
    }
    return pos;
}

// SLOT che indica al modello di salvare la lista nel file indicato da path
void Controller::saveAs() const throw(Anomalia){
    QString s=view->saveAsFilename();
    if(s != "\0"){
        try {
            model->saveAs(s.toStdString());
        } catch (Anomalia) {
            view->errorMessage("Salvataggio fallito", "Non è stato possibile salvare il file");
        }
    }
}

void Controller::save() const throw(Anomalia){
    if(!view->getFilename().isEmpty()){
        try {
            model->saveAs(view->getFilename().toStdString());
        } catch (Anomalia) {
            view->errorMessage("Salvataggio fallito", "Non è stato possibile salvare il file");
        }
    }
    else
        saveAs();
}

void Controller::newFile() const{
    view->loadPage();
}

void Controller::load() const throw(Anomalia){
    try {
        view->loadPage(true);
    } catch (Anomalia) {
        view->errorMessage("Errore di apertura", "Non è stato possibile aprire il file");
    }
}

QListWidget* Controller::loadData(){
    model->loadFile(view->getFilename().toStdString());
    QListWidget* list(new QListWidget());
    for(int i=0; i<model->count(); ++i)
        list->addItem(QString::fromStdString(model->getDptCar(static_cast<unsigned int>(i))->getName()));
    return list;
}

void Controller::getEnvironment() const{
    try {
        int r=view->itemRow();
        if(r!=-1){
            DeepPtr<Car> dpt=model->getDptCar(static_cast<unsigned int>(r));
            string env=dpt->environment();
            view->showEnvironment(QString::fromStdString(env));
        }
    } catch (Anomalia) {
        view->errorMessage("Azione annullata", "Nessun auto selezionata");
    }

}

void Controller::checkFields(const Anomalia& e) const{
    switch(e.getError()){
        case 'n':
            view->errorMessage("Inserimento annullato", "Campo 'nome' deve contenere almeno un carattere");
        break;
        case 'c':
            view->errorMessage("Inserimento annullato", "Campo 'CV' deve avere valor minimo 2 e massimo 1100");
        break;
        case 's':
            view->errorMessage("Inserimento annullato", "Campo 'Velocità massima' deve avere valor minimo 60 e massimo 350");
        break;
        case 'h':
            view->errorMessage("Inserimento annullato", "Campo 'Altezza dal suolo' deve avere valor minimo 8 e massimo 40");
        break;
        case 'y':
            view->errorMessage("Inserimento annullato", "Campo 'Anno produzione' deve avere valor minimo 1800 e massimo 1995");
        break;
        case 'v':
            view->errorMessage("Modifica annullata","Impossibile modificare l'auto");
        break;
        default:
            view->errorMessage("Azione annullata", "Nessun auto selezionata");
        break;
    }
}
