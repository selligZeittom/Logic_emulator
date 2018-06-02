#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QString>

class IControllerData
{
public:
    IControllerData();

    //implemented as required by thePortController, and provided by thePortData
    virtual void loadFile() = 0;
    virtual void convertJsonToGates() = 0;
    virtual void computeLogic() = 0;
    virtual void drawGates() = 0;
    virtual void setPath(QString path) = 0;

    //implemented as required by thePortData, and provided by thePortController
    virtual void onLoadingDone() = 0;
    virtual void onConvertingDone() = 0;
    virtual void onComputingDone() = 0;
    virtual void onError(int error) = 0;
    virtual void onDrawingDone() = 0;

};

#endif // ICONTROLLER_H