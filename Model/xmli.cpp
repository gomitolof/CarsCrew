#include "xmli.h"
#include <stdlib.h>
#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include "Gerarchia/car.h"
#include "Gerarchia/offroad.h"
#include "Gerarchia/sport.h"
#include "Gerarchia/rally.h"
#include "Gerarchia/vintage.h"
#include "Controller/anomalia.h"

XmlI::XmlI(const string& filepath) : filename(filepath) {}

Container<DeepPtr<Car>> XmlI::read() const {
    Container<DeepPtr<Car>> list;
    QFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::ReadOnly)) {
        throw Anomalia();
    }
    QXmlStreamReader reader(&file); // QIODevice*
    if(reader.readNextStartElement() && reader.name() == "root"){
        while(reader.readNextStartElement()) {
            if(reader.name() == "Auto") {
                // legge l'attributo 'type'
                const QXmlStreamAttributes attributes = reader.attributes();
                const QString type = attributes.hasAttribute("tipo") ? attributes.value("tipo").toString() : "";
                string nome="private";
                int cv=50;
                double sp=180.0;
                string dr="Posteriore";
                double h=12.00;
                int y=1980;
                bool cambio_man=true;
                string temp="\0";
                if(reader.readNextStartElement() && reader.name() == "nome")
                    nome = reader.readElementText().toStdString();
                if(reader.readNextStartElement() && reader.name() == "cv")
                    cv = reader.readElementText().toInt();
                if(type=="Sport" || type=="Rally"){
                    if(reader.readNextStartElement() && reader.name() == "velocità"){
                        temp=reader.readElementText().toStdString();
                        sp=atof(temp.c_str());
                    }
                    if(reader.readNextStartElement() && reader.name() == "trazione")
                        dr = reader.readElementText().toStdString();
                    if(type=="Rally" && reader.readNextStartElement() && reader.name() == "cambio")
                        cambio_man = reader.readElementText() == "Manuale" ? true : false;
                }
                else if(type=="OffRoad"){
                    if(reader.readNextStartElement() && reader.name() == "altezza")
                        temp=reader.readElementText().toStdString();
                        h = atof(temp.c_str());
                }
                else if(type=="Vintage"){
                    if(reader.readNextStartElement() && reader.name() == "anno")
                    y = reader.readElementText().toInt();
                }
                reader.skipCurrentElement();
                // creiamo un nuovo todo con il tipo giusto e lo aggiunge alla lista
                DeepPtr<Car> dpt(new Sport(nome,cv,sp,dr));
                if(type == "Rally")
                    dpt=new Rally(nome,cv,sp,dr,cambio_man);
                else if(type == "OffRoad")
                    dpt=new OffRoad(nome,cv,h);
                else if(type == "Vintage")
                    dpt=new Vintage(nome,cv,y);
                list.push_back(dpt);
            }
            else
                reader.skipCurrentElement();
            if(reader.hasError()){
                throw Anomalia();
            }
        }
    }
    file.close();
    return list;
}
