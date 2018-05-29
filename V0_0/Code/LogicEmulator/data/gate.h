#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <QString>
#include <QVector>
#include <iterator>

#include "pin.h"

class Gate
{
public:
    Gate();
    Gate(QString id, int type, int level, int nInputs, QVector<Pin> IOpins);
    virtual ~Gate();

    void initRelations();

private:
    void computeLogic();
    int type; //0 : AND, 1 : OR, 2 : NOT
    QString id;
    int level;
    int nInputs;
    QVector<Pin> IOpins;
    Pin* outputPin;
    bool output;

    bool getOutput() const;

};

#endif // GATE_H
