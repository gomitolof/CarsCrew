#include "carsview.h"
#include <QApplication>
#include <QSplashScreen>
#include <QTimer>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/css/stile/qss.css");
    file.open(QFile::ReadOnly);
    QString style = QLatin1String(file.readAll());
    a.setStyleSheet(style);
    file.close();

    CarsView w(true);
    w.show();
    return a.exec();
}
