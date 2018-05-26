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

}

void PortController::computeLogic()
{

}

void PortController::drawGates()
{

}

void PortController::onButtonLoadPressed(QString path)
{
    controller->evLoadButtonPressed(path);
}

void PortController::onPathSelected()
{

}
