#include "factory.h"
#include "userInterface/portui.h"
#include "controller/controller.h"
#include "controller/portcontroller.h"
#include "data/data.h"
#include "data/portdata.h"
#include "userInterface/ioview.h"

Factory::Factory()
{
    XF::getInstance();

    this->thePortUI = NULL;
    this->thePortController = NULL;
    this->thePortData = NULL;
    this->data = NULL;
    this->controller = NULL;
    this->ioView = NULL;
}

Factory::~Factory()
{
}

void Factory::create()
{
    this->thePortUI = new PortUI();
    this->thePortController = new PortController();
    this->thePortData = new PortData();
    this->data = new Data();
    this->controller = new Controller();
    this->ioView = new IOView();
}

void Factory::build()
{
    this->ioView->initRelations(thePortUI);
    this->thePortUI->initRelations(thePortController, ioView);
    this->thePortController->initRelations(controller, thePortData);
    this->thePortData->initRelations(data, thePortUI, thePortController);
    this->data->initRelations(thePortData);
    this->controller->initRelations(thePortController);
}

void Factory::destroy()
{
    if(ioView)
    {
        delete ioView;
        ioView = NULL;
    }

    if(thePortUI)
    {
        delete thePortUI;
        thePortUI = NULL;
    }

    if(thePortController)
    {
        delete thePortController;
        thePortController = NULL;
    }

    if(thePortData)
    {
        delete thePortData;
        thePortData = NULL;
    }

    if(data)
    {
        delete data;
        data = NULL;
    }

    if(controller)
    {
        delete controller;
        controller = NULL;
    }
    qDebug() <<"destroyed()";
}

