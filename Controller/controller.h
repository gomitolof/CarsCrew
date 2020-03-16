#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include "Model/model.h"

class CarsView;

class QListWidget;

class Controller : public QObject {
    Q_OBJECT

private:
    Model* model;
    CarsView* view;
    vector<int> research() const;
public:
    explicit Controller(CarsView*, QObject *parent = nullptr);
    ~Controller();
    QListWidget* loadData();
public slots:
    void addItem() const throw(Anomalia);
    void seeDetail();
    void changeCar() const throw(Anomalia);
    void removeItem() const throw(Anomalia);
    void removeItemResults() const throw(Anomalia);
    void removeAll() const throw(Anomalia);
    void removeAllResults() const throw(Anomalia);
    void buildResearchList() const;
    void newFile() const;
    void load() const throw(Anomalia);
    void saveAs() const throw(Anomalia);
    void save() const throw(Anomalia);
    void getEnvironment() const;
    void checkFields(const Anomalia&) const;
};

#endif // CONTROLLER_H
