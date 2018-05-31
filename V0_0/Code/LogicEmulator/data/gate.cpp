#include "gate.h"

Gate::Gate()
{

}

Gate::Gate(QString id, int type, int level, int nInputs, QVector<Pin> ioPins)
{
    this->id = id;
    this->type = type;
    this->level = level;
    this->nInputs = nInputs;
    this->inputPins = ioPins;

    //remove the last pin from the array, because it's the output pin
    if(!inputPins.isEmpty())
    {
        *(this->outputPin) = inputPins.takeLast();
    }
    else
    {
        this->outputPin = NULL;
    }
}

Gate::~Gate()
{

}

void Gate::initRelations()
{

}

void Gate::computeLogic()
{
    bool result = false;
    switch (type) {
    case 0:
        //means it's and AND gate
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
        for (int i = 0; i < inputPins.count(); ++i) {
            if(inputPins[i].getState() == true)
            {
                result = true;
            }
        }
        break;
        //means it's a NOT gate
    case 2:
        result = !(inputPins[0].getState());
        break;
    default:
        break;
    }

    //set the state of the output pin
    this->outputPin->setState(result);
}

QVector<Pin> Gate::getInputPins() const
{
    return this->inputPins;
}

bool Gate::getOutput() const
{
    return output;
}

int Gate::getLevel() const
{
    return level;
}
