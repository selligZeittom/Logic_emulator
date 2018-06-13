#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

void sortCodeIntoVar(QString codeChecked)
{
    QStringList idTemp;
    QStringList labelsTemp;
    QStringList connectedLabelsTemp;
    QStringList levelsTemp;

    //first get the string into a list line by line
    QRegularExpression lineByline("\r\n");
    QStringList words = codeChecked.split(lineByline);

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
            idTemp.append(idMatch.captured());

        }
        if(globalMatchLevel.hasMatch())
        {
            QString matched = globalMatchLevel.captured();
            QRegularExpressionMatch levelMatch = levelFilter.match(matched);
            qDebug() << "level : " << levelMatch.captured();
            levelsTemp.append(levelMatch.captured());
        }
        if(globalMatchLabel.hasMatch())
        {
            QString matched = globalMatchLabel.captured();
            QRegularExpressionMatch labelMatch1 = labelFilter1.match(matched);
            if(labelMatch1.hasMatch())
            {
                qDebug() << "label : " << labelMatch1.captured();
                labelsTemp.append(labelMatch1.captured());
            }
            else
            {
                QRegularExpressionMatch labelMatch2 = labelFilter2.match(matched);
                qDebug() << "label : " << labelMatch2.captured();
                labelsTemp.append(labelMatch2.captured());
            }
        }

        if(globalMatchConnectedLabel.hasMatch())
        {
            QString matched = globalMatchConnectedLabel.captured();
            QRegularExpressionMatch connectedLabelMatch1 = connectedLabelFilter1.match(matched);
            if(connectedLabelMatch1.hasMatch())
            {
                qDebug() << "the connected label : " << connectedLabelMatch1.captured();
                connectedLabelsTemp.append(connectedLabelMatch1.captured());
            }
            else
            {
                QRegularExpressionMatch connectedLabelMatch2 = connectedLabelFilter2.match(matched);
                if(connectedLabelMatch2.hasMatch())
                {
                    qDebug() << "the connected label : " << connectedLabelMatch2.captured();
                    connectedLabelsTemp.append(connectedLabelMatch2.captured());
                }
                else
                {
                    QRegularExpressionMatch connectedLabelMatch3 = connectedLabelFilter3.match(matched);
                    qDebug() << "the connected label : " << connectedLabelMatch3.captured();
                    connectedLabelsTemp.append(connectedLabelMatch3.captured());
                }
            }
        }
    }

    for (int i = 0; i < idTemp.count(); ++i) {
        qDebug() << idTemp[i];
    }
    qDebug()<<"___________________________";
    for (int i = 0; i < labelsTemp.count(); ++i) {
        qDebug() << labelsTemp[i];
    }
    qDebug()<<"___________________________";
    for (int i = 0; i < connectedLabelsTemp.count(); ++i) {
        qDebug() << connectedLabelsTemp[i];
    }
    qDebug()<<"___________________________";
    for (int i = 0; i < levelsTemp.count(); ++i) {
        qDebug() << levelsTemp[i];
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:/Users/Gilles Mottiez/Documents/HES/Informatique/Projet_inf2/Logic_emulator/JSON/TEST3_4l.json";
    QString codeChecked = "";
    QFile* file = new QFile(path);
    file->open(QIODevice::ReadOnly);
    QTextStream* reader = new QTextStream(file);
    codeChecked = reader->readAll();

    sortCodeIntoVar(codeChecked);
    return a.exec();
}
