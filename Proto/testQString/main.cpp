#include <QCoreApplication>
#include <QRegularExpression>
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

    QRegularExpression rx("\\s");
    QStringList words = codeChecked.split(rx, QString::SkipEmptyParts);
    for (int i = 0; i < words.count(); ++i) {
        qDebug() << words[i];

    }
    return a.exec();
}
