#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QString>
#include <QDebug>

#include "XF/ism.h"
#include "xfeventdata.h"
#include "globalvariables.h"


class PortController;

class Controller : public ISM
{
public:
    Controller();
    virtual ~Controller();
    void initRelations(PortController* thePortController);

    void evLoadButtonPressed(QString path);
    void evCheckButtonPressed(QString newCode);
    void evLoadingDone();
    void evConvertingDone();
    void evComputingDone();
    void evError(int error);
    void evDrawingDone();
    void evErrorProcessed();
    void evCheckModificationsDone(bool isValid);

    // ISM interface, provided
public:
    virtual bool processEvent(XFEvent *thePortController);

private:

    //states of the state machine
    enum LE_STATE{
        ST_WAIT, ST_LOAD, ST_CONVERT, ST_COMPUTE, ST_DRAW, ST_ERROR, ST_CHECK_MODIF, ST_UPDATE_GATES_PINS
    };

    //possibles events
    enum LE_EVENT{
        EV_LOAD_CLICKED, EV_END_LOADING, EV_END_CONVERTING, EV_END_COMPUTING,
        EV_END_DRAWING, EV_ERROR, EV_END_ERROR_PROCESSING, EV_MODIFICATION_BUTTON_PRESSED,
        EV_END_CHECKING, EV_END_UPDATING
    };

    PortController* thePortController;
    LE_STATE state;
};


#endif // CONTROLLER_H
