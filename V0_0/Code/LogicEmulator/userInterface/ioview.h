#ifndef IOVIEW_H
#define IOVIEW_H

#include <iostream>
#include <QPushButton>
#include <QFileDialog>
#include <QWidget>
#include <QRect>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QDebug>
#include <QVector>
#include <QGraphicsView>
#include <QLabel>
#include <QRect>
#include <QScreen>
#include <QGuiApplication>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QListWidget>
#include <QPen>
#include <QColor>

#include "interfaces/iviewupdate.h"
#include "data/gate.h"

#define RESULT_QLABEL_W 1200
#define RESULT_QLABEL_H 300

#define FILENAME_QLABEL_W 600
#define FILENAME_QLABEL_H 50

#define CODE_QLABEL_W 600
#define CODE_QLABEL_H 700

#define GATES_QLABEL_W 1200
#define GATES_QLABEL_H 600
class PortUI;


class IOView : public QWidget, public IViewUpdate
{
    Q_OBJECT

public:
    explicit IOView(QWidget* parent = 0);
    virtual ~IOView();
    void initRelations(PortUI* p1);
    int getWidth() const;
    int getHeight() const;

    //inputView  public functions and variables
    QString getPath();

    //outputView public functions and variables
    void drawGates(QVector<Gate> &gates, int maxLevel);
    void drawWires(QVector<Gate> &gates, int maxLevel);
    void onNewCode(QString listCode);
    void onNewFileName(QString filename);
    void onNewResults(QString results);
    void onDeleteOldGatesAndCode();

private:
    PortUI* thePortUI;
    int width;
    int height;

    //inputView privates variables and functions
    QPushButton* load;
    void initGraphicalObject();

    //outputView privates variables and functions
    QGraphicsView* drawWindow;
    QGraphicsScene *scnGates;
    QLabel* labelResult;
    QLabel* labelFileName;
    //QListWidget* listCode;
    QGraphicsView* codeWindow;
    QGraphicsScene* scnCode;
    QString styleSheet;

    void drawLineBetweenP1P2(int x1, int y1, int x2, int y2, QGraphicsScene &scn, QPen &pen);

public slots:
    void buttonClicked();


    // IViewUpdate interface, required
public:
    virtual void onButtonLoadPressed(QString path);
};

#endif // IOVIEW_H
