#include "gate.h"

Gate::Gate(QString label, uint8_t id, uint8_t level, uint8_t nInputs, QVector<Pin> *pins)
{
    this->label = label;
    this->id = id;
    this->level = level;
    this->nInputs = nInputs;
    this->inputPins = pins;
}

Gate::~Gate()
{

}

void Gate::initRelations()
{

}

void Gate::computeLogic()
{


}

bool Gate::getOutput() const
{
    return output;
}
