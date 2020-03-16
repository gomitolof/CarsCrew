#include "xmlo.h"

#include <QFile>
#include <QSaveFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QMessageBox>
#include <QDebug>
#include "Gerarchia/car.h"
#include "Gerarchia/offroad.h"
#include "Gerarchia/sport.h"
#include "Gerarchia/rally.h"
#include "Gerarchia/vintage.h"
#include "Controller/anomalia.h"
using std::to_string;

XmlO::XmlO(const string& filepath) : filename(filepath) {}

/* QSaveFile rispetto a QFile è più adatto per effettuare scritture su disco. Gestisce meglio
   i casi di errore, garantendo che non vengano persi i dati del file in caso di errori in scrittura */
void XmlO::write(const Container<DeepPtr<Car>>& container) const {
    QSaveFile file(QString::fromStdString(filename));
    if(!file.open(QIODevice::WriteOnly)) {
        throw Anomalia();
    }
    QXmlStreamWriter writer(&file);
    writer.setAutoFormatting(true); // Per leggibilità del file XML
    writer.writeStartDocument();    // Scrive le intestazioni XML
    writer.writeComment("File di salvataggio dell'applicazione. Non modificare a mano.");
    writer.writeStartElement("root");
    auto cit = container.begin();
    while(cit != container.end()) {
        writer.writeStartElement("Auto");
        OffRoad* off=dynamic_cast<OffRoad*>(&(**cit));
        Sport* s=dynamic_cast<Sport*>(&(**cit));
        Rally* r=dynamic_cast<Rally*>(&(**cit));
        Vintage* v=dynamic_cast<Vintage*>(&(**cit));
        if(off){
           off=static_cast<OffRoad*>(&(**cit));
            writer.writeAttribute("tipo", QString::fromStdString("OffRoad"));
        }
        else if(r){
            r=static_cast<Rally*>(&(**cit));
            writer.writeAttribute("tipo", QString::fromStdString("Rally"));
        }
        else if(s){
            s=static_cast<Sport*>(&(**cit));
            writer.writeAttribute("tipo", QString::fromStdString("Sport"));
        }
        else if(v){
            v=static_cast<Vintage*>(&(**cit));
            writer.writeAttribute("tipo", QString::fromStdString("Vintage"));
        }
        writer.writeStartElement("nome");
        writer.writeCharacters(QString::fromStdString((*cit)->getName()));
        writer.writeEndElement();
        writer.writeStartElement("cv");
        writer.writeCharacters(QString::fromStdString(to_string((*cit)->getCV())));
        writer.writeEndElement();
        if(off!=nullptr){
            QString f=QString::fromStdString(to_string(off->getHeightFromTheGround()));
            f.chop(4);
            writer.writeStartElement("altezza");
            writer.writeCharacters(f);
            writer.writeEndElement();
        }
        else if(r!=nullptr){
            writer.writeStartElement("velocità");
            QString f=QString::fromStdString(to_string(s->getSpeed()));
            f.chop(4);
            writer.writeCharacters(f);
            writer.writeEndElement();
            writer.writeStartElement("trazione");
            writer.writeCharacters(QString::fromStdString(r->getDrive()));
            writer.writeEndElement();
            writer.writeStartElement("cambio");
            writer.writeCharacters(r->isManualGearbox() ? "Manuale" : "Sequenziale");
            writer.writeEndElement();
        }
        else if(s!=nullptr){
            writer.writeStartElement("velocità");
            QString f=QString::fromStdString(to_string(s->getSpeed()));
            f.chop(4);
            writer.writeCharacters(f);
            writer.writeEndElement();
            writer.writeStartElement("trazione");
            writer.writeCharacters(QString::fromStdString(s->getDrive()));
            writer.writeEndElement();
        }
        else if(v!=nullptr){
            writer.writeStartElement("anno");
            writer.writeCharacters(QString::fromStdString(to_string(v->getProductionYear())));
            writer.writeEndElement();
        }
        writer.writeEndElement();
        if(writer.hasError()) // se c'è stato un problema in scrittura interrompe ed esce
            throw Anomalia();
        ++cit;
    }
    writer.writeEndElement();                                        // </root>
    writer.writeEndDocument();  // chiude eventuali tag lasciati aperti e aggiunge una riga vuota alla fine
    file.commit(); // Scrive il file temporaneo su disco
}
