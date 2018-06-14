#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QString>

class IControllerData
{
public:
    IControllerData();

    //implemented as required by thePortController, and provided by thePortData
    virtual void loadFile(QString path) = 0;
    virtual void convertJsonToGates() = 0;
    virtual void computeLogic() = 0;
    virtual void drawGates(bool isValid) = 0;
    virtual void manageError(QString labelError) = 0;
    virtual void checkValidity(QString newCode) = 0;
    virtual void updateGatesAndPins(bool isValid) = 0;

    //implemented as required by thePortData, and provided by thePortController
    virtual void onLoadingDone() = 0;
    virtual void onConvertingDone() = 0;
    virtual void onComputingDone() = 0;
    virtual void onError(int error) = 0;
    virtual void onDrawingDone() = 0;
    virtual void onErrorProcessed() = 0;
    virtual void onCheckingModificationsDone(bool isValid) = 0;
    virtual void onUpdateDone(bool isValid) = 0;

};

#endif // ICONTROLLER_H
