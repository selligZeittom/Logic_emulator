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
#include <QStringList>

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
    void checkValidity(QString newCode);
    void updateInputAndOutput();

private:
    void outputResultsToString();
    PortData* thePortData;
    QFile* file ;
    QString fileName;
    QString result;
    QString codeChecked;
    QString codeModified;
    QVector<Gate*> vGates;
    QString path;
    int levelMax;

};

#endif // DATA_H
