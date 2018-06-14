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
    //make the global connections between packages
    this->controller = p1;
    this->thePortData = p2;
}

void PortController::loadFile(QString path)
{
    thePortData->loadFile(path);
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

void PortController::manageError(QString labelError)
{
    thePortData->manageError(labelError);
}

void PortController::checkValidity(QString newCode)
{
    thePortData->checkValidity(newCode);
}

void PortController::updateGatesAndPins()
{
    thePortData->updateGatesAndPins();
}

void PortController::onButtonLoadPressed(QString path)
{
    controller->evLoadButtonPressed(path);
}

void PortController::onButtonUpdatePressed(QString labelToChange, QString newState)
{
    controller->evCheckButtonPressed(labelToChange, newState);
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

void PortController::onErrorProcessed()
{
    controller->evErrorProcessed();
}

void PortController::onCheckingModificationsDone(bool isValid)
{
    controller->evCheckModificationsDone(isValid);
}

void PortController::onUpdateDone()
{
    controller->evUpdateDone();
}
