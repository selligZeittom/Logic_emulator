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

void Data::loadFile()
{
    file = new QFile(path);

    file->open(QIODevice::ReadOnly);
    if(!file->isOpen())
    {
        qDebug() << "failed to open file...";
        thePortData->onError(ERROR_LOADING_FILE);
    }
    thePortData->onLoadingDone();
}

void Data::convertJsonToGates()
{
    //first clear the variables
    vGates.clear();
    //vPins.clear();
    levelMax = 0;
    fileName = "";
    result = "";
    code = "";

    QTextStream reader(file);
    code = reader.readAll();
    file->close();

    //translate the string into a byte array
    QByteArray byteData = code.toLocal8Bit();

    //the main document from the json file
    QJsonDocument doc = QJsonDocument::fromJson(byteData);
    if(doc.isEmpty())
    {
        qDebug() << "empty file...";
        thePortData->onError(ERROR_JSON_CONVERSION);
    }

    //convert it to a global object
    QJsonObject design = doc.object();
    try {
        //get the name of the file
        fileName = design["name"].toString();
        qDebug()<< fileName<< " : fileName";
        int nGates = design["nGates"].toInt();
        qDebug()<< nGates << " : nGates";

        //get the array of all the gates
        QJsonArray gates = design["gates"].toArray();
        if(gates.isEmpty())
        {
            qDebug()<<"failed to create gates array...";
        }

        //get all the gates of the design
        for(int i=0; i< gates.count(); ++i)
        {
            //get the characteristics of the gate
            QJsonObject gate = gates.at(i).toObject();

            int type = gate["type"].toInt();
            qDebug()<< type<< " : type";

            QString id = gate["ID"].toString();
            qDebug()<< id<< " : id";

            int level = gate["level"].toInt();
            qDebug()<< level<< " : level";

            int nInput = gate["nInput"].toInt();
            qDebug()<< nInput<< " : nInput";

            //get the array of the pins
            QJsonArray pins = gate["pins"].toArray();
            if(pins.isEmpty())
            {
                qDebug()<<"failed to create pins array...";
            }
            QVector<Pin> vPinsIO;
            for(int j=0; j< pins.count(); ++j)
            {
                QJsonObject pin = pins.at(j).toObject();
                QString label = pin["label"].toString();
                qDebug()<< label<< " : label";
                QString connected = pin["connected"].toString();
                qDebug()<< connected<< " : connected";
                qDebug() << "......................";

                //create a Pin object an add it to the end of the vector
                Pin* p = new Pin(label, connected);
                //vPins.push_back(*p); //add to the global vector
                vPinsIO.push_back(*p);//add to the gate's vector
            }

            //create a logic gate
            Gate* newGate = new Gate(id, type, level, nInput, vPinsIO);
            vGates.push_back(*newGate); //add to the global vector

            qDebug() << "--------------------";
        }
    }
    catch (...)
    {
        qDebug() << "error while converting...";
        thePortData->onError(1);
    }

    setGatesAndPins();
}

void Data::computeLogic()
{
    qDebug() << "computing logic";
    for (int i = 0; i < vGates.count(); ++i)
    {
        if(vGates[i].getLevel() == levelMax)
        {
            this->result += vGates[i].outputToString();
        }
    }

    thePortData->onComputingDone();

}

void Data::setPath(QString path)
{
    this->path = path;
}

void Data::drawResults()
{
    thePortData->onNewFileNAme(fileName);
    thePortData->onNewCode(code);
    thePortData->onNewResults(result);
    thePortData->onNewGates(vGates);
    thePortData->onDrawingDone();
}

Pin *Data::getConnectedPin(QString labelCOnnectedPin)
{
    Pin* retVal;
    for (int i = 0; i < vGates.count(); ++i)
    {
        for(int j = 0; j < vGates[i].getInputPins().count(); j++)
        {

        }
    }
}

/*
Pin &Data::getCorrespondingPin(QString label)
{
    Pin toReturn;
    for (int i = 0; i < vPins.count(); ++i) {
        if(vPins[i].getLabelPin() == label){
            toReturn = vPins[i];
        }
    }
    return toReturn;
}
*/

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
    for(int currentLevel = 0; currentLevel < levelMax; currentLevel++)
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
                    //gate.getOutputPin()->initRelations();
                    gate.computeLogicAndSetPixmap();
                }

                //for the others level
                else
                {
                    //set the input pins
                    for(int i = 0; i < gate.getInputPins().count(); i++)
                    {

                    }
                    gate.computeLogicAndSetPixmap();
                    //for the not final level
                    else if(levelGate < levelMax)
                    {

                    }
                }
            }
        }
    }


    thePortData->onConvertingDone();
}
