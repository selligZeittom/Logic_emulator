#ifndef PORTCONTROLLER_H
#define PORTCONTROLLER_H

#include <iostream>
#include <QString>
#include "interfaces/icontrollerdata.h"
#include "interfaces/iviewupdate.h"
#include "XF/xf.h"
#include "XF/xfevent.h"

class Controller;
class PortData;

class PortController : public IControllerData, public IViewUpdate
{
public:
    PortController();
    virtual ~PortController();
    void initRelations(Controller* p1, PortData* p2);

public:
    // IController interface
    //implemented as required
    virtual void loadFile(QString path);
    virtual void convertJsonToGates();
    virtual void computeLogic();
    virtual void drawGates();
    virtual void manageError(QString labelError);
    virtual void checkValidity(QString newCode);
    virtual void updateGatesAndPins();

    //implemented as provided
    virtual void onLoadingDone();
    virtual void onConvertingDone();
    virtual void onComputingDone();
    virtual void onError(int error);
    virtual void onDrawingDone();
    virtual void onErrorProcessed();
    virtual void onCheckingModificationsDone(bool isValid);
    virtual void onUpdateDone();

    // IViewUpdate interface, provided
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onButtonCheckPressed(QString newCode);

private:
    Controller* controller;
    PortData* thePortData;

};

#endif // PORTCONTROLLER_H
