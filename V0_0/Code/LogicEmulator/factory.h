#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <QWidget>

class PortUI;
class PortController;
class PortData;
class Data;
class Controller;
class IOView;

class Factory
{
public:
    Factory();
    virtual ~Factory();

    void create();
    void build();
    void destroy();

private:
    PortUI* thePortUI;
    PortController* thePortController;
    PortData* thePortData;
    Data* data;
    Controller* controller;
    IOView* ioView;
};

#endif // FACTORY_H
