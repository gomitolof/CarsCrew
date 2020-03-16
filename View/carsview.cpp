#include <QFileDialog>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include <QDesktopWidget>
#include <QCloseEvent>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QPushButton>
#include <QMenu>
#include <QMenuBar>
#include <QListWidget>
#include "Controller/controller.h"
#include "carsview.h"
#include "cardetail.h"
#include "researchingcars.h"
#include "insertcar.h"

CarsView::CarsView(bool loadFile, QWidget *parent): QWidget(parent),filename(QString()),attribute(new QComboBox(this)),
    searchBar(new QLineEdit(this)),list(new QListWidget(this)),form(new insertCar()),dialog(new CarDetail(this)),
    results(new ResearchingCars(this)){

    setWindowIcon(QIcon(":/images/img/icon_car.jpg")); // icona del programma
    setFixedSize(QSize(850, 450)); //dimensione fissa non ridimensionabile

    controller=new Controller(this);

    if(loadFile)
        loadData(); //caricamento modello
    else
        setWindowTitle("Cars Crew");

    QHBoxLayout *mainLayout=new QHBoxLayout;
    QHBoxLayout *menuLayout=new QHBoxLayout;
    QHBoxLayout *searchLayout=new QHBoxLayout;
    QHBoxLayout *searchFieldsLayout=new QHBoxLayout;
    QHBoxLayout *searchButtonsLayout=new QHBoxLayout;
    QVBoxLayout *contLayout=new QVBoxLayout;
    QHBoxLayout *buttonLayout=new QHBoxLayout;
    QVBoxLayout *insertLayout=new QVBoxLayout;

    attribute->addItem("Nome");
    attribute->addItem("Tipo auto");
    attribute->addItem("CV maggiori di");
    attribute->addItem("CV minori di");
    attribute->addItem("Velocità maggiore di");
    attribute->addItem("Velocità minore di");
    attribute->addItem("Anno produzione");
    attribute->addItem("Ambiente");
    searchBar->setPlaceholderText("Valore");
    QLabel* searchText=new QLabel("&Ricerca/eliminazione: ");
    searchText->setBuddy(attribute);
    searchText->setObjectName("title");
    QPushButton* sendSearchData = new QPushButton("Ricerca");
    sendSearchData->setToolTip("Cerca auto nella lista");
    QPushButton* removeSearchData = new QPushButton("Elimina auto filtrate");
    removeSearchData->setToolTip("Rimuove tutte le auto in base al criterio scelto");
    QPushButton* clearSearchButton = new QPushButton("X");
    clearSearchButton->setToolTip(tr("Elimina testo ricerca"));
    clearSearchButton->setObjectName("clearbutton");

    searchLayout->addWidget(searchText);

    searchFieldsLayout->addWidget(attribute);
    searchFieldsLayout->addWidget(searchBar);
    searchFieldsLayout->addWidget(clearSearchButton);

    searchButtonsLayout->addWidget(sendSearchData);
    searchButtonsLayout->addWidget(removeSearchData);

    //Menu
    QMenuBar *menuBar = new QMenuBar(this);
    QMenu *menu = new QMenu("File", menuBar);
    QMenu *change = new QMenu("Modifica", menuBar);
    QAction *newFile = new QAction("Nuovo...", menu);
    QAction *load = new QAction("Carica", menu);
    QAction *save = new QAction("Salva", menu);
    QAction *saveAs = new QAction("Salva come...", menu);
    QAction *exit = new QAction("Esci", menu);
    QAction *deleteAll = new QAction("Elimina tutto", change);

    menuBar->addMenu(menu);
    menuBar->addMenu(change);
    menu->addAction(newFile);
    menu->addAction(load);
    menu->addAction(save);
    menu->addAction(saveAs);
    menu->addAction(exit);
    change->addAction(deleteAll);
    menuLayout->addWidget(menuBar);

    //Bottoni
    QPushButton *buttonAdd=new QPushButton("Inserisci",this);
    buttonAdd->setToolTip("Aggiungi elemento");
    QPushButton *buttonEnv=new QPushButton("Ambiente",this);
    buttonEnv->setToolTip("Ambiente preferito dell'auto");
    QPushButton *buttonRemove = new QPushButton("Elimina");
    buttonRemove->setToolTip("Elimina elemento");
    QPushButton *showButton = new QPushButton("Visualizza/Modifica");
    showButton->setToolTip("Visualizza/Modifica un elemento");

    QLabel* insTitle=new QLabel("Inserimento auto:");
    //insTitle->setAlignment(Qt::AlignTop | Qt::AlignCenter);
    insTitle->setObjectName("title");

    QLabel* listTitle=new QLabel("Garage: ");
    listTitle->setBuddy(list);

    buttonLayout->addWidget(showButton);
    buttonLayout->addWidget(buttonEnv);
    buttonLayout->addWidget(buttonRemove);
    insertLayout->addWidget(insTitle);
    insertLayout->addWidget(form);
    insertLayout->addWidget(buttonAdd);

    contLayout->addLayout(menuLayout);
    contLayout->addLayout(searchLayout);
    contLayout->addLayout(searchFieldsLayout);
    contLayout->addLayout(searchButtonsLayout);
    contLayout->addWidget(listTitle);
    contLayout->addWidget(list);
    contLayout->addLayout(buttonLayout);

    mainLayout->addLayout(contLayout);

    mainLayout->addLayout(insertLayout);

    setLayout(mainLayout);

    connect(attribute, SIGNAL(currentTextChanged(const QString&)), this, SLOT(setResearchValidator(const QString&)));
    emit(attribute->currentTextChanged(attribute->currentText()));
    connect(deleteAll, SIGNAL(triggered()), controller, SLOT(removeAll()));
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));
    connect(buttonAdd, SIGNAL(clicked()), controller, SLOT(addItem()));
    connect(showButton, SIGNAL(clicked()), controller, SLOT(seeDetail()));
    connect(buttonEnv, SIGNAL(clicked()), controller, SLOT(getEnvironment()));
    connect(buttonRemove, SIGNAL(clicked()), controller, SLOT(removeItem()));
    connect(removeSearchData, SIGNAL(clicked()), controller, SLOT(removeAllResults()));
    connect(newFile, SIGNAL(triggered()), controller, SLOT(newFile()));
    connect(load, SIGNAL(triggered()), controller, SLOT(load()));
    connect(saveAs, SIGNAL(triggered()), controller, SLOT(saveAs()));
    connect(save, SIGNAL(triggered()), controller, SLOT(save()));
    connect(sendSearchData, SIGNAL(clicked()), controller, SLOT(buildResearchList()));
    connect(clearSearchButton, SIGNAL(clicked()), searchBar, SLOT(clear()));
}

void CarsView::setResearchValidator(const QString& s){
    searchBar->clear();
    searchBar->setValidator(nullptr);
    if(s == "CV maggiori di" || s == "CV minori di"){
        QIntValidator* valCV=new QIntValidator(2,1100,this);
        searchBar->setValidator(valCV);
    }
    else if(s == "Velocità maggiore di" || s == "Velocità maggiore di"){
        QDoubleValidator* valSp=new QDoubleValidator(this);
        valSp->setRange(60,450);
        searchBar->setValidator(valSp);
    }
    else if(s == "Anno produzione"){
        QIntValidator* valCV=new QIntValidator(1800,1995,this);
        searchBar->setValidator(valCV);
    }
}

insertCar* CarsView::getForm() const{
    return form;
}

CarDetail* CarsView::getCarDetail() const{
    return dialog;
}

ResearchingCars* CarsView::getResults() const{
    return results;
}

QString CarsView::getFilename() const{
    return filename;
}

QString CarsView::getResearchAttribute() const{
    return attribute->currentText();
}

QString CarsView::getResearchKey() const{
    return searchBar->text();
}

QListWidget* CarsView::getList() const{
    return list;
}

void CarsView::add() const{
    // Lo aggiungo
    list->addItem(form->getCarName());
    // Svuoto il campo di inserimento
    form->clearForm();
}

void CarsView::openDialog() const{
    dialog->show();
    connect(dialog, SIGNAL(changeClicked()), controller, SLOT(changeCar()));
}

void CarsView::openSportCar(QString n, QString en, int c, double s, QString d){
    dialog=new CarDetail("Sportiva", en, n, c, s, d);
    openDialog();
}

void CarsView::openOffRoadCar(QString n, QString en, int c, double h){
    dialog=new CarDetail("Fuoristrada", en, n, c, 0.0, "\0", h);
    openDialog();
}

void CarsView::openVintageCar(QString n, QString en, int c, int y){
    dialog=new CarDetail("Vintage", en, n, c, 0.0, "\0", 0.0, y);
    openDialog();
}

void CarsView::openRallyCar(QString n, QString en, int c, double s, QString d, bool g){
    dialog=new CarDetail("Rally", en, n, c, s, d, 0.0, 0, g);
    openDialog();
}

void CarsView::setCarName(QString s){
    QList<QListWidgetItem*> sel_item= list->selectedItems();
    for(QList<QListWidgetItem*>::iterator i=sel_item.begin(); i!=sel_item.end(); ++i){
        if((*i)->text()!=s)
            (*i)->setText(s);
    }
}

QString CarsView::selectedItem() const{
    if (!list->selectedItems().empty())
        return list->selectedItems().first()->text();
    else
        throw Anomalia('l');
}

int CarsView::itemRow() const{
    if (!list->selectedItems().empty()){
        QListWidgetItem* item=list->selectedItems().first();
        return list->row(item);
    }
    else
        throw Anomalia('l');
}

void CarsView::remove() const{
    qDeleteAll(list->selectedItems());
}

void CarsView::remove(int pos) const{
    list->takeItem(pos);
}

void CarsView::removeAll() const{
    list->clear();
}

// Restituisce il path di salvataggio per il file
QString CarsView::saveAsFilename(){
    filename = QFileDialog::getSaveFileName(this, tr("Save file"), "../CarsCrew/data/", "Tutti i files (*);;XML files (*.xml)");
    if(!filename.isEmpty()){
        setWindowTitle(QFileInfo(filename).fileName() + tr(" - Cars Crew"));
        return filename;
    }
    return "\0";
}

void CarsView::loadData(){
    try{
        filename = QFileDialog::getOpenFileName(this,"Load from a file", "../CarsCrew/data/", "Tutti i files (*);;XML files (*.xml)");
        if(!filename.isEmpty()){
            setWindowTitle(QFileInfo(filename).fileName() + " - Cars Crew");
            list->clear();
            list=controller->loadData();
        }
    }
    catch(...){
        throw Anomalia('r');
    }
}

void CarsView::loadPage(bool load){
    CarsView* cw = new CarsView (load);
    close();
    cw->show();
}

void CarsView::openResearchWindow(QListWidget* res){
    results=new ResearchingCars(searchBar->text(),res,attribute->currentText());
    results->show();
    connect(results, SIGNAL(removeClicked()), controller, SLOT(removeItemResults()));
    connect(results, SIGNAL(changeClicked()), controller, SLOT(seeDetail()));
    connect(results, SIGNAL(removeAllClicked()), controller, SLOT(removeAllResults()));
}

void CarsView::closeEvent(QCloseEvent *event){
    QMessageBox::StandardButton saveButton = QMessageBox::question( this, "Cars Crew", "Vuoi salvare i tuoi dati?",
        QMessageBox::Cancel | QMessageBox::No | QMessageBox::Yes);
    if(saveButton==QMessageBox::Cancel)
        event->ignore();
    else {
        if(saveButton==QMessageBox::Yes)
            controller->save();
        event->accept();
    }
}

void CarsView::showEnvironment(QString env) const{
    QPixmap pixmap = QPixmap(":/images/img/circuito.jpg");
    if(env=="città")
        pixmap = QPixmap(":/images/img/citta.jpg");
    else if(env=="deserto")
        pixmap = QPixmap(":/images/img/deserto.jpg");
    else if(env=="montagna")
        pixmap = QPixmap(":/images/img/montagna.jpg");
    else if(env=="terreno irregolare")
        pixmap = QPixmap(":/images/img/terreno_irregolare.jpg");
    QMessageBox qmsBox;
    qmsBox.setText("Ambiente preferito di "+selectedItem()+": "+env);
    qmsBox.setIconPixmap(pixmap);
    qmsBox.exec();
}

void CarsView::errorMessage(const QString& m1, const QString& m2) const{
    QMessageBox box(QMessageBox::Warning, m1, m2, QMessageBox::Ok);
    box.exec();
}

CarsView::~CarsView() {
    if (controller)
        delete controller;
}
