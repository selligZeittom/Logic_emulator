#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include "view.h"

class OutputView : public View
{
    Q_OBJECT
public:
    OutputView(int x, int y, int width, int heigth, QString title);
    void paintEvent(QPaintEvent* event);
protected:
    void changed();

};

#endif // OUTPUTVIEW_H
