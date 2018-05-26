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
    QFile file(":/gates/AND.json");
    file.open(QIODevice::ReadOnly);
    QTextStream reader(&file);
    QString data = reader.readAll();
    file.close();

    qDebug() << data;
    QByteArray byteData = data.toLocal8Bit();
    QJsonDocument doc = QJsonDocument::fromJson(byteData);

    if(doc.isNull()){
        qDebug()<<"Failed to create JSON doc.";
    }

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

    return a.exec();
}
