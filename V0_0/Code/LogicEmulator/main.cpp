#include "mainwindow.h"
#include <QApplication>

#include "factory.h"
#include <XF/xf.h>

int main(int argc, char *argv[])
{
//    QApplication a(argc, argv);

    Factory f;
    f.create();
    f.build();
    //a.setActiveWindow(f.getView());
//    return a.exec();

    return XF::getInstance().exec();
}
