#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    load = new QPushButton("test", this);
    connect(load, SIGNAL(clicked(bool)), this, SLOT(clicked()));
}

MainWindow::~MainWindow()
{

}

void MainWindow::clicked()
{
    qDebug() << "clicked";
}
