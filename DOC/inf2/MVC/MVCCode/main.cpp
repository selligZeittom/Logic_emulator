#include "factory.h"
#include <QApplication>
#include "factory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Factory f;
    f.build();
    return a.exec();
}
