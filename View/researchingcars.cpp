#include <QLabel>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include "researchingcars.h"

ResearchingCars::ResearchingCars(QWidget* parent):QDialog (parent){}

ResearchingCars::ResearchingCars( QString filter, QListWidget* l, QString att, QWidget* parent):QDialog(parent), carslist(l){

    setWindowTitle(filter+" - Cars Crew");

    QVBoxLayout* mainLayout=new QVBoxLayout;
    QHBoxLayout* buttonsLayout= new QHBoxLayout;

    //Bottoni
    QPushButton *buttonRemove = new QPushButton("Elimina");
    buttonRemove->setToolTip("Elimina elemento");
    QPushButton *showButton = new QPushButton("Visualizza/Modifica");
    showButton->setToolTip("Visualizza/Modifica un elemento");
    QPushButton *removeAll = new QPushButton("Elimina tutto");
    removeAll->setToolTip("Rimuove tutte le auto trovate nella ricerca");
    QPushButton *closeButton = new QPushButton("Chiudi ricerca");
    closeButton->setToolTip("Chiudi finestra");

    buttonsLayout->addWidget(showButton);
    buttonsLayout->addWidget(buttonRemove);
    buttonsLayout->addWidget(removeAll);
    buttonsLayout->addWidget(closeButton);

    QLabel* researchTitle=new QLabel("Ricerca per "+att+": "+filter);
    researchTitle->setObjectName("title");

    mainLayout->addWidget(researchTitle);
    mainLayout->addWidget(carslist);
    mainLayout->addLayout(buttonsLayout);

    connect(buttonRemove, SIGNAL(clicked()), this, SIGNAL(removeClicked()));
    connect(showButton, SIGNAL(clicked()), this, SIGNAL(changeClicked()));
    connect(removeAll, SIGNAL(clicked()), this, SIGNAL(removeAllClicked()));
    connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(buttonRemove, SIGNAL(clicked()), this, SLOT(close()));
    connect(removeAll, SIGNAL(clicked()), this, SLOT(close()));
    setLayout(mainLayout);
}

QString ResearchingCars::selectedItem() const{
    if (!carslist->selectedItems().empty()){
        return carslist->selectedItems().first()->text();
    }
    else return "\0";
}

int ResearchingCars::itemRow() const{
    if (!carslist->selectedItems().empty()){
        QListWidgetItem* item=carslist->selectedItems().first();
        return carslist->row(item);
    }
    else
        return -1;
}
