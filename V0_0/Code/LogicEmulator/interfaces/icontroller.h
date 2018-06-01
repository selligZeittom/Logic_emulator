#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <QString>

class IController
{
public:
    IController();
    virtual void loadFile() = 0;
    virtual void convertJsonToGates() = 0;
    virtual void computeLogic() = 0;
    virtual void drawGates() = 0;
    virtual void setPath(QString path) = 0;


    virtual void onLoadingDone() = 0;
    virtual void onConvertingDone() = 0;
    virtual void onComputingDone() = 0;

};

#endif // ICONTROLLER_H
