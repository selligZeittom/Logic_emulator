#include "factory.h"

#include "userInterface/inputview.h"
#include "userInterface/portui.h"
#include "controller/controller.h"
#include "controller/portcontroller.h"
#include "data/data.h"
#include "data/portdata.h"
#include "userInterface/outputview.h"
#include "userInterface/view.h"

Factory::Factory()
{
    this->inputView = NULL;
    this->thePortUI = NULL;
    this->thePortController = NULL;
    this->thePortData = NULL;
    this->data = NULL;
    this->controller = NULL;
    this->outputView = NULL;
    this->view = NULL;
}

Factory::~Factory()
{
   std::cout <<"destroyed" << std::endl;
}

void Factory::create()
{
    this->inputView = new InputView();
    this->thePortUI = new PortUI();
    this->thePortController = new PortController();
    this->thePortData = new PortData();
    this->data = new Data();
    this->controller = new Controller();
    this->outputView = new OutputView();
    this->view = new View();
}

void Factory::build()
{
    this->inputView->initRelations(view);
    this->thePortUI->initRelations(thePortController, outputView);
    this->thePortController->initRelations(controller, thePortData);
    this->thePortData->initRelations(data, thePortUI);
    this->data->initRelations(thePortData);
    this->controller->initRelations(thePortController);
    this->outputView->initRelations(view);
    this->view->initRelations(outputView, thePortUI);
}

void Factory::destroy()
{
    if(inputView)
    {
        delete inputView;
        inputView = NULL;
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

    if(outputView)
    {
        delete outputView;
        outputView = NULL;
    }
}
