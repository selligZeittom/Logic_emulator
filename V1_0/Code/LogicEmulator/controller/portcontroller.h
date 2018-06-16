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

class PortController :  public IViewUpdate , public IControllerData
{
public:
    PortController();
    virtual ~PortController();
    void initRelations(Controller* p1, PortData* p2);

public:
    // IController interface, required to PortData
    virtual void loadFile(QString path);
    virtual void convertJsonToGates();
    virtual void computeLogic();
    virtual void drawGates(bool isValid);
    virtual void manageError(QString labelError);
    virtual void checkValidity(QString newCode);
    virtual void updateGatesAndPins(bool isValid);

    // IController interface, provided from PortData
    virtual void onLoadingDone();
    virtual void onConvertingDone();
    virtual void onComputingDone();
    virtual void onError(int error);
    virtual void onDrawingDone();
    virtual void onErrorProcessed();
    virtual void onCheckingModificationsDone(bool isValid);
    virtual void onUpdateDone(bool isValid);

    // IViewUpdate interface, provided from PortUI
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onButtonUpdatePressed(QString labelToChange, QString newState);

private:
    Controller* controller;
    PortData* thePortData;

};

#endif // PORTCONTROLLER_H
