#include "mainwindow.h"
#include <QApplication>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QFile>
#include <QTextStream>
#include <QString>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QFile file(":/gates/TEST1.json");

    file.open(QIODevice::ReadOnly);
    if(!file.isOpen())
    {
        qDebug()<<"Failed to open the file";
        return -1;

    }

    QTextStream reader(&file);
    QString data = reader.readAll();
    file.close();

    qDebug() << data;
    QByteArray byteData = data.toLocal8Bit();

    //the main document from the json file
    QJsonDocument doc = QJsonDocument::fromJson(byteData);

    //check the validity of the document
    if(doc.isNull()){
        qDebug()<<"Failed to create JSON doc.";
        return -1;
    }

    QJsonObject design = doc.object();

    //get the name of the file
    QString fileName = design["name"].toString();
    qDebug()<< fileName<< " : fileName";
    int nGates = design["nGates"].toInt();
    qDebug()<< nGates << " : nGates";

    //get the array of all the gates
    QJsonArray gates = design["gates"].toArray();
    if(gates.isEmpty())
    {
        qDebug()<<"Failed to create gates array";
        return -1;
    }

    //get all the gates of the design
    for(int i=0; i< gates.count(); ++i){

        //get the characteristics of the gate
        QJsonObject gate = gates.at(i).toObject();
        QString type = gate["type"].toString();
        qDebug()<< type<< " : type";
        QString id = gate["ID"].toString();
        qDebug()<< id<< " : id";
        int level = gate["level"].toInt();
        qDebug()<< level<< " : level";
        int nInput = gate["nInput"].toInt();
        qDebug()<< nInput<< " : nInput";

        //get the array of the pins
        QJsonArray pins = gate["pins"].toArray();
        if(pins.isEmpty())
        {
            qDebug()<<"Failed to create pins array";
            return -1;
        }

        for(int j=0; j< pins.count(); ++j)
        {
            QJsonObject pin = pins.at(j).toObject();
            QString label = pin["label"].toString();
            qDebug()<< label<< " : label";
            QString connected = pin["connected"].toString();
            qDebug()<< connected<< " : connected";
            qDebug() << "......................";

        }

        qDebug() << "--------------------";
    }


    /*
    QJsonObject gate = doc.object();
    qDebug() << gate["type"].toString();
    qDebug() << gate["ID"].toString();
    qDebug() << gate["level"].toString();
    qDebug() << gate["nInput"].toInt();

    QJsonArray pins = gate["pins"].toArray();
    if(pins.isEmpty())
    {
        qDebug()<<"Failed to create array";
    }
    for(int i=0; i< pins.count(); ++i){
        QJsonObject obj = pins.at(i).toObject();
        qDebug() << obj["label"].toString();
        qDebug() << obj["connected"].toString();
    }


*/
    return a.exec();
}
