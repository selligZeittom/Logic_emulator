#include "pin.h"

Pin::Pin()
{

}

Pin::~Pin()
{

}

void Pin::setState(bool state)
{
    this->state = state;
}

bool Pin::getState() const
{
    return state;
}
