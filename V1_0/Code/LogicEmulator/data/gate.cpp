#include "gate.h"


Gate::Gate()
{

}

Gate::Gate(QString id, int level, QVector<Pin*> ioPins)
{
    this->id = id;
    this->level = level;

    this->inputPins = ioPins;

    this->outputPin = new Pin();
    this->qpixMap = new QPixmap(":/gates/images/and_gate_original.png");

    //remove the last pin from the array, because it's the output pin
    if(!inputPins.isEmpty())
    {
        this->outputPin = inputPins.takeLast();
    }
    else
    {
        this->outputPin = NULL;
    }
    this->x = 0;
    this->y = 0;
}

Gate::~Gate()
{
    if(outputPin)
    {
        delete outputPin;
        outputPin = NULL;
    }
    for (int i = 0; i < inputPins.count(); ++i)
    {
        Pin* toDestroy = inputPins[i];
        if(toDestroy)
        {
            delete toDestroy;
            toDestroy = NULL;
        }
    }
    if(qpixMap)
    {
        delete qpixMap;
        qpixMap = NULL;
    }
}

QVector<Pin*> Gate::getInputPins()
{
    return this->inputPins;
}

Pin *Gate::getOutputPin()
{
    return this->outputPin;
}

QPixmap Gate::getQPixMap() const
{
    return (*qpixMap);
}

//set a string from the output
QString Gate::outputToString()
{
    QString retVal = "the gate [";
    retVal += (this->id);

    retVal += "] has the output : NULL";
    if(outputPin!=NULL)
    {
        retVal = "the gate [";
        retVal += this->id;
        retVal += "] has the output : ";

        if(outputPin->getState())
        {
            retVal += "1";
        } else if(!outputPin->getState())
        {
            retVal += "0";
        }
    }
    return retVal;
}

QString Gate::getID() const
{
    return id;
}

void Gate::setOutputPin(Pin *oPin)
{
    this->outputPin = oPin;
}

void Gate::setInputPins(QVector<Pin*> iPins)
{
    this->inputPins = iPins;
}

void Gate::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
    setXYpins();
}

int Gate::getLevel() const
{
    return level;
}
