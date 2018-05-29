#ifndef FACTORY_H
#define FACTORY_H

#include <iostream>
#include <QWidget>


class InputView;
class PortUI;
class PortController;
class PortData;
class Data;
class Controller;
class OutputView;
class View;

class Factory
{
public:
    Factory();
    virtual ~Factory();

    void create();
    void build();
    void destroy();

    QWidget* getView() const;

private:
    InputView* inputView;
    PortUI* thePortUI;
    PortController* thePortController;
    PortData* thePortData;
    Data* data;
    Controller* controller;
    OutputView* outputView;
    View* view;
};

#endif // FACTORY_H
