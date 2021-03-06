#ifndef PORTUI_H
#define PORTUI_H

#include <iostream>

#include "controller/portcontroller.h"
#include "interfaces/iviewupdate.h"
#include "interfaces/idataupdate.h"

class IOView;

class PortUI : public IViewUpdate, public IDataUpdate
{
public:
    PortUI();
    virtual ~PortUI();
    void initRelations(PortController* p1, IOView* p2);

    // IViewUpdate interface, required
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onButtonUpdatePressed(QString labelToChange, QString newState);

    // IDataUpdate interface, provided
public:
    virtual void onNewCode(QString code);
    virtual void onNewFileNAme(QString filename);
    virtual void onNewGates(QVector<Gate*> &gates, int maxLevel);
    virtual void onNewResults(QString results);
    virtual void onNewListConnectedLabels(QStringList listConnectedLabel);
    virtual void onNewStatusModifications(QString status);
    virtual void onDeleteOldGatesAndCode();

private:
    IOView* ioView;
    PortController* thePortController;

};

#endif // PORTUI_H
