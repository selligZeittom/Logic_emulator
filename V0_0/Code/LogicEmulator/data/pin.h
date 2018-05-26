#ifndef PIN_H
#define PIN_H

#include <iostream>
#include <QString>

class Pin
{
public:
    Pin();
    virtual ~Pin();
    void initRelations(Pin* connected);

    void setState(bool state);
    bool getState() const;

private:
    QString label;
    Pin* connectedPin;
    bool state;
};

#endif // PIN_H
