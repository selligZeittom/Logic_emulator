#ifndef PIN_H
#define PIN_H

#include <iostream>
#include <QString>

class Pin
{
public:
    Pin();
    Pin(bool state);
    Pin(QString lab, QString con);
    virtual ~Pin();
    void initRelations(Pin* connected);

    void setState(bool state);
    bool getState() const;
    QString getLabel() const;

private:
    QString label;
    QString connected;
    Pin* connectedPin;
    bool state;
};

#endif // PIN_H
