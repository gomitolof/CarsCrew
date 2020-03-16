#ifndef CARDETAIL_H
#define CARDETAIL_H

#include <QDialog>

class QLineEdit;
class QComboBox;
class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;
class QLabel;
class QPushButton;
class QString;

class CarDetail : public QDialog
{
    Q_OBJECT
private:
    QLabel *carType,* img, *environ;
    QComboBox *driv;
    QLineEdit *carName;
    QSpinBox *cav, *year;
    QDoubleSpinBox *spe,*hfg;
    QCheckBox *gear;
public:
    explicit CarDetail(QWidget* =nullptr);
    explicit CarDetail(QString, QString ="città", QString ="private", int =50, double =180.0, QString ="Posteriore", double =12.0, int =1980, bool =true, QWidget* =nullptr);
    ~CarDetail() =default;
    QString getCarType() const;
    QString getCarName() const;
    QString getDrive() const;
    int getCV() const;
    double getSpeed() const;
    double getHFG() const;
    int getYear() const;
    bool isManualGearbox() const;
    void setCarName(QString);
    void setCV(int);
    void setSpeed(double);
    void setDrive(QString);
    void setHeightFromTheGround(double);
    void setYear(int);
    void setSequencialGearboxChecked(bool);
signals:
    void changeClicked();
};

#endif // CARDETAIL_H
