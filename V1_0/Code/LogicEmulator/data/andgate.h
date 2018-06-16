#ifndef ANDGATE_H
#define ANDGATE_H

#include "gate.h"


class AndGate : public Gate
{
public:
    AndGate();
    AndGate(QString id, int level, QVector<Pin*> ioPins);
    ~AndGate();

    // Gate extended functions
public:
    virtual void setXYpins();
    virtual void updateLogic(int maxLevel);
};

#endif // ANDGATE_H
