#include "outputview.h"
#include "userInterface/view.h"

OutputView::OutputView(QWidget *parent) : QWidget(parent)
{
    this->drawWindow = NULL;
    this->labelResult = NULL;
    this->labelFileName = NULL;
    this->labelCode = NULL;
    this->host = NULL;

    this->styleSheet = "QLabel { background-color : white; border: 1px solid gray; border-radius: 5px; color : black; }";
}

OutputView::~OutputView()
{
    if(drawWindow)
    {
        delete drawWindow;
        drawWindow = NULL;
    }

    if(labelResult)
    {
        delete labelResult;
        labelResult = NULL;
    }

    if(labelFileName)
    {
        delete labelFileName;
        labelFileName = NULL;
    }

    if(labelCode)
    {
        delete labelCode;
        labelCode = NULL;
    }
}

void OutputView::initRelations(View *p1)
{
    this->host = p1;
    this->setParent(host);

    initGraphicalObject();
    this->show();
}

void OutputView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
}

void OutputView::draw(QVector<Gate> gates)
{
    int maxLevel = 0;
    for (int i = 0; i < gates.count(); ++i)
    {
        if(gates[i].getLevel() > maxLevel)
        {
            maxLevel = gates[i].getLevel();
        }
    }
    qDebug() << maxLevel << " : maxLevel";
    for (int _level = 0; _level <= maxLevel; ++_level) {
        int j = 0;
        for (int i = 0; i < gates.count(); ++i)
        {
            if(gates[i].getLevel() == _level)
            {
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
                item->setPos(100*_level, 100*j);
                item->setPixmap(gates[i].getQPixMap().scaled(80, 80));
                scn->addItem(item);

                qDebug() << "draw first gate" << gates[i].getLevel();
                j++;
            }
        }
    }
}

void OutputView::onNewCode(QString code)
{
    this->labelCode->setText(code);
}

void OutputView::onNewFileName(QString filename)
{
    this->labelFileName->setText(filename);
}

void OutputView::onNewResults(QString results)
{
    this->labelResult->setText(results);
}

void OutputView::initGraphicalObject()
{
    this->drawWindow = new QGraphicsView(this);
    drawWindow->setGeometry(680, 40, GATES_QLABEL_W, GATES_QLABEL_H);
    drawWindow->setStyleSheet("QGraphicsView { background-color : white; border: 1px solid gray; border-radius: 5px; color : black; }");
    scn = new QGraphicsScene(drawWindow);
    //scn->addPixmap(QPixmap(":/gates/images/and_gate_original.png"));
    drawWindow->setScene(scn);

    this->labelResult = new QLabel(this);
    labelResult->setGeometry(680, 680, RESULT_QLABEL_W, RESULT_QLABEL_H);
    labelResult->setStyleSheet(styleSheet);
    labelResult->setText("no results ...");

    this->labelFileName = new QLabel(this);
    labelFileName->setGeometry(40, 40, FILENAME_QLABEL_W, FILENAME_QLABEL_H);
    labelFileName->setStyleSheet(styleSheet);
    labelFileName->setText("no file loaded ...");

    this->labelCode = new QLabel(this);
    labelCode->setGeometry(40, 140,CODE_QLABEL_W, CODE_QLABEL_H);
    labelCode->setStyleSheet(styleSheet);
    labelCode->setText("NULL");

    drawWindow->show();
    labelResult->show();
    labelFileName->show();
    labelCode->show();
}
