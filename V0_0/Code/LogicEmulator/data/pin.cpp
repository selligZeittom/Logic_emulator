#include "pin.h"

Pin::Pin(QString lab  = "NO_LABEL", QString con = "NO_CONNECTED")
{
    this->connectedPin = NULL;
    this->label = lab;
    this->connected = con;
}

Pin::~Pin()
{
    if(connectedPin)
    {
        delete connectedPin;
        connectedPin = NULL;
    }
}

void Pin::initRelations(Pin *connected)
{
    this->connectedPin = connected;
}

void Pin::setState(bool state)
{
    this->state = state;
}

bool Pin::getState() const
{
    return state;
}
