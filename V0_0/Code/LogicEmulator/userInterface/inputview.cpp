#include "inputview.h"

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
    QString filename =  QFileDialog::getOpenFileName(
                this,
                "Open Document",
                QDir::currentPath(),
                "All files (*.*) ;; Document files (*.doc *.rtf);; PNG files (*.png)");
    qDebug() << "selected file path : " << filename.toUtf8();
    return filename;
}

void InputView::initGraphicalObject()
{
    this->load = new QPushButton(this);
    load->setGeometry(170, host->getHeight() - 200, 340, 80);
    load->setStyleSheet("QPushButton { background-color : rgb(47, 230, 228); border: 1px solid gray; border-radius: 5px; color : black; }");
    load->setText("Browse a Json file");
    load->show();
    connect(this->load, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));

}

void InputView::buttonClicked()
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
