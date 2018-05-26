#include "pin.h"

Pin::Pin()
{
    this->connectedPin = NULL;
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
