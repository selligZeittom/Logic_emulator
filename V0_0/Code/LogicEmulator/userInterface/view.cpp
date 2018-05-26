#include "view.h"
#include "outputview.h"
#include "portui.h"

View::View(QWidget *parent)
{
    this->outputView = NULL;
    this->thePortUI = NULL;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    this->height = screenGeometry.height();
    this->width = screenGeometry.width();

    std::cout << "width : " << width << ", height : " << height << std::endl;

    this->setWindowTitle("Logic Emulator");
    this->setGeometry(0, 35, width, height);
    this->setVisible(true);
}

View::~View()
{
}

void View::initRelations(OutputView *p1, PortUI *p2)
{
    this->outputView = p1;
    this->thePortUI = p2;
}

int View::getWidth() const
{
   return width;
}

int View::getHeight() const
{
    return height;
}

void View::onButtonLoadPressed(QString path)
{
    thePortUI->onButtonLoadPressed(path);
}

void View::onPathSelected()
{

}
