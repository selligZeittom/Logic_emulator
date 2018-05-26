#include "data.h"

#include "QDebug"
#define MAXOBSERVERS 5

Data::Data()
{
    observers = new Observer*[MAXOBSERVERS];

    for (int cnt=0; cnt<MAXOBSERVERS; cnt++)
    {
        observers[cnt] = 0;
    }
    obsCnt=0;
    c = 0;
}

void Data::subscribe(Observer *obs)
{
    if (obsCnt < MAXOBSERVERS)
    {
        observers[obsCnt++] = obs;
    }
}

void Data::notifyAll()
{
    for (int cnt=0; cnt<MAXOBSERVERS; cnt++)
    {
        if (observers[cnt])
        {
            observers[cnt]->changed();
        }

    }
}

Data::Circle *Data::getCircle()
{
    return c;
}

void Data::setCircle()
{
    if (c)
    {
        delete c;
    }
    c = new Circle(this);
    notifyAll();
}

//this is the Circle Stuff
Data::Circle::Circle(Data* host)
{
    x=y=0;
    this->host=host;
}

Data::Circle::~Circle()
{

}

void Data::Circle::draw(QPainter *p)
{
    QColor col(255,0,0);
    p->setPen(col);
    p->setBrush(QBrush(col));
    p->drawEllipse(x,y,20,20);
}

void Data::Circle::setXY(int x, int y)
{
    bool changed = false;
    if (this->x != x)
    {
        this->x=x;
        changed = true;
    }
    if (this->x != y)
    {
        this->y=y;
        changed = true;
    }

    if (changed)
    {
        host->notifyAll();
    }

}

int Data::Circle::getX()
{
    return x;
}

int Data::Circle::getY()
{
    return y;
}


