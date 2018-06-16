#include "notgate.h"

NotGate::NotGate()
{
}

NotGate::NotGate(QString id, int level, QVector<Pin *> ioPins) : Gate(id, level, ioPins)
{
    this->qpixMap = new QPixmap(":/gates/images/not_gate_original.png");
}

NotGate::~NotGate()
{

}

void NotGate::setXYpins()
{
    this->inputPins[0]->setXY(this->x, this->y + 40);
    this->outputPin->setXY(this->x+80, this->y+40);
}

void NotGate::updateLogic(int maxLevel)
{
    //toggle the input to get the output
    bool result = false;
    result = !(inputPins[0]->getState());

    this->outputPin->setState(result);

    //update the coneected pin if there is one
    if(this->level != maxLevel)
    {
        Pin* conPin = outputPin->getConnectedPin();
        conPin->setState(result);
    }
}
