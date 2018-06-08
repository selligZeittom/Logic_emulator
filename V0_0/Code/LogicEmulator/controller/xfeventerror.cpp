#include "xfeventerror.h"

XFEventError::XFEventError()
{

}

int XFEventError::getErrorCode() const
{
    return this->errorCode;
}

void XFEventError::setErrorCode(int code)
{
    this->errorCode = code;
}
