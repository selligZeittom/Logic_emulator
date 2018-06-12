#include <QCoreApplication>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QStringList>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString path = "C:/Users/Gilles Mottiez/Documents/HES/Informatique/Projet_inf2/Logic_emulator/JSON/TEST3_4l.json";
    QString codeChecked = "";
    QFile* file = new QFile(path);
    file->open(QIODevice::ReadOnly);
    QTextStream* reader = new QTextStream(file);
    codeChecked = reader->readAll();

    /*
     *  "ID": "O1",
     *  "level": 0,
     *  "label": "O1_I1",
     *  "connectedLabel": "LOG_LOW"
     *
     */

    //first get the string into a list line by line
    QRegularExpression lBl("\r\n");
    QStringList words = codeChecked.split(lBl);

    //this is the filter used to get the lines corresponding to an ID
    QRegularExpression idFilterGlobal("\\W\\w\\w\\W\\W \\W\\w\\d\\W");

    //then get only the 2 letters from the ID
    QRegularExpression idFilterID("\\w\\d");

    //this is the filter used to get the lines corresponding to a level
    QRegularExpression levelFilterGlobal("\\W\\w+\\W\\W \\d\\W");

    //then get only the number of the level
    QRegularExpression levelFilter("\\d");

    //this is the filter used to get the lines corresponding to a label
    QRegularExpression labelFilterGlobal("\\W\\w\\d\\W\\w\\d\\W");

    //then get only the the label itself
    QRegularExpression labelFilter("\\d");




    for (int i = 0; i < words.count(); ++i) {
        QString str = words[i];
        QRegularExpressionMatch globalMatchID = idFilterGlobal.match(str);
        QRegularExpressionMatch globalMatchLevel = levelFilterGlobal.match(str);
        QRegularExpressionMatch globalMatchLabel = labelFilterGlobal.match(str);
        if(globalMatchID.hasMatch())
        {
            QString matched = globalMatchID.captured();
            qDebug() << "global id match : " << matched;
            QRegularExpressionMatch idMatch = idFilterID.match(matched);
            qDebug() << "id : " << idMatch.captured();

        }
        if(globalMatchLevel.hasMatch())
        {
            QString matched = globalMatchLevel.captured();
            qDebug() << "global level match : " << matched;
            QRegularExpressionMatch levelMatch = levelFilter.match(matched);
            qDebug() << "level : " << levelMatch.captured();
        }
        if(globalMatchLabel.hasMatch())
        {
            QString matched = globalMatchLabel.captured();
            qDebug() << "global label match : " << matched;
            QRegularExpressionMatch labelMatch = labelFilterGlobal.match(matched);
            qDebug() << "level : " << labelMatch.captured();
        }

    }
    return a.exec();
}
