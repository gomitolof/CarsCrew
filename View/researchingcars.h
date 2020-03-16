#ifndef RESEARCHINGCAR_H
#define RESEARCHINGCAR_H
#include <QDialog>

class QListWidget;

class ResearchingCars : public QDialog
{
    Q_OBJECT
private:
    QListWidget* carslist;
public:
    explicit ResearchingCars(QWidget* =nullptr);
    explicit ResearchingCars(QString, QListWidget* =nullptr, QString = "Nome", QWidget* =nullptr);
    ~ResearchingCars() =default;
    QString selectedItem() const;
    int itemRow() const;
signals:
    void changeClicked();
    void removeClicked();
    void removeAllClicked();
};

#endif // RESEARCHINGCAR_H
