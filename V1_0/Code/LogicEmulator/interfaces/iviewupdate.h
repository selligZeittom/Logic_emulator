#ifndef IVIEWUPDATE_H
#define IVIEWUPDATE_H

#include <QString>

class IViewUpdate
{
public:
    IViewUpdate();
    virtual void onButtonLoadPressed(QString path) = 0;
    virtual void onButtonUpdatePressed(QString labelToChange, QString newState) = 0;
};

#endif // IVIEWUPDATE_H
