#include "mainwindow.h"
#include <QApplication>

#include "factory.h"
#include <XF/xf.h>

int main(int argc, char *argv[])
{
    Factory f;
    f.create();
    f.build();
    return XF::getInstance().exec();
}
