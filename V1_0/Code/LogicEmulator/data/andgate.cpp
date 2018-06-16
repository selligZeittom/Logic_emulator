#include "andgate.h"

AndGate::AndGate()
{
}

AndGate::AndGate(QString id, int level, QVector<Pin *> ioPins) : Gate(id, level, ioPins)
{
    //load the picture
    this->qpixMap = new QPixmap(":/gates/images/and_gate_original.png");
}

AndGate::~AndGate()
{

}

void AndGate::setXYpins()
{
    for (int i = 0; i < inputPins.count(); ++i)
    {
        inputPins[i]->setXY(this->x, this->y + i * 39 + 20);
    }
    this->outputPin->setXY(this->x+80, this->y+40);
}

void AndGate::updateLogic(int maxLevel)
{
    //if one input is LOW -> output is LOW
    bool result = true;
    for (int i = 0; i < inputPins.count(); ++i) {
        if(inputPins[i]->getState() == false)
        {
            result = false;
        }
    }
    this->outputPin->setState(result);

    //only set the connected pin if there is one
    if(this->level != maxLevel)
    {
        Pin* conPin = outputPin->getConnectedPin();
        conPin->setState(result);
    }
}
