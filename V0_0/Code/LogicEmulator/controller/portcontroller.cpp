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
thePortData->computeLogic();
}

void PortController::drawGates()
{
thePortData->drawGates();
}

void PortController::setPath(QString path)
{
    thePortData->setPath(path);
}

void PortController::manageError(QString labelError)
{
    thePortData->manageError(labelError);
}

void PortController::onButtonLoadPressed(QString path)
{
    controller->evLoadButtonPressed(path);
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

void PortController::onError(int error)
{
    controller->evError(error);
}

void PortController::onDrawingDone()
{
    controller->evDrawingDone();
}

void PortController::onProcessErrorDone()
{
    controller->evErrorProcessed();
}
