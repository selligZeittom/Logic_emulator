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
    Gate(QString id, int type, int level, int nInputs, QVector<Pin> ioPins);
    virtual ~Gate();

    void initRelations();

    bool getOutput() const;
    int getLevel() const;
    void computeLogic();
    QVector<Pin> getInputPins() const;

private:
    int type; //0 : AND, 1 : OR, 2 : NOT
    QString id;
    int level;
    int nInputs;
    QVector<Pin> inputPins;
    Pin* outputPin;
    bool output;


};

#endif // GATE_H
