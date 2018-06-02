#ifndef GATE_H
#define GATE_H

#include <iostream>
#include <QString>
#include <QVector>
#include <iterator>
#include <QPixmap>

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
    void computeLogicAndSetPixmap();
    QVector<Pin> getInputPins() const;
    QPixmap getQPixMap() const;
    QString outputToString();

private:
    int type; //0 : AND, 1 : OR, 2 : NOT
    QString id;
    int level;
    int nInputs;
    QVector<Pin> inputPins;
    Pin* outputPin;
    bool output;
    QPixmap* qpixMap;



};

#endif // GATE_H
