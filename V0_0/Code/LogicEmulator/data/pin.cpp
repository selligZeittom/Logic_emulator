#include "pin.h"

Pin::Pin()
{

}

Pin::Pin(bool state)
{
    this->state = state;
    this->labelConnectedPin = "LOGICAL_SIGNAL";
    this->labelPin = "CREATED_PIN";
}

Pin::Pin(QString lab, QString con)
{
    this->connectedPin = NULL;
    this->labelPin = lab;
    this->labelConnectedPin = con;
    this->setState(false);
}

Pin::~Pin()
{
}

void Pin::initRelations(Pin *connected)
{
    this->connectedPin = connected;

    //two connected pins share the same state
    //this->setState(connectedPin->getState());
}

void Pin::setState(bool state)
{
    this->state = state;
}

bool Pin::getState() const
{
    return state;
}

QString Pin::getLabelConnectedPin() const
{
    return this->labelConnectedPin;
}

QString Pin::getLabelPin() const
{
    return this->labelPin;
}
