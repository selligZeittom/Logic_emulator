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

    void loadFile(QString path);
    void convertJsonToGates();
    void drawResults();
    Pin* getPinFromLabel(QString labelPinToFind);
    void setGatesAndPins();
    void processError(QString labelError);

private:
    void outputResultsToString();
    PortData* thePortData;
    QFile* file ;
    QString fileName;
    QString result;
    QString code;
    QVector<Gate*> vGates;
    QString path;
    int levelMax;

};

#endif // DATA_H
