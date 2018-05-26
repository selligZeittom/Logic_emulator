#ifndef OUTPUTVIEW_H
#define OUTPUTVIEW_H

#include <iostream>
#include <QVector>
#include <QString>
#include <QGraphicsView>
#include <QLabel>
#include <QWidget>
#include <QRect>
#include <QScreen>
#include <QGuiApplication>
#include <QGraphicsScene>


#include "data/gate.h"

#define RESULT_QLABEL_W 1200
#define RESULT_QLABEL_H 300

#define FILENAME_QLABEL_W 600
#define FILENAME_QLABEL_H 50

#define CODE_QLABEL_W 600
#define CODE_QLABEL_H 700

#define GATES_QLABEL_W 1200
#define GATES_QLABEL_H 600

class View;

class OutputView : QWidget
{

    Q_OBJECT

public:
    explicit OutputView(QWidget* parent = 0);
    virtual ~OutputView();
    void initRelations(View* p1);

    virtual void paintEvent(QPaintEvent *event);
    void draw(QVector<Gate> gates);
    void setText(QString result);

private:
    QGraphicsView* drawWindow;
    QLabel* result;
    QLabel* fileName;
    QLabel* code;
    View* host;
    QString styleSheet;

    void initGraphicalObject();
};

#endif // OUTPUTVIEW_H
