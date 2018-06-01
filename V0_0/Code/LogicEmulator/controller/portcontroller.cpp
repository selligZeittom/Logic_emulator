#include "portcontroller.h"
#include "controller.h"
#include "data/portdata.h"


PortController::PortController()
{
    this->thePortData = NULL;
    this->controller = NULL;
}

PortController::~PortController()
{
}

void PortController::initRelations(Controller *p1, PortData *p2)
{
    this->controller = p1;
    this->thePortData = p2;
}

void PortController::loadFile()
{
    thePortData->loadFile();
}

void PortController::convertJsonToGates()
{
    thePortData->convertJsonToGates();
}

void PortController::computeLogic()
{

}

void PortController::drawGates()
{

}

void PortController::setPath(QString path)
{
    thePortData->setPath(path);
}

void PortController::onButtonLoadPressed(QString path)
{
    controller->evLoadButtonPressed(path);
}

void PortController::onPathSelected()
{

}

void PortController::onLoadingDone()
{
    controller->evLoadingDone();
}

void PortController::onConvertingDone()
{
    controller->evConvertingDone();
}

void PortController::onComputingDone()
{
    controller->evComputingDone();
}
