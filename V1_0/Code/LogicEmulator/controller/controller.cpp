#include "controller.h"
#include "portcontroller.h"

Controller::Controller()
{
    this->thePortController = NULL;
    this->state = ST_WAIT; //first state
}

Controller::~Controller()
{
}

//do the global connections
void Controller::initRelations(PortController *p1)
{
    this->thePortController = p1;
}

//it is called when the user clicked on the load button
void Controller::evLoadButtonPressed(QString path)
{
    //special XFEvent : need to store and forward data
    XFEventData* ev = new XFEventData();
    ev->setID((int) EV_LOAD_CLICKED);
    ev->setTarget(this);
    ev->setData(path); //store the path
    XF::getInstance().pushEvent(ev);
}

//it is called when the user clicked on the update button
void Controller::evCheckButtonPressed(QString labelToChange, QString newState)
{
    //special XFEvent : need to store and forward data
    XFEventData* ev = new XFEventData();
    ev->setID((int) EV_UPDATE_BUTTON_PRESSED);
    ev->setTarget(this);
    ev->setData(labelToChange+";"+newState); //store the data to update
    XF::getInstance().pushEvent(ev);
}

//is called when the file has been loaded
void Controller::evLoadingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_LOADING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

//is called when the conversion from .json file to gates is done
void Controller::evConvertingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_CONVERTING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

//is called when all the gates and pins are connected, and the results computed
void Controller::evComputingDone()
{
    XFEventData* ev = new XFEventData();
    ev->setID((int) EV_END_COMPUTING);
    ev->setTarget(this);
    ev->setIsValid(true);
    XF::getInstance().pushEvent(ev);
}

//is called if an error has occured during the conversion process
void Controller::evError(int error)
{
    XFEventData* ev = new XFEventData();
    ev->setID((int) EV_ERROR);
    ev->setTarget(this);
    ev->setErrorCode(error);
    XF::getInstance().pushEvent(ev);
}

//is called when the drawing on the screen is done
void Controller::evDrawingDone()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_DRAWING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

//is called after an error has been treated and displayed on the ioview
void Controller::evErrorProcessed()
{
    XFEvent* ev = new XFEvent();
    ev->setID((int) EV_END_ERROR_PROCESSING);
    ev->setTarget(this);
    XF::getInstance().pushEvent(ev);
}

//it is called when the update data have been checked
void Controller::evCheckModificationsDone(bool isValid)
{
    XFEventData* ev = new XFEventData();
    ev->setID((int) EV_END_CHECKING);
    ev->setTarget(this);
    ev->setIsValid(isValid);
    XF::getInstance().pushEvent(ev);
}

//it is called after an update has been done in the logic
void Controller::evUpdateDone(bool isValid)
{
    XFEventData* ev = new XFEventData();
    ev->setID((int) EV_END_UPDATING);
    ev->setTarget(this);
    ev->setIsValid(isValid);
    XF::getInstance().pushEvent(ev);
}

//state machine : double switch pattern
bool Controller::processEvent(XFEvent *p1)
{

    //downcast the event to get the potential stored data
    XFEventData* p2 = (XFEventData*) p1;

    //if the event isn't processed in this state machine
    bool processed = false;

    //Store the old state
    LE_STATE oldState = state;

    //switch state : on transition
    switch (state) {

    case ST_WAIT :
        //standard loading procedure
        if(p2->getID() == EV_LOAD_CLICKED)
        {
            state = ST_LOAD;
        }

        //if the user did modifications on the code displayer on the screen
        else if(p2->getID() == EV_UPDATE_BUTTON_PRESSED)
        {
            state = ST_CHECK_MODIF;
        }
        break;

    case ST_LOAD :
        //loading was done finely
        if(p2->getID() == EV_END_LOADING)
        {
            state = ST_CONVERT;
        }
        //an error occured
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_ERROR;
        }
        break;

    case ST_CONVERT :
        //conversion was done properly
        if(p2->getID() == EV_END_CONVERTING)
        {
            state = ST_COMPUTE;
        }
        //an error occured
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_ERROR;
        }
        break;

    case ST_COMPUTE :
        //computation was done properly
        if(p2->getID() == EV_END_COMPUTING)
        {
            state = ST_DRAW;
        }
        //an error occured
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_ERROR;
        }
        break;

    case ST_DRAW :
        //drawing was done succesfully
        if(p2->getID() == EV_END_DRAWING)
        {
            state = ST_WAIT;
            qDebug() << "-> ST_WAIT";
        }
        //an error occured
        else if(p2->getID() == EV_ERROR)
        {
            state = ST_ERROR;
        }
        break;

    case ST_ERROR :
        //error has been managed
        if(p2->getID() == EV_END_ERROR_PROCESSING)
        {
            state = ST_WAIT;
        }
        break;

    case ST_CHECK_MODIF :
        //modifications were checked
        if(p2->getID() == EV_END_CHECKING)
        {
            state = ST_UPDATE_GATES_PINS;
        }
        break;

    case ST_UPDATE_GATES_PINS :
        //logic updated -> drawing time again
        if(p2->getID() == EV_END_UPDATING)
        {
            state = ST_DRAW;
        }
        break;
    default:
        break;
    }

    if(oldState!=state)
    {
        processed = true;

        //probably not used, but must be declared here...
        QString errorLabel;

        //do action on entry
        switch (state) {
        case ST_WAIT :
            break;

        case ST_LOAD :
            //start the loading of the selected file
            thePortController->loadFile(p2->getData());
            break;

        case ST_CONVERT :
            //start the conversion of the file
            thePortController->convertJsonToGates();
            break;

        case ST_COMPUTE :
            //set all the gates and pins
            thePortController->computeLogic();
            break;

        case ST_DRAW :
            //Draw the result on the screen
            thePortController->drawGates(p2->getIsValid());
            break;

        case ST_ERROR :
            //get the string to represent the error
            switch (p2->getErrorCode()) {
            case ERROR_LOADING_FILE:
                errorLabel = "error : failed to load file...";
                break;
            case ERROR_JSON_LOADING:
                errorLabel = "error : failed to convert the global .json file...";
                break;
            case ERROR_JSON_CONVERSION:
                errorLabel = "error : failed to convert into an object the .json file...";
                break;
            case ERROR_JSON_CONVERSION_ARRAY:
                errorLabel = "error : failed to create an array in the .json file";
                break;
            case ERROR_JSON_CONVERSION_GATE:
                errorLabel = "error : failed to create a gate...";
                break;
            case ERROR_JSON_CONVERSION_PIN:
                errorLabel = "error : failed to create a pin...";
                break;
            case ERROR_JSON_CONVERSION_ID:
                errorLabel = "error : a gate's ID is missing or wrong declared";
                break;
            case ERROR_JSON_CONVERSION_LABEL:
                errorLabel = "error : a pin's label is missing or wrong declared...";
                break;
            case ERROR_JSON_CONVERSION_CONNECTED:
                errorLabel = "error : a pin's connectedLabel is missing or wrong declared...";
                break;
            case ERROR_READING_FILE:
                errorLabel = "error : can't read the file...";
                break;
            case ERROR_LABEL_PIN_NOT_VALID:
                errorLabel = "error : there is a mistake in a label or connectedLabel -> pin doesn't exist...";
                break;
            default:
                errorLabel="error : unvalid error code...";
                break;
            }
            //forward the error and display it on the screen
            thePortController->manageError(errorLabel);
            break;
        case ST_CHECK_MODIF:
            //check the validity of the modifications
            thePortController->checkValidity(p2->getData());
            break;
        case ST_UPDATE_GATES_PINS:
            //updates logic
            thePortController->updateGatesAndPins(p2->getIsValid());
            break;
        default:
            break;
        }
    }
    return processed;
}
