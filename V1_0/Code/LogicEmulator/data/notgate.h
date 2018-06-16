#ifndef NOTGATE_H
#define NOTGATE_H

#include "gate.h"

class NotGate : public Gate
{
public:
    NotGate();
    NotGate(QString id, int level, QVector<Pin *> ioPins);
    ~NotGate();

    // Gate interface
public:
    virtual void setXYpins();
    virtual void updateLogic(int maxLevel);
};

#endif // NOTGATE_H
