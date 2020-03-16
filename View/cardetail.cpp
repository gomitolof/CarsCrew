#include "cardetail.h"
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QString>
#include <QPixmap>
#include "Controller/anomalia.h"

CarDetail::CarDetail(QWidget *parent):QDialog(parent){}

CarDetail::CarDetail(QString ty, QString en, QString nome, int CV, double speed, QString dri, double he, int ye, bool ge, QWidget* parent):
QDialog(parent), carType(new QLabel(ty,this)), img(new QLabel(this)), environ(new QLabel(en,this)), driv(new QComboBox(this)),
carName(new QLineEdit(this)), cav(new QSpinBox(this)),year(new QSpinBox(this)), spe(new QDoubleSpinBox(this)),
hfg(new QDoubleSpinBox(this)), gear(new QCheckBox(this)){

    setWindowTitle(nome+" - Cars Crew");

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    QVBoxLayout* formLayout= new QVBoxLayout();
    QHBoxLayout* typeLayout = new QHBoxLayout();
    QHBoxLayout* envLayout = new QHBoxLayout();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    QHBoxLayout* cvLayout = new QHBoxLayout();
    QHBoxLayout* speedLayout = new QHBoxLayout();
    QHBoxLayout* driveLayout = new QHBoxLayout();
    QHBoxLayout* gearLayout = new QHBoxLayout();
    QHBoxLayout* heightLayout = new QHBoxLayout();
    QHBoxLayout* yearLayout = new QHBoxLayout();
    QHBoxLayout* buttonLayout = new QHBoxLayout();

    QLabel* type(new QLabel("&Tipo di auto: ",this)),*env(new QLabel("&Ambiente preferito: ",this));
    QLabel * name(new QLabel("&Nome dell'auto",this)),* cv(new QLabel("&Cavalli",this)),* sp(new QLabel("&Velocità",this));
    QLabel* drive(new QLabel("&Trazione dell'auto",this)),* hei(new QLabel("&Altezza dal suolo",this));
    QLabel* yea(new QLabel("&Anno produzione",this)),* cs(new QLabel("&Cambio sequenziale",this));

    type->setBuddy(carType);

    env->setBuddy(environ);

    carName->setText(nome);
    name->setBuddy(carName);

    cav->setMinimum(2);
    cav->setMaximum(1100);
    cav->setValue(CV);
    cav->setWrapping(true);
    cav->setSuffix(" CV");

    cv->setBuddy(cav);

    QPixmap p(":/images/img/Sportiva.jpg");

    if(ty=="Sportiva" || ty=="Rally"){

        hei->setVisible(false);
        hfg->setVisible(false);
        year->setVisible(false);
        yea->setVisible(false);

        spe->setMinimum(60);
        spe->setMaximum(450);
        spe->setValue(speed);
        spe->setWrapping(true);
        spe->setSuffix(" Km/h");

        sp->setBuddy(spe);

        if(dri=="Posteriore"){
            driv->addItem("Posteriore");
            driv->addItem("Integrale");
            driv->addItem("Anteriore");
        }
        else if(dri=="Anteriore"){
            driv->addItem("Anteriore");
            driv->addItem("Posteriore");
            driv->addItem("Integrale");
        }
        else if(dri=="Integrale"){
            driv->addItem("Integrale");
            driv->addItem("Posteriore");
            driv->addItem("Anteriore");
        }
        drive->setBuddy(driv);

        if(ty=="Rally"){
            if(ge==true){
                gear->setChecked(true);
            }
            else{
                gear->setChecked(false);
            }
            cs->setBuddy(gear);
            p=QPixmap(":/images/img/Rally.jpg");
        }
        else {
            gear->setVisible(false);
            cs->setVisible(false);
        }
    }
    else if(ty=="Fuoristrada"){
        sp->setVisible(false);
        spe->setVisible(false);
        driv->setVisible(false);
        drive->setVisible(false);
        year->setVisible(false);
        yea->setVisible(false);
        gear->setVisible(false);
        cs->setVisible(false);

        hfg->setMinimum(8);
        hfg->setMaximum(40);
        hfg->setValue(he);
        hfg->setWrapping(true);
        hfg->setSuffix(" cm");

        hei->setBuddy(hfg);

        p=QPixmap(":/images/img/Fuoristrada.jpg");
    }
    else if(ty=="Vintage"){
        sp->setVisible(false);
        spe->setVisible(false);
        driv->setVisible(false);
        drive->setVisible(false);
        hei->setVisible(false);
        hfg->setVisible(false);
        gear->setVisible(false);
        cs->setVisible(false);

        year->setMinimum(1800);
        year->setMaximum(1995);
        year->setValue(ye);
        year->setWrapping(true);

        yea->setBuddy(year);
        p=QPixmap(":/images/img/Vintage.jpg");
    }

    img->resize(320.0,240.0);
    int w=img->width();
    int h=img->height();
    img->setPixmap(p.scaled(w,h,Qt::KeepAspectRatio));
    img->setMargin(15);

    QPushButton *buttonChange = new QPushButton("Modifica");
    buttonChange->setToolTip("Modifica elemento");
    QPushButton *buttonExit = new QPushButton("Chiudi");
    buttonExit->setToolTip("Esci");

    typeLayout->addWidget(type);
    typeLayout->addWidget(carType);
    envLayout->addWidget(env);
    envLayout->addWidget(environ);
    nameLayout->addWidget(name);
    nameLayout->addWidget(carName);
    cvLayout->addWidget(cv);
    cvLayout->addWidget(cav);
    if(ty=="Sportiva" || ty=="Rally"){
        speedLayout->addWidget(sp);
        speedLayout->addWidget(spe);
        driveLayout->addWidget(drive);
        driveLayout->addWidget(driv);
        if(ty=="Rally"){
            gearLayout->addWidget(cs);
            gearLayout->addWidget(gear);
        }
    }
    else if(ty=="Fuoristrada"){
        heightLayout->addWidget(hei);
        heightLayout->addWidget(hfg);
    }
    else if(ty=="Vintage"){
        yearLayout->addWidget(yea);
        yearLayout->addWidget(year);
    }
    buttonLayout->addWidget(buttonChange);
    buttonLayout->addWidget(buttonExit);

    formLayout->addLayout(typeLayout);
    formLayout->addLayout(envLayout);
    formLayout->addLayout(nameLayout);
    formLayout->addLayout(cvLayout);
    if(ty=="Sportiva" || ty=="Rally"){
        formLayout->addLayout(speedLayout);
        formLayout->addLayout(driveLayout);
        if(ty=="Rally"){
            formLayout->addLayout(gearLayout);
        }
    }
    else if(ty=="Fuoristrada"){
        formLayout->addLayout(heightLayout);
    }
    else if(ty=="Vintage"){
        formLayout->addLayout(yearLayout);
    }
    formLayout->addLayout(buttonLayout);
    mainLayout->addWidget(img);
    mainLayout->addLayout(formLayout);

    connect(buttonExit, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonChange, SIGNAL(clicked()), this, SIGNAL(changeClicked()));
    connect(buttonChange, SIGNAL(clicked()), this, SLOT(close()));
    setLayout(mainLayout);
}

QString CarDetail::getCarType() const{
    return carType->text();
}

QString CarDetail::getDrive() const{
    return driv->currentText();
}

QString CarDetail::getCarName() const{
    if(carName->text().length() > 0)
        return carName->text();
    else
        throw Anomalia('n');
}

int CarDetail::getCV() const{
    if(cav->value()>=2 && cav->value()<=1100)
        return cav->value();
    else
        throw Anomalia('c');
}

double CarDetail::getSpeed() const{
    if(spe->value()>=60.0 && spe->value()<=450.0)
        return spe->value();
    else
        throw Anomalia('s');
}

double CarDetail::getHFG() const{
    if(hfg->value()<=40 && hfg->value()>=8)
        return hfg->value();
    else
        throw Anomalia('h');
}

int CarDetail::getYear() const{
    if(year->value()>=1800 && year->value()<=1995)
        return year->value();
    else
        throw Anomalia('y');
}

bool CarDetail::isManualGearbox() const{
    return !gear->isChecked();
}
