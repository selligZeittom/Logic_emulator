#ifndef PORTDATA_H
#define PORTDATA_H

#include <QString>
#include "userInterface/portui.h"
#include "interfaces/icontrollerdata.h"
#include "interfaces/idataupdate.h"

class Data;
class PortController;

class PortData : public IControllerData, public IDataUpdate
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
    virtual void loadFile(QString path);
    virtual void convertJsonToGates();
    virtual void computeLogic();
    virtual void drawGates();
    virtual void manageError(QString labelError);

    //implemented as required
    virtual void onLoadingDone();
    virtual void onConvertingDone();
    virtual void onComputingDone();
    virtual void onError(int error);
    virtual void onDrawingDone();
    virtual void onErrorProcessed();

    // IDataUpdate interface, required
public:
    virtual void onNewCode(QString code);
    virtual void onNewFileNAme(QString filename);
    virtual void onNewGates(QVector<Gate *> &gates, int maxLevel);
    virtual void onNewResults(QString results);
    virtual void onDeleteOldGatesAndCode();
};

#endif // PORTDATA_H
