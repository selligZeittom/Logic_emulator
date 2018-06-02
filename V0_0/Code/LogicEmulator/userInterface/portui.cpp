#include "portui.h"
#include "ioview.h"

PortUI::PortUI()
{
    this->thePortController = NULL;
    this->ioView = NULL;
}

PortUI::~PortUI()
{
}

void PortUI::initRelations(PortController *p1, IOView *p2)
{
    this->thePortController = p1;
    this->ioView = p2;
}

void PortUI::onButtonLoadPressed(QString path)
{
    thePortController->onButtonLoadPressed(path);
}

void PortUI::onNewCode(QString code)
{
    ioView->onNewCode(code);
}

void PortUI::onNewFileNAme(QString filename)
{
    ioView->onNewFileName(filename);
}

void PortUI::onNewGates(QVector<Gate> gates)
{
    ioView->draw(gates);
}

void PortUI::onNewResults(QString results)
{
    ioView->onNewResults(results);
}
