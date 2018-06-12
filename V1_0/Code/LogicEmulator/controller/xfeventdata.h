#ifndef XFEVENTERROR_H
#define XFEVENTERROR_H

#include <QString>
#include "XF/xfevent.h"


class XFEventData : public XFEvent
{
public:
    XFEventData();
    int getErrorCode() const;
    void setErrorCode(int code);
    void setData(QString data);
    QString getData() const;
    void setIsValid(bool isValid);
    bool getIsValid() const;
private:
    int errorCode;
    QString data;
    bool isValid;
};

#endif // XFEVENTERROR_H
