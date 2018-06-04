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

    /*
     * set the state if the pin is an input pin connected to a constant and
     * not to the output of another gate
    if(labelConnectedPin.contains("LOW"))
    {
        this->connectedPin = new Pin(false);
        this->setState(connectedPin->getState());
    }
    else if(labelConnectedPin.contains("HIGH"))
    {
        this->connectedPin = new Pin(true);
        this->setState(connectedPin->getState());
    }
    */
}

Pin::~Pin()
{
}

void Pin::initRelations(Pin *connected)
{
    this->connectedPin = connected;

    //two connected pins share the same state
    this->setState(connectedPin->getState());
}

void Pin::setState(bool state)
{
    this->state = state;
}

bool Pin::getState() const
{
    return state;
}

QString Pin::getLabel() const
{
    return this->labelPin;
}
