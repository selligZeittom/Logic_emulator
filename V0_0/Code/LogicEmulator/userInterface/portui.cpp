#include "portui.h"

PortUI::PortUI()
{
    this->thePortController = NULL;
    this->outputView = NULL;
}

PortUI::~PortUI()
{
}

void PortUI::initRelations(PortController *p1, OutputView *p2)
{
    this->thePortController = p1;
    this->outputView = p2;
}

void PortUI::onDataChanged()
{

}

void PortUI::onButtonLoadPressed(QString path)
{
    thePortController->onButtonLoadPressed(path);
}

void PortUI::onPathSelected()
{

}
