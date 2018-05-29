#include "gate.h"

Gate::Gate(QString id = "NO_ID", int type = -1, int level = -1, int nInputs = -1, QVector<Pin> pins = NULL)
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
