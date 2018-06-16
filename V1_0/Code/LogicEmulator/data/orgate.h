#ifndef ORGATE_H
#define ORGATE_H

#include "gate.h"

class OrGate : public Gate
{
public:
    OrGate();
    OrGate(QString id, int level, QVector<Pin *> ioPins);
    ~OrGate();

    // Gate interface
public:
    virtual void setXYpins();
    virtual void updateLogic(int maxLevel);
};

#endif // ORGATE_H
