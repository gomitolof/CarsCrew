#ifndef CARSVIEW_H
#define CARSVIEW_H

#include <QWidget>

class QComboBox;
class QLineEdit;
class insertCar;
class ResearchingCars;
class CarDetail;
class Controller;
class QCloseEvent;
class QListWidget;

class CarsView : public QWidget{
    Q_OBJECT
private:
    Controller *controller;
    QString filename;
    QComboBox* attribute;
    QLineEdit* searchBar;
    QListWidget* list;
    insertCar* form;
    CarDetail* dialog;
    ResearchingCars* results;
protected:
    virtual void closeEvent(QCloseEvent *) override;
private slots:
    void setResearchValidator(const QString&);
public:
    explicit CarsView(bool =false, QWidget* = nullptr);
    ~CarsView() override;
    void add() const;
    QString selectedItem() const;
    int itemRow() const;
    void remove() const;
    void remove(int) const;
    void removeAll() const;
    insertCar* getForm() const;
    CarDetail* getCarDetail() const;
    ResearchingCars* getResults() const;
    QString getFilename() const;
    QString getResearchAttribute() const;
    QString getResearchKey() const;
    QListWidget* getList() const;
    void openDialog() const;
    void openSportCar(QString, QString, int, double, QString);
    void openOffRoadCar(QString, QString, int, double);
    void openVintageCar(QString, QString, int, int);
    void openRallyCar(QString, QString, int, double, QString, bool);
    void setCarName(QString);
    void openResearchWindow(QListWidget*);
    QString saveAsFilename();
    QString saveFilename();
    void loadData();
    void loadPage(bool =false);
    void showEnvironment(QString) const;
    void errorMessage(const QString&, const QString&) const;
};


#endif // CarsView_H
