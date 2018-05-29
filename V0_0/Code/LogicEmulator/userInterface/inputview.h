#ifndef INPUTVIEW_H
#define INPUTVIEW_H

#include <iostream>
#include <QPushButton>
#include <QFileDialog>
#include <QWidget>
#include <QRect>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QDebug>

#include "view.h"
#include "interfaces/iviewupdate.h"

class InputView : public QWidget, public IViewUpdate
{
    Q_OBJECT

public:
    explicit InputView(QWidget* parent = 0);
    virtual ~InputView();
    void initRelations(View* p1);

    virtual void paintEvent(QPaintEvent *event);
    QString getPath();

private:
    QPushButton* load;
    QFileDialog* browser;
    View* host;

    void initGraphicalObject();

public slots:
    void buttonClicked(bool g);

    // IViewUpdate interface
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onPathSelected();
};

#endif // INPUTVIEW_H
