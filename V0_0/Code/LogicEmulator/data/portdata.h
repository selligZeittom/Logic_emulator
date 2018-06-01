#ifndef PORTDATA_H
#define PORTDATA_H

#include "userInterface/portui.h"
#include "interfaces/icontroller.h"
#include "interfaces/idataupdate.h"

class Data;
class PortController;

class PortData : public IController, public IDataUpdate
{
public:
    PortData();
    virtual ~PortData();
    void initRelations(Data* p1, PortUI* p2, PortController *p3);

private:
    Data* data;
    PortUI* thePortUI;
    PortController* thePortController;

    // IController interface, provided
public:
    //implemented as provided
    virtual void loadFile();
    virtual void convertJsonToGates();
    virtual void computeLogic();
    virtual void drawGates();
    virtual void setPath(QString path);

    //implemented as required
    virtual void onLoadingDone();
    virtual void onConvertingDone();
    virtual void onComputingDone();

    // IUpdate interface, required
public:
    virtual void onDataChanged();


};

#endif // PORTDATA_H
