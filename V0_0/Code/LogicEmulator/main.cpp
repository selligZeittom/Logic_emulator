#include "mainwindow.h"
#include <QApplication>

#include "factory.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Factory f;
    f.create();
    f.build();
    //a.setActiveWindow(f.getView());
    return a.exec();
}
