#include "data.h"
#include "portdata.h"


Data::Data()
{
    this->thePortData = NULL;
    this->jsonConverter = NULL;
    this->file = NULL;
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
}

void Data::convertJsonToGates()
{

    file->open(QIODevice::ReadOnly);
    if(!file->isOpen())
    {
        qDebug() << "failed to open file...";
    }

    QTextStream reader(file);
    QString data = reader.readAll();
    file->close();

    //translate the string into a byte array
    QByteArray byteData = data.toLocal8Bit();

    //the main document from the json file
    QJsonDocument doc = QJsonDocument::fromJson(byteData);

    //convert it to a global object
    QJsonObject design = doc.object();

    //get the name of the file
    QString fileName = design["name"].toString();
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
    for(int i=0; i< gates.count(); ++i){

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
            Pin p(label, connected);
            vPins.push_back(p); //add to the global vector
            vPinsIO.push_back(p);//add to the gate's vector
        }

        //create a logic gate
        Gate g(id, type, level, nInput, vPinsIO);
        vGates.push_back(g); //add to the global vector

        qDebug() << "--------------------";
    }
}

void Data::computeLogic()
{

}

void Data::setPath(QString path)
{
    this->path = path;
}
