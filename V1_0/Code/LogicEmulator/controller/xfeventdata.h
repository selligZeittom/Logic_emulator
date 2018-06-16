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
    //store the error code in the event
    int errorCode;
    //Store the data to update
    QString data;
    //store if the update is valid or not
    bool isValid;
};

#endif // XFEVENTERROR_H
