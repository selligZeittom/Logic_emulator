#include "outputview.h"
#include <QDebug>

OutputView::OutputView(int x, int y, int width, int heigth, QString title)
 : View(x, y, width, heigth, title)
{
}

void OutputView::paintEvent(QPaintEvent *event)
{
    if (pData->getCircle())
    {
        QPainter p(this);
        pData->getCircle()->draw(&p);
    }
}

void OutputView::changed()
{
    update();
}


