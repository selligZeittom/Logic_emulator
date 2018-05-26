#ifndef PORTDATA_H
#define PORTDATA_H

#include "userInterface/portui.h"
#include "interfaces/icontroller.h"
#include "interfaces/idataupdate.h"

class Data;

class PortData : public IController, public IDataUpdate
{
public:
    PortData();
    virtual ~PortData();
    void initRelations(Data* p1, PortUI* p2);

private:
    Data* data;
    PortUI* thePortUI;

    // IController interface, provided
public:
    virtual void loadFile();
    virtual void convertJsonToGates();
    virtual void computeLogic();
    virtual void drawGates();
    virtual void setPath(QString path);

    // IUpdate interface, required
public:
    virtual void onDataChanged();


};

#endif // PORTDATA_H
