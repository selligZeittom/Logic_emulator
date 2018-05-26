#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QFile>
#include <QFileDialog>
#include <QJsonDocument>
#include <QString>

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

private:
    PortData* thePortData;
    QJsonDocument* jsonConverter ;
    QFile* file ;
    QVector<Gate> gates;
    QString path;

};

#endif // DATA_H
