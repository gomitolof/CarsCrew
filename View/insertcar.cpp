#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "insertcar.h"
#include "Controller/anomalia.h"

insertCar::insertCar(QWidget* parent):QWidget(parent),type(new QLabel("&Tipo di auto",this)),
    dri(new QLabel("&Trazione dell'auto",this)),name(new QLabel("&Nome dell'auto",this)),
    cv(new QLabel("&Cavalli",this)),y(new QLabel("&Anno produzione",this)),
    sp(new QLabel("&Velocità massima",this)),height(new QLabel("&Altezza dal suolo",this)),
    gbox(new QLabel("&Cambio sequenziale",this)), carType(new QComboBox(this)), drive(new QComboBox(this)),
    carName(new QLineEdit(this)),CV(new QSpinBox(this)), year(new QSpinBox(this)), speed(new QDoubleSpinBox(this)),
    hfg(new QDoubleSpinBox(this)),gear(new QCheckBox(this)){

    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    QVBoxLayout* formLayout= new QVBoxLayout();
    QHBoxLayout* typeLayout = new QHBoxLayout();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QHBoxLayout* cvLayout = new QHBoxLayout();
    QHBoxLayout* speedLayout = new QHBoxLayout();
    QHBoxLayout* driveLayout = new QHBoxLayout();
    QHBoxLayout* heightLayout = new QHBoxLayout();
    QHBoxLayout* yearLayout = new QHBoxLayout();
    QHBoxLayout* gearLayout = new QHBoxLayout();


    carType->addItem("Sport");
    carType->addItem("Fuoristrada");
    carType->addItem("Vintage");
    carType->addItem("Rally");
    type->setBuddy(carType);

    name->setBuddy(carName);

    CV->setMinimum(2);
    CV->setMaximum(1100);
    CV->setValue(30);
    CV->setWrapping(true);
    CV->setSuffix(" CV");

    cv->setBuddy(CV);

    speed->setMinimum(60);
    speed->setMaximum(450);
    speed->setValue(150);
    speed->setWrapping(true);
    speed->setSuffix(" Km/h");

    sp->setBuddy(speed);

    drive->addItem("Posteriore");
    drive->addItem("Integrale");
    drive->addItem("Anteriore");

    dri->setBuddy(drive);

    hfg->setMinimum(8);
    hfg->setMaximum(40);
    hfg->setValue(12);
    hfg->setWrapping(true);
    hfg->setSuffix(" cm");

    height->setBuddy(hfg);

    year->setMinimum(1800);
    year->setMaximum(1995);
    year->setValue(1970);
    year->setWrapping(true);

    y->setBuddy(year);

    gbox->setBuddy(gear);

    typeLayout->addWidget(type);
    typeLayout->addWidget(carType);
    nameLayout->addWidget(name);
    nameLayout->addWidget(carName);
    cvLayout->addWidget(cv);
    cvLayout->addWidget(CV);
    speedLayout->addWidget(sp);
    speedLayout->addWidget(speed);
    driveLayout->addWidget(dri);
    driveLayout->addWidget(drive);
    heightLayout->addWidget(height);
    heightLayout->addWidget(hfg);
    yearLayout->addWidget(y);
    yearLayout->addWidget(year);
    gearLayout->addWidget(gbox);
    gearLayout->addWidget(gear);

    type->setObjectName("distance");
    carType->setObjectName("distance");
    name->setObjectName("distance");
    carName->setObjectName("distance");
    cv->setObjectName("distance");
    CV->setObjectName("distance");
    sp->setObjectName("distance");
    speed->setObjectName("distance");
    dri->setObjectName("distance");
    drive->setObjectName("distance");
    height->setObjectName("distance");
    hfg->setObjectName("distance");
    y->setObjectName("distance");
    year->setObjectName("distance");
    gbox->setObjectName("distance");
    gear->setObjectName("distanceGear");

    formLayout->addLayout(typeLayout);
    formLayout->addLayout(nameLayout);
    formLayout->addLayout(cvLayout);
    formLayout->addLayout(speedLayout);
    formLayout->addLayout(driveLayout);
    formLayout->addLayout(heightLayout);
    formLayout->addLayout(yearLayout);
    formLayout->addLayout(gearLayout);

    mainLayout->addLayout(formLayout);
    setLayout(mainLayout);

    connect(carType, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setFields(const QString &)));
    setLayout(mainLayout);
    emit(carType->currentTextChanged(carType->currentText()));
}

void insertCar::setFields(const QString& s){
    sp->setVisible(false);
    speed->setVisible(false);
    dri->setVisible(false);
    drive->setVisible(false);
    height->setVisible(false);
    hfg->setVisible(false);
    y->setVisible(false);
    year->setVisible(false);
    gbox->setVisible(false);
    gear->setVisible(false);
    if(s=="Sport" || s=="Rally"){
        sp->setVisible(true);
        speed->setVisible(true);
        dri->setVisible(true);
        drive->setVisible(true);
        if(s=="Rally"){
            gbox->setVisible(true);
            gear->setVisible(true);
        }
    }
    else if(s=="Fuoristrada"){
        height->setVisible(true);
        hfg->setVisible(true);
    }
    else if(s=="Vintage"){
        y->setVisible(true);
        year->setVisible(true);
    }
}

QString insertCar::getCarType() const{
    return carType->currentText();
}

QString insertCar::getDrive() const{
    return drive->currentText();
}

QString insertCar::getCarName() const{
    if(carName->text().length() > 0)
        return carName->text();
    else
        throw Anomalia('n');
}

int insertCar::getCV() const{
    if(CV->value()>=2 && CV->value()<=1100)
        return CV->value();
    else
        throw Anomalia('c');
}

double insertCar::getSpeed() const{
    if(speed->value()>=60.0 && speed->value()<=450.0)
        return speed->value();
    else
        throw Anomalia('s');
}

double insertCar::getHFG() const{
    if(hfg->value()<=40 && hfg->value()>=8)
        return hfg->value();
    else
        throw Anomalia('h');
}

int insertCar::getYear() const{
    if(year->value()>=1800 && year->value()<=1995)
        return year->value();
    else
        throw Anomalia('y');
}

QString insertCar::getGearbox() const{
    return gear->isChecked() ? "Sequenziale" : "Manuale";
}

void insertCar::clearForm(){
    carName->clear();
    CV->setValue(30);
    speed->setValue(150);
    year->setValue(1970);
    hfg->setValue(12);
    gear->setChecked(false);
}
