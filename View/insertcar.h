#ifndef INSERTCAR_H
#define INSERTCAR_H

#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QLabel>

class insertCar : public QWidget
{
    Q_OBJECT
private:
    QLabel *type,*dri,*name,*cv,*y,*sp,*height,*gbox;
    QComboBox *carType, *drive;
    QLineEdit *carName;
    QSpinBox *CV, *year;
    QDoubleSpinBox *speed,*hfg;
    QCheckBox *gear;
public:
    explicit insertCar(QWidget* patent=nullptr);
    QString getCarType() const;
    QString getDrive() const;
    QString getCarName() const;
    int getCV() const;
    double getSpeed() const;
    double getHFG() const;
    int getYear() const;
    QString getGearbox() const;
    void clearForm();
    ~insertCar()=default;
signals:
    void insertClicked();
private slots:
    void setFields(const QString &);
};

#endif // INSERTVIEW_H
