#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

#include "data.h"
#include "logic.h"

class View : public QWidget, public Observer
{
    Q_OBJECT
public:
    View(int x, int y, int width, int heigth, QString title);
    void initRelations(Data* d, Logic* l);

protected:
    Data* pData;
    Logic* pLogic;
    void changed();

private:

    int x;
    int y;
    int height;
    int width;
    QString title;

private:
    void setupUI();
};

#endif // VIEW_H
