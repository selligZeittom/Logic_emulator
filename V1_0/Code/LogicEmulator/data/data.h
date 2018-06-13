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
    void checkModifications(QString newCode);
    void sortCodeIntoQStringList(QString newCode, QStringList &idList, QStringList &idLabelsList, QStringList &idConnectedLabelsList, QStringList &levelList);
    void updateInputAndOutput();

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

    //store the id, label, connectedLabel and level as qstring when they're valid
    QStringList id;
    QStringList labels;
    QStringList connectedLabels;
    QStringList levels;

    //temp list to check the validity of a new code
    QStringList idTemp;
    QStringList labelsTemp;
    QStringList connectedLabelsTemp;
    QStringList levelsTemp;
};

#endif // DATA_H
