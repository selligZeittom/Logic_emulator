#include "pin.h"

Pin::Pin()
{

}

Pin::Pin(bool state)
{
    this->state = state;
    this->connected = "LOGICAL_SIGNAL";
    this->label = "CREATED_PIN";
}

Pin::Pin(QString lab, QString con)
{
    this->connectedPin = NULL;
    this->label = lab;
    this->connected = con;
    this->setState(false);

    /*
     * set the state if the pin is an input pin connected to a constant and
     * not to the output of another gate
    */
    if(connected.contains("LOW"))
    {
        this->connectedPin = new Pin(false);
        this->setState(connectedPin->getState());
    }
    else if(connected.contains("HIGH"))
    {
        this->connectedPin = new Pin(true);
        this->setState(connectedPin->getState());
    }
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
    return this->label;
}
