#include "outputview.h"
#include "userInterface/view.h"

OutputView::OutputView(QWidget *parent) : QWidget(parent)
{
    this->drawWindow = NULL;
    this->result = NULL;
    this->fileName = NULL;
    this->code = NULL;
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

    if(result)
    {
        delete result;
        result = NULL;
    }

    if(fileName)
    {
        delete fileName;
        fileName = NULL;
    }

    if(code)
    {
        delete code;
        code = NULL;
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

}

void OutputView::setText(QString result)
{
    this->result->setText(result);
}

void OutputView::initGraphicalObject()
{
    this->drawWindow = new QGraphicsView(this);
    drawWindow->setGeometry(680, 40, GATES_QLABEL_W, GATES_QLABEL_H);
    drawWindow->setStyleSheet("QGraphicsView { background-color : white; border: 1px solid gray; border-radius: 5px; color : black; }");

    this->result = new QLabel(this);
    result->setGeometry(680, 680, RESULT_QLABEL_W, RESULT_QLABEL_H);
    result->setStyleSheet(styleSheet);
    result->setText("no results ...");

    this->fileName = new QLabel(this);
    fileName->setGeometry(40, 40, FILENAME_QLABEL_W, FILENAME_QLABEL_H);
    fileName->setStyleSheet(styleSheet);
    fileName->setText("no file loaded ...");

    this->code = new QLabel(this);
    code->setGeometry(40, 140,CODE_QLABEL_W, CODE_QLABEL_H);
    code->setStyleSheet(styleSheet);
    code->setText("NULL");

    drawWindow->show();
    result->show();
    fileName->show();
    code->show();
}
