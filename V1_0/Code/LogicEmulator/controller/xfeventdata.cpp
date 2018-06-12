#include "xfeventdata.h"

XFEventData::XFEventData()
{

}

int XFEventData::getErrorCode() const
{
    return this->errorCode;
}

void XFEventData::setErrorCode(int code)
{
    this->errorCode = code;
}

void XFEventData::setData(QString path)
{
    this->data = path;
}

QString XFEventData::getData() const
{
    return this->data;
}

void XFEventData::setIsValid(bool isValid)
{
    this->isValid = isValid;
}

bool XFEventData::getIsValid() const
{
    return this->isValid;
}
