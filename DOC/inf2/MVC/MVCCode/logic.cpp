#include "logic.h"
#include <QString>
#include <QDebug>
#include <QApplication>

Logic::Logic()
{
    pData = 0;
}

void Logic::initRelations(Data *d)
{
    pData = d;
}

void Logic::onInput(QString data)
{
    if (data.left(1).toLower()=="c")
    {
        qDebug() << "create";
        pData->setCircle();
        pData->getCircle()->setXY(200,150);
    }

    if (data.left(1).toLower()=="l")
    {
        qDebug() << "left";
        if (pData->getCircle())
        {
            pData->getCircle()->setXY(pData->getCircle()->getX()-20,pData->getCircle()->getY());
        }
    }
    if (data.left(1).toLower()=="r")
    {
        qDebug() << "right";
        if (pData->getCircle())
        {
            pData->getCircle()->setXY(pData->getCircle()->getX()+20,pData->getCircle()->getY());
        }
    }

    if (data.left(1).toLower()=="u")
    {
        qDebug() << "up";
        if (pData->getCircle())
        {
            pData->getCircle()->setXY(pData->getCircle()->getX(),pData->getCircle()->getY()-20);
        }

    }

    if (data.left(1).toLower()=="d")
    {
        qDebug() << "down";
        if (pData->getCircle())
        {
            pData->getCircle()->setXY(pData->getCircle()->getX(),pData->getCircle()->getY()+20);
        }
    }

    if (data.left(1).toLower()=="x")
    {
        qDebug() << "exit";
        QApplication::closeAllWindows();
        QApplication::exit();
    }
}

