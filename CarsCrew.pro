######################################################################
# POWERED BY FRANCESCO FREDA AND CARS CREW COMPANY
######################################################################

QT += widgets

TEMPLATE = app
TARGET = CarsCrew

CONFIG += c++11

# Input
HEADERS += Controller/anomalia.h \
           Controller/controller.h \
           Model/container.h \
           Model/deeptr.h \
           Model/model.h \
           Model/xmli.h \
           Model/xmlo.h \
           View/cardetail.h \
           View/carsview.h \
           View/insertcar.h \
           View/researchingcars.h \
           Model/Gerarchia/car.h \
           Model/Gerarchia/offroad.h \
           Model/Gerarchia/rally.h \
           Model/Gerarchia/sport.h \
           Model/Gerarchia/vintage.h

SOURCES += Controller/anomalia.cpp \
           Controller/controller.cpp \
           Model/model.cpp \
           Model/xmli.cpp \
           Model/xmlo.cpp \
           View/cardetail.cpp \
           View/carsview.cpp \
           View/insertcar.cpp \
           View/main.cpp \
           View/researchingcars.cpp \
           Model/Gerarchia/car.cpp \
           Model/Gerarchia/offroad.cpp \
           Model/Gerarchia/rally.cpp \
           Model/Gerarchia/sport.cpp \
           Model/Gerarchia/vintage.cpp

RESOURCES += resources.qrc
