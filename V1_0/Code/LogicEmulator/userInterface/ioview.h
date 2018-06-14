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
#include <QTextDocument>
#include <QLineEdit>

#include "interfaces/iviewupdate.h"
#include "data/gate.h"

class PortUI;


class IOView : public QWidget
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
    void drawGates(QVector<Gate*> &gates, int maxLevel);
    void drawWires(QVector<Gate*> &gates, int maxLevel);
    void onNewCode(QString listCode);
    void onNewFileName(QString filename);
    void onNewResults(QString results);
    void onNewListConnectedLabels(QStringList listConnectedLabel);
    void onNewStatusModifications(QString status);
    void onDeleteOldGatesAndCode();

private:
    PortUI* thePortUI;
    int width;
    int height;

    //inputView privates variables and functions
    QPushButton* load;
    QPushButton* check;

    QListWidget* listLabel;
    QListWidget* listState;
    void initGraphicalObject();

    //outputView privates variables and functions
    QGraphicsView* drawWindow;
    QGraphicsScene *scnGates;
    QLabel* labelResult;
    QLabel* labelFileName;
    QLabel* labelModifStatus;
    QGraphicsView* codeWindow;
    QGraphicsScene* scnCode;

    void drawLineBetweenP1P2(int x1, int y1, int x2, int y2, QGraphicsScene &scn, QPen &pen);

public slots:
    void loadButtonClicked();
    void updateButtonClicked();

};

#endif // IOVIEW_H
