#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <QString>
#include <QDebug>

#include "XF/ism.h"
#include "xfeventdata.h"

#define ERROR_LOADING_FILE 0
#define ERROR_JSON_LOADING 1
#define ERROR_JSON_CONVERSION 2
#define ERROR_JSON_CONVERSION_ARRAY 3
#define ERROR_JSON_CONVERSION_GATE 4
#define ERROR_JSON_CONVERSION_PIN 5
#define ERROR_JSON_CONVERSION_ID 7
#define ERROR_JSON_CONVERSION_LABEL 9
#define ERROR_JSON_CONVERSION_CONNECTED 10
#define ERROR_READING_FILE 11
#define ERROR_LABEL_PIN_NOT_VALID 12

class PortController;

class Controller : public ISM
{
public:
    Controller();
    virtual ~Controller();
    void initRelations(PortController* thePortController);

    //path : the path of the selected file by the user
    void evLoadButtonPressed(QString path);

    /*
     * labelToChange : the pin's label to update its input
     * newState : HIGH or LOW
     */
    void evCheckButtonPressed(QString labelToChange, QString newState);
    void evLoadingDone();
    void evConvertingDone();
    void evComputingDone();

    //error : the error code to display the right message on the screen
    void evError(int error);
    void evDrawingDone();
    void evErrorProcessed();

    //isValid : true is user selected a label, false otherwise
    void evCheckModificationsDone(bool isValid);
    void evUpdateDone(bool isValid);

    // ISM interface, provided
public:
    virtual bool processEvent(XFEvent *thePortController);

private:
    //states of the state machine
    enum LE_STATE{
        ST_WAIT, ST_LOAD, ST_CONVERT, ST_COMPUTE, ST_DRAW, ST_ERROR, ST_CHECK_MODIF, ST_UPDATE_GATES_PINS
    };

    //possibles events
    enum LE_EVENT{
        EV_LOAD_CLICKED, EV_END_LOADING, EV_END_CONVERTING, EV_END_COMPUTING,
        EV_END_DRAWING, EV_ERROR, EV_END_ERROR_PROCESSING, EV_UPDATE_BUTTON_PRESSED,
        EV_END_CHECKING, EV_END_UPDATING
    };

    PortController* thePortController;
    LE_STATE state;
};


#endif // CONTROLLER_H
