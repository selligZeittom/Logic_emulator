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

//state machine : double switch pattern
bool Controller::processEvent(XFEvent *p1)
{
    /*
         * double switch pattern for state machine
         */

    bool processed = false;

    //Store the old state
    LE_STATE oldState = state;

    //switch the state : on transition
    switch (state) {

    case ST_WAIT :
        if(p1->getID() == EV_LOAD_CLICKED)
        {
            state = ST_LOAD;
            std::cout << "init done -> ST_OFF" << std::endl;
        }
        break;
    case ST_LOAD :
        if(p1->getID() == EV_END_LOADING)
        {
            state = ST_CONVERT;
            std::cout << "ST_ON" << std::endl;
        }
        break;

    case ST_CONVERT :
        if(p1->getID() == EV_END_CONVERTING)
        {
            state = ST_COMPUTE;
            std::cout << "ST_OFF" << std::endl;
        }
        break;
    case ST_COMPUTE :
        if(p1->getID() == EV_END_COMPUTING)
        {
            state = ST_DRAW;
            std::cout << "ST_OFF" << std::endl;
        }
        break;
    case ST_DRAW :
        if(p1->getID() == EV_END_DRAWING)
        {
            state = ST_WAIT;
            std::cout << "ST_OFF" << std::endl;
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
            thePortController->loadFile();
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
    }
    return processed;
}
