#include "data.h"
#include "portdata.h"
#include "globalvariables.h"


Data::Data()
{
    this->thePortData = NULL;
    this->file = NULL;
    levelMax = 0;
}

Data::~Data()
{
    //delete the pointer
    if(file)
    {
        delete file;
        file = NULL;
    }
}

void Data::initRelations(PortData *p1)
{
    this->thePortData = p1;
}

void Data::loadFile(QString path)
{
    //set the path
    this->path = path;

    //create the file
    file = new QFile(path);

    //open the file
    file->open(QIODevice::ReadOnly);

    //check that the file is valid : if not, send error
    if(!file->isOpen())
    {
        code="no code...";//no valid code to display
        thePortData->onError(ERROR_LOADING_FILE);
    }

    //if the file is valids
    thePortData->onLoadingDone();
}

void Data::convertJsonToGates()
{
    //first clear the variables
    vGates.clear();
    levelMax = 0;
    fileName = "";
    result = "";
    code = "";

    //get the string corresponding to the .json file
    QTextStream reader(file);
    code = reader.readAll();

    //check that the read operation was well done
    if(code.isEmpty())
    {
        //if not, send an error
        thePortData->onError(ERROR_READING_FILE);
    }

    //close file, don't need it anymore
    file->close();

    //translate the string into a byte array
    QByteArray byteData = code.toLocal8Bit();

    //the main document from the json file
    QJsonDocument doc = QJsonDocument::fromJson(byteData);

    //check that the conversion has been well done
    if(doc.isEmpty())
    {
        //if not, send an error
        thePortData->onError(ERROR_JSON_LOADING);
    }

    //convert it to a global object
    QJsonObject design = doc.object();
    if(design.isEmpty())
    {
        //if not, send an error
        thePortData->onError(ERROR_JSON_CONVERSION);
    }

    //get the name of the file
    fileName = design["name"].toString();

    //get the array of all the gates
    QJsonArray gates = design["gates"].toArray();

    //check that the array has sth inside
    if(gates.isEmpty())
    {
        //if not, send an error
        thePortData->onError(ERROR_JSON_CONVERSION_ARRAY);
    }

    //get all the gates of the design
    for(int i=0; i< gates.count(); ++i)
    {
        //get the characteristics of the gate
        QJsonObject gate = gates.at(i).toObject();
        if(gate.isEmpty())
        {
            thePortData->onError(ERROR_JSON_CONVERSION_GATE);
        }

        QString id = gate["ID"].toString();
        if(id.isEmpty())
        {
            thePortData->onError(ERROR_JSON_CONVERSION_ID);
        }

        int level = gate["level"].toInt();

        //get the array of the pins
        QJsonArray pins = gate["pins"].toArray();
        if(pins.isEmpty())
        {
            thePortData->onError(ERROR_JSON_CONVERSION_ARRAY);
        }

        //get all the input pins
        QVector<Pin*> vPinsIO;
        for(int j=0; j< pins.count(); ++j)
        {
            //create an object for each array element
            QJsonObject pin = pins.at(j).toObject();
            if(pin.isEmpty())
            {
                thePortData->onError(ERROR_JSON_CONVERSION_PIN);
            }

            QString label = pin["label"].toString();
            //add the label to the list of label if the level is 0 and it's an input pin
            if(level == 0 && !label.contains("U"))
            {
                labelsList.append(label);
            }

            if(label.isEmpty())
            {
                thePortData->onError(ERROR_JSON_CONVERSION_LABEL);
            }
            QString connectedLabel = pin["connectedLabel"].toString();


            if(connectedLabel.isEmpty())
            {
                thePortData->onError(ERROR_JSON_CONVERSION_LABEL);
            }

            //create a Pin object an add it to the end of the vector
            Pin* p = new Pin(label, connectedLabel);
            vPinsIO.push_back(p);//add to the gate's vector
        }




        //create a logic gate
        if(id.contains("AND"))
        {
            AndGate* andGate = new AndGate(id, level, vPinsIO);
            vGates.push_back(andGate); //add to the global vector
        }
        else if(id.contains("OR"))
        {
            OrGate* orGate = new OrGate(id, level, vPinsIO);
            vGates.push_back(orGate); //add to the global vector
        }
        else if(id.contains("NOT"))
        {
            NotGate* notGate = new NotGate(id, level, vPinsIO);
            vGates.push_back(notGate); //add to the global vector
        }
    }

    //if the conversion has been well done
    thePortData->onConvertingDone();
}

//get a string representing the output of all the gates
void Data::outputResultsToString()
{
    for (int i = 0; i < vGates.count(); ++i)
    {
        if(vGates[i]->getLevel() == levelMax)
        {
            this->result += "\r\n";
        }
        this->result += vGates[i]->outputToString();
        this->result += "\r\n";
    }

    thePortData->onComputingDone();
}

//send the informations to the ioview to display on the screen
void Data::drawResults(bool isValid)
{
    if(isValid)
    {
        thePortData->onNewFileNAme(fileName);
        thePortData->onNewCode(code);
        thePortData->onNewResults(result);
        thePortData->onNewGates(vGates, levelMax);
        thePortData->onNewListConnectedLabels(labelsList);
    }
    thePortData->onDrawingDone();
}

//return the pin with the label
Pin *Data::getPinFromLabel(QString labelPinToFind)
{
    Pin* retVal = NULL;
    for (int i = 0; i < vGates.count(); ++i)
    {
        //search for an output pin
        QString labelPin = vGates[i]->getOutputPin()->getLabelPin();
        if(labelPin == labelPinToFind)
        {
            return vGates[i]->getOutputPin();
        }

        //search for an input pin
        for(int j = 0; j < vGates[i]->getInputPins().count(); j++)
        {
            labelPin = vGates[i]->getInputPins()[j]->getLabelPin();
            if(labelPin == labelPinToFind)
            {
                return vGates[i]->getInputPins()[j];
            }
        }
    }
    //if we have to return a non existing pin ->> error !
    thePortData->onError(ERROR_LABEL_PIN_NOT_VALID);
    return retVal;
}

//set all the pins and gates, and therefor comput the logic
void Data::setGatesAndPins()
{
    //get the max level of the design
    levelMax = 0;
    for(int i = 0; i < vGates.count(); i++)
    {
        int levelGate = vGates[i]->getLevel();
        if(levelGate > levelMax)
        {
            this->levelMax = levelGate;
        }
    }

    //then compute level by level
    for(int currentLevel = 0; currentLevel <= levelMax; currentLevel++)
    {

        //look for all the gates in the vector if the level correspond to the currentLEvel
        for(int currentGate = 0; currentGate < vGates.count(); currentGate++)
        {
            int levelGate = vGates[currentGate]->getLevel();
            if(levelGate == currentLevel)
            {
                Gate* gate = vGates[currentGate];

                //for the first level there isn't a real connected pin
                if(levelGate == 0)
                {
                    for(int i = 0; i < gate->getInputPins().count(); i++)
                    {
                        if(gate->getInputPins()[i]->getLabelConnectedPin().contains("HIGH"))
                        {
                            gate->getInputPins()[i]->setState(true);
                        }
                        else if(gate->getInputPins()[i]->getLabelConnectedPin().contains("LOW"))
                        {
                            gate->getInputPins()[i]->setState(false);
                        }
                    }
                    Pin* outputPin = gate->getOutputPin();
                    outputPin->initRelations(getPinFromLabel(outputPin->getLabelConnectedPin()));
                    gate->updateLogic(levelMax);
                }

                //for the others level
                else
                {
                    //set the input pins
                    for(int i = 0; i < gate->getInputPins().count(); i++)
                    {
                        Pin* inputPin = gate->getInputPins()[i];
                        Pin* pinToConnect = getPinFromLabel(inputPin->getLabelConnectedPin());
                        inputPin->initRelations(pinToConnect);
                        inputPin->setState(pinToConnect->getState());
                    }
                    //for the not final level
                    if(levelGate < levelMax)
                    {
                        Pin* outputPin = gate->getOutputPin();
                        outputPin->initRelations(getPinFromLabel(outputPin->getLabelConnectedPin()));
                    }
                    gate->updateLogic(levelMax);
                }
            }
        }
    }
    outputResultsToString();
}

//send the error data to the ioview to display on the screen
void Data::processError(QString labelError)
{
    thePortData->onNewFileNAme(fileName);
    thePortData->onDeleteOldGatesAndCode();
    thePortData->onNewCode("!!! ERROR in the code !!!\r\n"+code);
    thePortData->onNewResults(labelError);
    thePortData->onErrorProcessed();
}

void Data::checkModifications(QString data)
{
    QStringList listTemp = data.split(";");
    qDebug()<<listTemp[0];
    qDebug()<<listTemp[1];

    //check that the label is corresponding to a gate's pin input
    if(labelsList.contains(listTemp[0]))
    {
        //check that the newState is correct
        if(listTemp[1] == "HIGH" || listTemp[1] == "LOW")
        {
            Pin* toUpdatePin = getPinFromLabel(listTemp[0]);
            if(listTemp[1] == "HIGH")
            {
                toUpdatePin->setState(true);
            } else
            {
                toUpdatePin->setState(false);
            }
            thePortData->onCheckingModificationsDone(true);
        } else
        {
            thePortData->onCheckingModificationsDone(false);
        }
    }
    else
    {
        thePortData->onCheckingModificationsDone(false);
    }
}

void Data::updateInputAndOutput(bool isValid)
{    
    if(isValid)
    {
        //then do the update of the gates logic
        for(int i = 0; i < vGates.count(); i++)
        {
            vGates[i]->updateLogic(levelMax);
        }
        thePortData->onNewStatusModifications("[modifications status] : update is valid !");
    }
    else
    {
        thePortData->onNewStatusModifications("[modifications status] : update is not valid, select a label !");
    }
    thePortData->onUpdateDone(isValid);
}
