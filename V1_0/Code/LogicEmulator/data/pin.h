#ifndef PIN_H
#define PIN_H

#include <iostream>
#include <QString>
#include <QDebug>


class Pin
{
public:
    Pin();
    Pin(bool state);
    Pin(QString lab, QString con);
    virtual ~Pin();
    void initRelations(Pin* cPin);

    void setState(bool state);
    bool getState() const;
    QString getLabelConnectedPin() const;
    QString getLabelPin() const;
    Pin* getConnectedPin() const;
    void setXY(int x, int y);
    int getX() const;
    int getY() const;

private:
    QString labelPin; //identifies this pin
    QString labelConnectedPin; //identifies the others pin
    Pin* connectedPin;
    bool state;
    int x, y;
};

#endif // PIN_H
