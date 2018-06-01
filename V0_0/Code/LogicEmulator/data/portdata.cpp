#include "portdata.h"
#include "controller/portcontroller.h"
#include "data.h"

PortData::PortData()
{
    this->data = NULL;
    this->thePortUI = NULL;
    this->thePortController = NULL;
}

PortData::~PortData()
{
}

void PortData::initRelations(Data *p1, PortUI *p2, PortController *p3)
{
    this->data = p1;
    this->thePortUI = p2;
    this->thePortController = p3;

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
    data->drawResults();
}

void PortData::setPath(QString path)
{
    data->setPath(path);
}

void PortData::onLoadingDone()
{
    thePortController->onLoadingDone();
}

void PortData::onConvertingDone()
{
    thePortController->onConvertingDone();
}

void PortData::onComputingDone()
{
    thePortController->onComputingDone();
}

void PortData::onError(int error)
{
    thePortController->onError(error);
}

void PortData::onDrawingDone()
{
    thePortController->onDrawingDone();
}

void PortData::onNewCode(QString code)
{
    thePortUI->onNewCode(code);
}

void PortData::onNewFileNAme(QString filename)
{
    thePortUI->onNewFileNAme(filename);
}

void PortData::onNewGates(QVector<Gate> gates)
{
    thePortUI->onNewGates(gates);
}

void PortData::onNewResults(QString results)
{
    thePortUI->onNewResults(results);
}
