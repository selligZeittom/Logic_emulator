#ifndef PORTCONTROLLER_H
#define PORTCONTROLLER_H

#include <iostream>
#include "interfaces/icontroller.h"
#include "interfaces/iviewupdate.h"
#include "XF/xf.h"
#include "XF/xfevent.h"

class Controller;
class PortData;

class PortController : public IController, public IViewUpdate
{
public:
    PortController();
    virtual ~PortController();
    void initRelations(Controller* p1, PortData* p2);

    // IController interface, required
public:
    virtual void loadFile();
    virtual void convertJsonToGates();
    virtual void computeLogic();
    virtual void drawGates();
    virtual void setPath(QString path);

    // IViewUpdate interface, provided
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onPathSelected();

private:
    Controller* controller;
    PortData* thePortData;


};

#endif // PORTCONTROLLER_H
