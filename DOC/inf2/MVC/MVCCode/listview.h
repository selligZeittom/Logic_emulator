#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListWidget>

#include "data.h"
#include "logic.h"

class ListView : public QListWidget, public Observer
{
    Q_OBJECT
public:
    ListView(int x, int y, int width, int heigth, QString title);
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

#endif // LISTVIEW_H
