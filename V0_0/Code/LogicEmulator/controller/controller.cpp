#include "controller.h"
#include "portcontroller.h"

Controller::Controller()
{
    this->thePortController = NULL;
    this->state = ST_WAIT;
}

Controller::~Controller()
{
}

void Controller::initRelations(PortController *p1)
{
    this->thePortController = p1;
}

void Controller::evLoadButtonPressed(QString path)
{
    thePortController->setPath(path);
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_LOAD_CLICKED);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

void Controller::evLoadingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_LOADING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

void Controller::evConvertingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_CONVERTING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

void Controller::evComputingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_COMPUTING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

void Controller::evError(int error)
{
    XFEventError* ev = new XFEventError();
    ev->setID((int) EV_ERROR);
    ev->setTarget(this);
    ev->setErrorCode(error);
    XF::getInstance().pushEvent(ev);
}

void Controller::evDrawingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_DRAWING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

//state machine : double switch pattern
bool Controller::processEvent(XFEvent *p1)
{
    /*
     * double switch pattern for state machine
     */
    XFEventError* p2 = (XFEventError*) p1;

    bool processed = false;

    //Store the old state
    LE_STATE oldState = state;

    //switch the state : on transition
    switch (state) {

    case ST_WAIT :
        if(p2->getID() == EV_LOAD_CLICKED)
        {
            state = ST_LOAD;
            qDebug() << "-> ST_LOAD";
        }
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_WAIT;
            qDebug() << "error -> ST_WAIT";
        }
        break;
    case ST_LOAD :
        if(p2->getID() == EV_END_LOADING)
        {
            state = ST_CONVERT;
            qDebug() << "-> ST_CONVERT";
        }
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_WAIT;
            qDebug() << "error -> ST_WAIT";
        }
        break;

    case ST_CONVERT :
        if(p2->getID() == EV_END_CONVERTING)
        {
            state = ST_COMPUTE;
            qDebug() << "-> ST_COMPUTE";
        }
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_WAIT;
            qDebug() << "error -> ST_WAIT";
        }
        break;
    case ST_COMPUTE :
        if(p2->getID() == EV_END_COMPUTING)
        {
            state = ST_DRAW;
            qDebug() << "-> ST_DRAW";
        }
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_WAIT;
            qDebug() << "error -> ST_WAIT";
        }
        break;
    case ST_DRAW :
        if(p2->getID() == EV_END_DRAWING)
        {
            state = ST_WAIT;
            qDebug() << "-> ST_WAIT";
        }
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_WAIT;
            qDebug() << "error -> ST_WAIT";
        }
        break;
    default:
        break;
    }

    if(oldState!=state)
    {
        processed = true;

        //do action on exit
        switch (oldState) {
        case ST_WAIT :
            break;
        case ST_LOAD :
            break;
        case ST_CONVERT :
            break;
        case ST_COMPUTE :
            break;
        case ST_DRAW :
            break;
        default:
            break;
        }

        //do action on entry
        switch (state) {
        case ST_WAIT :
            qDebug() << "ST_WAIT : onEntry";
            break;
        case ST_LOAD :
            qDebug() << "ST_LOAD : onEntry";
            thePortController->loadFile();
            break;
        case ST_CONVERT :
            qDebug() << "ST_CONVERT : onEntry";
            thePortController->convertJsonToGates();
            break;
        case ST_COMPUTE :
            qDebug() << "ST_COMPUTE : onEntry";
            thePortController->computeLogic();
            break;
        case ST_DRAW :
            qDebug() << "ST_DRAW : onEntry";
            thePortController->drawGates();
            break;
        default:
            break;
        }
    }
    return processed;
}
