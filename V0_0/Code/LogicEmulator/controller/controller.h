#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QString>
#include "XF/ism.h"

class PortController;

class Controller : public ISM
{
public:
    Controller();
    virtual ~Controller();
    void initRelations(PortController* thePortController);

    void evLoadButtonPressed(QString path);
    void evLoadingDone();
    void evConvertingDone();
    void evComputingDone();

    // ISM interface, provided
public:
    virtual bool processEvent(XFEvent *thePortController);

private:

    //states of the state machine
    enum LE_STATE{
        ST_WAIT, ST_LOAD, ST_CONVERT, ST_COMPUTE, ST_DRAW
    };

    //possibles events
    enum LE_EVENT{
        EV_LOAD_CLICKED, EV_END_LOADING, EV_END_CONVERTING, EV_END_COMPUTING, EV_END_DRAWING, EV_END_ERROR
    };

    PortController* thePortController;
    LE_STATE state;
};


#endif // CONTROLLER_H
