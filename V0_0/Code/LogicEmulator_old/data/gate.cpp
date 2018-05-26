#include "gate.h"

Gate::Gate(QString label, uint8_t id, uint8_t level, uint8_t nInputs, QVector<Pin> *pins)
{
    this->label = label;
    this->id = id;
    this->level = level;
    this->nInputs = nInputs;
    this->pins = pins;
}

Gate::~Gate()
{

}

void Gate::initRelations()
{

}

void Gate::computeLogic()
{
    bool out = false;

    switch (id) {
    case 0:

        break;
    case 1:

        break;
    case 2:

        break;
    default:
        break;
    }
}

bool Gate::getOutput() const
{
    return output;
}
