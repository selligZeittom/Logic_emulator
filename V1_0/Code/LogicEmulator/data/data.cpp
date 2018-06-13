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

    //get the original lists of the code
    sortCodeIntoQStringList(code, id, labels, connectedLabels, levels);

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
        Gate* newGate = new Gate(id, level, vPinsIO);
        vGates.push_back(newGate); //add to the global vector
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
void Data::drawResults()
{
    thePortData->onNewFileNAme(fileName);
    thePortData->onNewCode(code);
    thePortData->onNewResults(result);
    thePortData->onNewGates(vGates, levelMax);
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
                    gate->computeLogicAndSetPixmap();
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
                    gate->computeLogicAndSetPixmap();
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

void Data::checkModifications(QString newCode)
{
    //updates the list with some new string
    sortCodeIntoQStringList(newCode, idTemp, labelsTemp, connectedLabelsTemp, levelsTemp);

    //check for the id, label and level : no modifications authorized
    for (int i = 0; i < id.count(); ++i)
    {
        if(id[i] != idTemp[i])
        {
            thePortData->onCheckingModificationsDone(false);
        }
    }

    for (int i = 0; i < labels.count(); ++i)
    {
        if(labels[i] != labelsTemp[i])
        {
            thePortData->onCheckingModificationsDone(false);
        }
    }

    for (int i = 0; i < levels.count(); ++i)
    {
        if(levels[i] != levelsTemp[i])
        {
            thePortData->onCheckingModificationsDone(false);
        }
    }

    //now check and compare the connectedLabel
    for (int i = 0; i < connectedLabels.count(); ++i)
    {
        QString conLabel = connectedLabels[i];
        QString conLabelTemp = connectedLabelsTemp[i];

        //find the difference
        if(conLabel != conLabelTemp)
        {
            //if there is a difference and the original label is : LOG_LOW -> the new is obligatory LOG_HIGH
            if(conLabel == "LOG_LOW" && conLabelTemp != "LOG_HIGH")
            {
                thePortData->onCheckingModificationsDone(false);
            }
            //if there is a difference and the original label is : LOG_HIGH -> the new is obligatory LOG_LOW
            else if(conLabel == "LOG_HIGH" && conLabelTemp != "LOG_LOW")
            {
                thePortData->onCheckingModificationsDone(false);
            }
            //means that the modifications is valid...
            else
            {
                connectedLabels[i] = connectedLabelsTemp[i];
            }
        }
    }
    thePortData->onCheckingModificationsDone(true);
}


void Data::sortCodeIntoQStringList(QString newCode, QStringList &idList, QStringList &labelsList, QStringList &connectedLabelsList, QStringList &levelList)
{
    //first clear the list
    idList.clear();
    labelsList.clear();
    connectedLabelsList.clear();
    levelList.clear();

    //first get the string into a list line by line
    QRegularExpression lineByline("\r\n");
    QStringList words = newCode.split(lineByline);

    //this is the filter used to get the lines corresponding to an ID
    QRegularExpression idFilterGlobal("\\W\\w\\w\\W\\W \\W\\w\\d\\W");

    //then get only the 2 letters from the ID
    QRegularExpression idFilterID("\\w\\d");

    //this is the filter used to get the lines corresponding to a level
    QRegularExpression levelFilterGlobal("\\W\\w+\\W\\W \\d\\W");

    //then get only the number of the level
    QRegularExpression levelFilter("\\d");

    //this is the filter used to get the lines corresponding to a label
    QRegularExpression labelFilterGlobal("\\W\\w{5}\\W\\W \\W\\w\\d_\\w.*");

    //then get only the the label itself
    QRegularExpression labelFilter1("\\w\\d_\\w\\d");

    //then get only the the label itself
    QRegularExpression labelFilter2("\\w\\d_\\w");

    //this is the filter used to get the lines corresponding to a connectedLabel
    QRegularExpression connectedLabelFilterGlobal("\\W\\w{14}\\W\\W \\W\\w.{3,}");

    //then get only the the connectedLabel itself like O1_I1
    QRegularExpression connectedLabelFilter1("\\w\\d_\\w\\d");

    //then get only the the connectedLabel itself like LOG_LOW
    QRegularExpression connectedLabelFilter2("\\w{3}_\\w{3}");

    //then get only the the connectedLabel itself like O1_I1
    QRegularExpression connectedLabelFilter3("\\w\\d_\\w");



    //look on every word of the list
    for (int i = 0; i < words.count(); ++i)
    {
        QString str = words[i];
        QRegularExpressionMatch globalMatchID = idFilterGlobal.match(str);
        QRegularExpressionMatch globalMatchLevel = levelFilterGlobal.match(str);
        QRegularExpressionMatch globalMatchLabel = labelFilterGlobal.match(str);
        QRegularExpressionMatch globalMatchConnectedLabel = connectedLabelFilterGlobal.match(str);

        if(globalMatchID.hasMatch())
        {
            QString matched = globalMatchID.captured();
            QRegularExpressionMatch idMatch = idFilterID.match(matched);
            qDebug() << "id : " << idMatch.captured();
            idList.append(idMatch.captured());

        }
        if(globalMatchLevel.hasMatch())
        {
            QString matched = globalMatchLevel.captured();
            QRegularExpressionMatch levelMatch = levelFilter.match(matched);
            qDebug() << "level : " << levelMatch.captured();
            levelList.append(levelMatch.captured());
        }
        if(globalMatchLabel.hasMatch())
        {
            QString matched = globalMatchLabel.captured();
            QRegularExpressionMatch labelMatch1 = labelFilter1.match(matched);
            if(labelMatch1.hasMatch())
            {
                qDebug() << "label : " << labelMatch1.captured();
                labelsList.append(labelMatch1.captured());
            }
            else
            {
                QRegularExpressionMatch labelMatch2 = labelFilter2.match(matched);
                qDebug() << "label : " << labelMatch2.captured();
                labelsList.append(labelMatch2.captured());
            }
        }

        if(globalMatchConnectedLabel.hasMatch())
        {
            QString matched = globalMatchConnectedLabel.captured();
            QRegularExpressionMatch connectedLabelMatch1 = connectedLabelFilter1.match(matched);
            if(connectedLabelMatch1.hasMatch())
            {
                qDebug() << "the connected label : " << connectedLabelMatch1.captured();
                connectedLabelsList.append(connectedLabelMatch1.captured());
            }
            else
            {
                QRegularExpressionMatch connectedLabelMatch2 = connectedLabelFilter2.match(matched);
                if(connectedLabelMatch2.hasMatch())
                {
                    qDebug() << "the connected label : " << connectedLabelMatch2.captured();
                    connectedLabelsList.append(connectedLabelMatch2.captured());
                }
                else
                {
                    QRegularExpressionMatch connectedLabelMatch3 = connectedLabelFilter3.match(matched);
                    qDebug() << "the connected label : " << connectedLabelMatch3.captured();
                    connectedLabelsList.append(connectedLabelMatch3.captured());
                }
            }
        }
    }
}

void Data::updateInputAndOutput()
{
    //go over each pins and check the LOGICAL input signals
    for(int i = 0; i< connectedLabels.count(); i++)
    {
        if(connectedLabels[i] == "LOG_LOW")
        {
            Pin* pinToSet = getPinFromLabel(labels[i]);
            pinToSet->setState(false);
        }
        else if(connectedLabels[i] == "LOG_HIGH")
        {
            Pin* pinToSet = getPinFromLabel(labels[i]);
            pinToSet->setState(true);
        }
    }

    //then do the update of the gates logic
    for(int i = 0; i < vGates.count(); i++)
    {
        vGates[i]->computeLogicAndSetPixmap();
    }

    thePortData->onUpdateDone();
}
