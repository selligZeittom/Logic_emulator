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
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStringList>

#include "gate.h"
#include "andgate.h"
#include "notgate.h"
#include "orgate.h"

class PortData;

class Data
{

public:
    Data();
    virtual ~Data();
    void initRelations(PortData* p1);

    void loadFile(QString path);
    void convertJsonToGates();
    void drawResults(bool isValid);
    Pin* getPinFromLabel(QString labelPinToFind);
    void setGatesAndPins();
    void processError(QString labelError);
    void checkModifications(QString data);
    void updateInputAndOutput(bool isValid);

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

    //store the connectedLabel to update them
    QStringList labelsList;

};

#endif // DATA_H
