#include "inputview.h"

InputView::InputView(int x, int y, int width, int heigth, QString title) :
                     View(x, y, width, heigth, title)
{
    setupUI();
    connect(le,SIGNAL(returnPressed()),this,SLOT(onCommandEntered()));
}

void InputView::setupUI()
{
    le = new QLineEdit("type command here...", this);
    le->setGeometry(10,10,300,20);
    le->selectAll();
    le->setVisible(true);
}

void InputView::onCommandEntered()
{
    le->selectAll();
    pLogic->onInput(le->text());
}
