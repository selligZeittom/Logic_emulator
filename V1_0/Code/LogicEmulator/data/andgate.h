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
    //Set the coordinates to draw the pic and lines
    virtual void setXYpins();
    //compute the output depending on the entry
    virtual void updateLogic(int maxLevel);
};

#endif // ANDGATE_H
