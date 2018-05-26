#include "listview.h"

#include <QDebug>
#include <QScrollBar>

ListView::ListView(int x, int y, int width, int height, QString title)
{
    pData = 0;
    pLogic = 0;

    this->x = x;
    this->y = y;
    this->height = height;
    this->width = width;
    this->title = title;
    setupUI();
}

void ListView::initRelations(Data *d, Logic *l)
{
    pData = d;
    pLogic = l;
}

void ListView::changed()
{
    this->addItem(QString("x = %1 , y = %2")
                  .arg(pData->getCircle()->getX())
                  .arg(pData->getCircle()->getY()));
    this->scrollToBottom();
}

void ListView::setupUI()
{
    this->setGeometry(x,y,width,height);
    this->setWindowTitle(title);
    this->setVisible(true);
}
