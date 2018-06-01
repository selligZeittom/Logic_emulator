#include "inputview.h"

#define DEBUG_not

InputView::InputView(QWidget *parent) : QWidget(parent)
{
    this->host = NULL;
    this->load = NULL;
}

InputView::~InputView()
{
}

void InputView::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
}

QString InputView::getPath()
{
#ifdef DEBUG

    //set the filter for only json files
    QString filter = "File Description (*.json)";

    //get the opened file
    QString filename =  QFileDialog::getOpenFileName(
                host,
                "Open Json file§",
                QDir::homePath(), filter);
    return filename;

#else
    return "C:/Users/Gilles Mottiez/Documents/HES/Informatique/Projet_inf2/Logic_emulator/JSON/TEST1.json";
#endif
}

void InputView::initGraphicalObject()
{
    this->load = new QPushButton(this);
    load->setGeometry(170, host->getHeight() - 200, 340, 80);
    load->setStyleSheet("QPushButton { background-color : rgb(50, 150, 150); border: 1px solid gray; border-radius: 5px; color : black; }");
    load->setText("Browse a Json file");

    connect(this->load, SIGNAL(clicked(bool)), this, SLOT(buttonClicked(bool)));
}

void InputView::buttonClicked(bool g)
{
    QString path = getPath();
    qDebug() << "file browsed : " << path ;
    onButtonLoadPressed(path);
}

void InputView::onButtonLoadPressed(QString path)
{
    host->onButtonLoadPressed(path);
}

void InputView::onPathSelected()
{
    onPathSelected();
}

void InputView::initRelations(View *p1)
{
    this->host = p1;
    this->setParent(host);

    initGraphicalObject();
    this->show();
}
