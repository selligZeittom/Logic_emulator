#include "gate.h"

Gate::Gate()
{

}

Gate::Gate(QString id, int level, QVector<Pin> ioPins)
{
    this->id = id;
    this->level = level;

    this->inputPins = ioPins;

    this->outputPin = new Pin();
    this->qpixMap = new QPixmap(":/gates/images/and_gate_original.png");

    //remove the last pin from the array, because it's the output pin
    if(!inputPins.isEmpty())
    {
        *(this->outputPin) = inputPins.takeLast();
    }
    else
    {
        this->outputPin = NULL;
    }
    this->nInputs = ioPins.count();
}

Gate::~Gate()
{

}

void Gate::initRelations()
{

}

void Gate::computeLogicAndSetPixmap()
{
    bool result = false;

    int type = 0;
    if(id.contains("A"))
    {
        type = 0;
    }else if(id.contains("O"))
    {
        type = 1;
    }else if(id.contains("N"))
    {
        type = 2;
    }
    switch (type) {
    case 0:
        //means it's and AND gate
        qpixMap = new QPixmap(":/gates/images/and_gate_original.png");
        result = true;
        for (int i = 0; i < inputPins.count(); ++i) {
            if(inputPins[i].getState() == false)
            {
                result = false;
            }
        }
        break;
        //means it's an OR gate
    case 1:
        qpixMap = new QPixmap(":/gates/images/or_gate_original.png");
        for (int i = 0; i < inputPins.count(); ++i) {
            if(inputPins[i].getState() == true)
            {
                result = true;
            }
        }
        break;
        //means it's a NOT gate
    case 2:
        qpixMap = new QPixmap(":/gates/images/not_gate_original.png");
        result = !(inputPins[0].getState());
        break;
    default:
        break;
    }

    //set the state of the output pin
    this->outputPin->setState(result);
}

QVector<Pin> &Gate::getInputPins()
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
    //this->outputPin = new Pin();
    this->outputPin = oPin;
}

void Gate::setInputPins(QVector<Pin> iPins)
{
    this->inputPins = iPins;
}

int Gate::getLevel() const
{
    return level;
}
