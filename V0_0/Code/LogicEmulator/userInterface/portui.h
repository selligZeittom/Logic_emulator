#ifndef PORTUI_H
#define PORTUI_H

#include <iostream>

#include "outputview.h"
#include "controller/portcontroller.h"
#include "interfaces/iviewupdate.h"
#include "interfaces/idataupdate.h"

class PortUI : public IViewUpdate, public IDataUpdate
{
public:
    PortUI();
    virtual ~PortUI();
    void initRelations(PortController* p1, OutputView* p2);

    // IDataUpdate interface, provided
public:
    virtual void onDataChanged();

    // IViewUpdate interface, required
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onPathSelected();

private:
    OutputView* outputView;
    PortController* thePortController;

};

#endif // PORTUI_H
