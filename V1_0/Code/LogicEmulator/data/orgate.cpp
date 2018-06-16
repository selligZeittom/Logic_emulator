#include "orgate.h"

OrGate::OrGate()
{
}

OrGate::OrGate(QString id, int level, QVector<Pin *> ioPins) : Gate(id, level, ioPins)
{
    this->qpixMap = new QPixmap(":/gates/images/or_gate_original.png");
}

OrGate::~OrGate()
{
}

void OrGate::setXYpins()
{
    for (int i = 0; i < inputPins.count(); ++i)
    {
        inputPins[i]->setXY(this->x, this->y + i * 39 + 20);
    }
    this->outputPin->setXY(this->x+80, this->y+40);
}

void OrGate::updateLogic(int maxLevel)
{
    //true if there is at least one HIGH input
    bool result = false;
    for (int i = 0; i < inputPins.count(); ++i) {
        if(inputPins[i]->getState() == true)
        {
            result = true;
        }
        this->outputPin->setState(result);
        if(this->level != maxLevel)
        {
            Pin* conPin = outputPin->getConnectedPin();
            conPin->setState(result);
        }
    }
}
