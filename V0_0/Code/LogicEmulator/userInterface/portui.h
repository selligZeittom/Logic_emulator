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

    // IViewUpdate interface, required
public:
    virtual void onButtonLoadPressed(QString path);

    // IDataUpdate interface, provided
public:
    virtual void onNewCode(QString code);
    virtual void onNewFileNAme(QString filename);
    virtual void onNewGates(QVector<Gate> gates);
    virtual void onNewResults(QString results);

private:
    OutputView* outputView;
    PortController* thePortController;


};

#endif // PORTUI_H
