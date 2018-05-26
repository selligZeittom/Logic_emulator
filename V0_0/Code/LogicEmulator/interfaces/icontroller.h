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

};

#endif // ICONTROLLER_H
