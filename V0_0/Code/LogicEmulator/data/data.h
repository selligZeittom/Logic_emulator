#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QString>
#include <QDebug>
#include <QTextStream>
#include <QByteArray>

#include "gate.h"

class PortData;

class Data
{

public:
    Data();
    virtual ~Data();
    void initRelations(PortData* p1);

    void loadFile();
    void convertJsonToGates();
    void computeLogic();
    void setPath(QString path);
    void drawResults();
    Pin &getCorrespondingPin(QString label);

private:
    void setGatesAndPins();
    PortData* thePortData;
    QJsonDocument* jsonConverter ;
    QFile* file ;
    QString fileName;
    QString result;
    QString code;
    QVector<Gate> vGates;
    QVector<Pin> vPins;
    QString path;
    int levelMax;

};

#endif // DATA_H
