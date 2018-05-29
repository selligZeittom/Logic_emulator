#include "gate.h"

Gate::Gate()
{

}

Gate::Gate(QString id, int type, int level, int nInputs, QVector<Pin> pins)
{
    this->id = id;
    this->type = type;
    this->level = level;
    this->nInputs = nInputs;
    this->IOpins = pins;
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
