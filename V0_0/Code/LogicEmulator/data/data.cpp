#include "data.h"
#include "portdata.h"


Data::Data()
{
    this->thePortData = NULL;
    this->jsonConverter = NULL;
    this->file = NULL;
}

Data::~Data()
{

}

void Data::initRelations(PortData *p1)
{
    this->thePortData = p1;
}

void Data::loadFile()
{

}

void Data::convertJsonToGates()
{

}

void Data::computeLogic()
{

}

void Data::setPath(QString path)
{
    this->path = path;
}
