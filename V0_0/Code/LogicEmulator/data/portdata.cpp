#include "portdata.h"
#include "data.h"

PortData::PortData()
{
    this->data = NULL;
    this->thePortUI = NULL;
}

PortData::~PortData()
{
}

void PortData::initRelations(Data *p1, PortUI *p2)
{
    this->data = p1;
    this->thePortUI = p2;

}

void PortData::loadFile()
{
    data->loadFile();
}

void PortData::convertJsonToGates()
{
    data->convertJsonToGates();
}

void PortData::computeLogic()
{
    data->computeLogic();
}

void PortData::drawGates()
{

}

void PortData::setPath(QString path)
{
    data->setPath(path);
}

void PortData::onDataChanged()
{

}
