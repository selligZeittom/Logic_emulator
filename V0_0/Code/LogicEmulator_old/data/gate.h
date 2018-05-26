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
    Gate(QString label, uint8_t id, uint8_t level, uint8_t nInputs, QVector<Pin>* pins);
    ~Gate();

    void initRelations();

private:
    void computeLogic();
    QString label;
    uint8_t id; //0 : AND, 1 : OR, 2 : NOT
    uint8_t level;
    uint8_t nInputs;
    QVector<Pin>* pins;
    bool output;

    bool getOutput() const;

};

#endif // GATE_H
