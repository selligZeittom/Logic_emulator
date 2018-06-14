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
    Gate(QString id, int level, QVector<Pin *> ioPins);
    virtual ~Gate();

    int getLevel() const;
    void computeLogicAndSetPixmap();
    void updateLogic();
    QVector<Pin*> getInputPins();
    Pin *getOutputPin();
    QPixmap getQPixMap() const;
    QString outputToString();
    QString getID() const;
    void setOutputPin(Pin* oPin);
    void setInputPins(QVector<Pin*> iPins);
    void setXY(int x, int y);

private:
    //int type; //0 : AND, 1 : OR, 2 : NOT
    QString id;
    int level;
    QVector<Pin*> inputPins;
    Pin* outputPin;
    QPixmap* qpixMap;
    int x, y; //represent the point of drawing pixmap
    void setXYpins();


};

#endif // GATE_H
