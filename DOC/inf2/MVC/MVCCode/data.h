#ifndef DATA_H
#define DATA_H

#include "observer.h"
#include <Qpainter>
class Logic;

class Data
{
    friend class Logic;
    class Circle
    {
        friend class Logic;
    public:
        Circle(Data* host);
        ~Circle();
        void draw(QPainter* p);
        int getX();
        int getY();
    private:
        void setXY(int x, int y);
        int x;
        int y;
        Data* host;
    };

public:
    Data();
    void subscribe(Observer* obs);
    Circle *getCircle();

private:
    Observer** observers;
    int obsCnt;
    Circle* c;
    void notifyAll();
    void setCircle();
};

#endif // DATA_H
