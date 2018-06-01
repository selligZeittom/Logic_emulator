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

void PortUI::onButtonLoadPressed(QString path)
{
    thePortController->onButtonLoadPressed(path);
}

void PortUI::onNewCode(QString code)
{
        outputView->onNewCode(code);
}

void PortUI::onNewFileNAme(QString filename)
{
    outputView->onNewFileName(filename);
}

void PortUI::onNewGates(QVector<Gate> gates)
{
    outputView->draw(gates);
}

void PortUI::onNewResults(QString results)
{
    outputView->onNewResults(results);
}
