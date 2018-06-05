#ifndef IUPDATE_H
#define IUPDATE_H

#include <QString>
#include <data/gate.h>

class IDataUpdate
{
public:
    IDataUpdate();
    virtual void onNewCode(QString code) = 0;
    virtual void onNewFileNAme(QString filename) = 0;
    virtual void onNewGates(QVector<Gate> gates, int maxLevel) = 0;
    virtual void onNewResults(QString results) = 0;
};

#endif // IUPDATE_H
