#ifndef XFEVENTERROR_H
#define XFEVENTERROR_H

#include "XF/xfevent.h"


class XFEventError : public XFEvent
{
public:
    XFEventError();
    int getErrorCode() const;
    void setErrorCode(int code);
private:
    int errorCode;
};

#endif // XFEVENTERROR_H
