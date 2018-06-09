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

void XFEventData::setPath(QString path)
{
    this->path = path;
}

QString XFEventData::getPath() const
{
    return this->path;
}
