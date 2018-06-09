#include "data.h"
#include "portdata.h"
#include "globalvariables.h"


Data::Data()
{
    this->thePortData = NULL;
    this->jsonConverter = NULL;
    this->file = NULL;
    levelMax = 0;
}

Data::~Data()
{

}

void Data::initRelations(PortData *p1)
{
    this->thePortData = p1;
}

void Data::loadFile(QString path)
{
    this->path = path;
    file = new QFile(path);

    file->open(QIODevice::ReadOnly);
    if(!file->isOpen())
    {
        qDebug() << "failed to open file...";
        code="no code...";
        thePortData->onError(ERROR_LOADING_FILE);
    }
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

    QTextStream reader(file);
    code = reader.readAll();
    if(code.isEmpty())
    {
        qDebug() << "failed to read file...";
        thePortData->onError(ERROR_READING_FILE);
    }
    file->close();

    //translate the string into a byte array
    QByteArray byteData = code.toLocal8Bit();

    //the main document from the json file
    QJsonDocument doc = QJsonDocument::fromJson(byteData);
    if(doc.isEmpty())
    {
        qDebug() << "empty file...";
        thePortData->onError(ERROR_JSON_LOADING);
    }

    //convert it to a global object
    QJsonObject design = doc.object();
    if(design.isEmpty())
    {
        qDebug() << "error of the main design...";
        thePortData->onError(ERROR_JSON_CONVERSION);
    }

    //get the name of the file
    fileName = design["name"].toString();

    //get the array of all the gates
    QJsonArray gates = design["gates"].toArray();
    if(gates.isEmpty())
    {
        qDebug()<<"failed to create gates array...";
        thePortData->onError(ERROR_JSON_CONVERSION_ARRAY);
    }

    //get all the gates of the design
    for(int i=0; i< gates.count(); ++i)
    {
        //get the characteristics of the gate
        QJsonObject gate = gates.at(i).toObject();
        if(gate.isEmpty())
        {
            qDebug()<<"failed to create gate...";
            thePortData->onError(ERROR_JSON_CONVERSION_GATE);
        }

        QString id = gate["ID"].toString();
        if(id.isEmpty())
        {
            qDebug()<<"failed to get id...";
            thePortData->onError(ERROR_JSON_CONVERSION_ID);
        }

        int level = gate["level"].toInt();

        //get the array of the pins
        QJsonArray pins = gate["pins"].toArray();
        if(pins.isEmpty())
        {
            qDebug()<<"failed to create pins array...";
            thePortData->onError(ERROR_JSON_CONVERSION_ARRAY);
        }
        QVector<Pin> vPinsIO;
        for(int j=0; j< pins.count(); ++j)
        {
            QJsonObject pin = pins.at(j).toObject();
            if(pin.isEmpty())
            {
                qDebug()<<"failed to create pin...";
                thePortData->onError(ERROR_JSON_CONVERSION_PIN);
            }
            QString label = pin["label"].toString();
            if(label.isEmpty())
            {
                qDebug()<<"failed to get pin's label...";
                thePortData->onError(ERROR_JSON_CONVERSION_LABEL);
            }
            QString connectedLabel = pin["connectedLabel"].toString();
            if(connectedLabel.isEmpty())
            {
                qDebug()<<"failed to get pin's connectedLabel...";
                thePortData->onError(ERROR_JSON_CONVERSION_LABEL);
            }

            //create a Pin object an add it to the end of the vector
            Pin* p = new Pin(label, connectedLabel);
            vPinsIO.push_back(*p);//add to the gate's vector
        }

        //create a logic gate
        Gate* newGate = new Gate(id, level, vPinsIO);
        vGates.push_back(*newGate); //add to the global vector

    }

    thePortData->onConvertingDone();
}

void Data::outputResultsToString()
{
    qDebug() << "computing logic";
    for (int i = 0; i < vGates.count(); ++i)
    {
        if(vGates[i].getLevel() == levelMax)
        {
            this->result += "\r\n";
        }
        this->result += vGates[i].outputToString();
        this->result += "\r\n";
    }

    thePortData->onComputingDone();

}

void Data::drawResults()
{
    thePortData->onNewFileNAme(fileName);
    thePortData->onNewCode(code);
    thePortData->onNewResults(result);
    thePortData->onNewGates(vGates, levelMax);
    thePortData->onDrawingDone();
}

Pin &Data::getConnectedPin(QString labelCOnnectedPin)
{
    Pin retVal = NULL;
    for (int i = 0; i < vGates.count(); ++i)
    {
        //search for an output pin
        QString labelPin = vGates[i].getOutputPin()->getLabelPin();
        if(labelPin == labelCOnnectedPin)
        {
            return *(vGates[i].getOutputPin());
        }

        //search for an input pin
        for(int j = 0; j < vGates[i].getInputPins().count(); j++)
        {
            labelPin = vGates[i].getInputPins()[j].getLabelPin();
            if(labelPin == labelCOnnectedPin)
            {
                return (vGates[i].getInputPins()[j]);
            }
        }
    }
    return retVal;
}

void Data::setGatesAndPins()
{
    //get the max level of the design
    levelMax = 0;
    for(int i = 0; i < vGates.count(); i++)
    {
        int levelGate = vGates[i].getLevel();
        if(levelGate > levelMax)
        {
            levelMax = levelGate;
        }
    }

    //then compute level by level
    for(int currentLevel = 0; currentLevel <= levelMax; currentLevel++)
    {

        //look for all the gates in the vector if the level correspond to the currentLEvel
        for(int currentGate = 0; currentGate < vGates.count(); currentGate++)
        {
            int levelGate = vGates[currentGate].getLevel();
            if(levelGate == currentLevel)
            {
                Gate& gate = vGates[currentGate];

                //for the first level there isn't a real connected pin
                if(levelGate == 0)
                {
                    for(int i = 0; i < gate.getInputPins().count(); i++)
                    {
                        if(gate.getInputPins()[i].getLabelConnectedPin().contains("HIGH"))
                        {
                            gate.getInputPins()[i].setState(true);
                        }
                        else if(gate.getInputPins()[i].getLabelConnectedPin().contains("LOW"))
                        {
                            gate.getInputPins()[i].setState(false);
                        }
                    }
                    Pin& outputPin = *gate.getOutputPin();
                    outputPin.initRelations(&getConnectedPin(outputPin.getLabelConnectedPin()));
                    gate.computeLogicAndSetPixmap();
                }

                //for the others level
                else
                {
                    //set the input pins
                    for(int i = 0; i < gate.getInputPins().count(); i++)
                    {
                        Pin& inputPin = gate.getInputPins()[i];
                        Pin* pinToConnect = &getConnectedPin(inputPin.getLabelConnectedPin());
                        inputPin.initRelations(pinToConnect);
                        inputPin.setState(pinToConnect->getState());
                    }
                    //for the not final level
                    if(levelGate < levelMax)
                    {
                        Pin& outputPin = *gate.getOutputPin();
                        outputPin.initRelations(&getConnectedPin(outputPin.getLabelConnectedPin()));
                    }
                    gate.computeLogicAndSetPixmap();
                }
            }
        }
    }
    outputResultsToString();
}

void Data::processError(QString labelError)
{
    thePortData->onNewFileNAme(fileName);
    thePortData->onDeleteOldGatesAndCode();
    thePortData->onNewCode("!!! ERROR in the code !!!\r\n"+code);
    thePortData->onNewResults(labelError);
    thePortData->onProcessErrorDone();
}

