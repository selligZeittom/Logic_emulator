#ifndef IVIEWUPDATE_H
#define IVIEWUPDATE_H

#include <QString>

class IViewUpdate
{
public:
    IViewUpdate();
    virtual void onButtonLoadPressed(QString path) = 0;
    virtual void onPathSelected() = 0;
};

#endif // IVIEWUPDATE_H
