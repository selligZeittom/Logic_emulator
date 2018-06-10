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
    void setPath(QString path);
    QString getPath() const;
private:
    int errorCode;
    QString path;
};

#endif // XFEVENTERROR_H
