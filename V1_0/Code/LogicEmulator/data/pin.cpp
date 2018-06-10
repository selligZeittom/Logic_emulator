#include "pin.h"

Pin::Pin()
{
}

Pin::Pin(bool state)
{
    this->state = state;
    this->labelConnectedPin = "LOGICAL_SIGNAL";
    this->labelPin = "CREATED_PIN";
    this->x = 0;
    this->y = 0;
}

Pin::Pin(QString lab, QString con)
{
    this->connectedPin = NULL;
    this->labelPin = lab;
    this->labelConnectedPin = con;
    this->setState(false);
    this->x = this->y = 0;
}

Pin::~Pin()
{
}

void Pin::initRelations(Pin *cPin)
{
    this->connectedPin = cPin;
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

Pin *Pin::getConnectedPin() const
{
    return this->connectedPin;
}

void Pin::setXY(int x, int y)
{
    this->x = x;
    this->y = y;
}

int Pin::getX() const
{
    return this->x;
}

int Pin::getY() const
{
    return this->y;
}
