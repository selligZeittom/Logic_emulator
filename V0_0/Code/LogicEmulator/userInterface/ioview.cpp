#include "ioview.h"
#include "portui.h"

#define RELEASE

IOView::IOView(QWidget *parent)
{
    this->thePortUI = NULL;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    this->height = screenGeometry.height();
    this->width = screenGeometry.width();

    std::cout << "width : " << width << ", height : " << height << std::endl;

    this->setWindowTitle("Logic Emulator");
    this->setGeometry(0, 35, width, height-35);
    this->setVisible(true);
    this->styleSheet = "QLabel { background-color : white; border: 1px solid gray; border-radius: 10px; color : black; }";
}

IOView::~IOView()
{
}

void IOView::initRelations(PortUI *p1)
{
    this->thePortUI = p1;
    initGraphicalObject();

    this->show();
}

int IOView::getWidth() const
{
    return width;
}

int IOView::getHeight() const
{
    return height;
}

QString IOView::getPath()
{
#ifdef RELEASE

    //set the filter for only json files
    QString filter = "File Description (*.json)";

    //get the opened file
    QString filename =  QFileDialog::getOpenFileName(
                this,
                "Open Json file",
                QDir::homePath(), filter);
    return filename;

#else
    return "C:/Users/Gilles Mottiez/Documents/HES/Informatique/Projet_inf2/Logic_emulator/JSON/TEST4_4level.json";
#endif
}

void IOView::draw(QVector<Gate> gates, int maxLevel)
{
    scnGates->clear();

    //store how many gates per level there are
    int itemPerLevel[maxLevel+1];
    for (int i = 0; i < maxLevel+1; ++i)
    {
        itemPerLevel[i] = 0;
    }

    //get the number of thoses items per level
    for(int i = 0; i < gates.count(); i++)
    {
        itemPerLevel[gates[i].getLevel()]++;
    }
    int xOffset = 200;
    int yOffset = 150;


    qDebug() << maxLevel << " : maxLevel";
    for (int _level = 0; _level <= maxLevel; ++_level) {
        int j = 0;
        for (int i = 0; i < gates.count(); ++i)
        {
            if(gates[i].getLevel() == _level)
            {
                double ratio = 1;
                if(_level != 0)
                {
                    ratio = itemPerLevel[_level-1] / itemPerLevel[_level];
                }
                int x = xOffset * _level;
                 int y = 0;
                if(itemPerLevel[_level] != 1)
                {
                    y = yOffset * j * ratio + (_level) * 75;
                }
                else
                {
                   y =  yOffset * itemPerLevel[0] / 2;
                }
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
                item->setPos(x, y);
                item->setPixmap(gates[i].getQPixMap().scaled(80, 80));
                scnGates->addItem(item);

                QGraphicsTextItem* item2 = new QGraphicsTextItem();
                item2->setPos(x + 20, y + 30);
                item2->setPlainText(gates[i].getID());
                this->scnGates->addItem(item2);

                qDebug() << "draw first gate" << gates[i].getLevel();
                j++;
            }
        }
    }
}

void IOView::onNewCode(QString labelCode)
{
    this->scnCode->clear();
    QGraphicsTextItem* item = new QGraphicsTextItem();
    item->setPlainText(labelCode);
    this->scnCode->addItem(item);
}

void IOView::onNewFileName(QString filename)
{
    this->labelFileName->setText(filename);
}

void IOView::onNewResults(QString results)
{
    this->labelResult->setText(results);
}

void IOView::initGraphicalObject()
{
    this->load = new QPushButton(this);
    load->setGeometry(170, height - 200, 340, 80);
    load->setStyleSheet("QPushButton { background-color : rgb(50, 150, 150); border: 1px solid gray; border-radius: 10px; color : black; }");
    load->setText("Browse a Json file");

    this->drawWindow = new QGraphicsView(this);
    drawWindow->setGeometry(680, 40, GATES_QLABEL_W, GATES_QLABEL_H);
    drawWindow->setStyleSheet("QGraphicsView { background-color : white; border: 1px solid gray; border-radius: 10px; color : black; }");
    scnGates = new QGraphicsScene(drawWindow);
    drawWindow->setScene(scnGates);

    this->labelResult = new QLabel(this);
    labelResult->setGeometry(680, 680, RESULT_QLABEL_W, RESULT_QLABEL_H);
    labelResult->setStyleSheet(styleSheet);
    labelResult->setText("no results ...");

    this->labelFileName = new QLabel(this);
    labelFileName->setGeometry(40, 40, FILENAME_QLABEL_W, FILENAME_QLABEL_H);
    labelFileName->setStyleSheet(styleSheet);
    labelFileName->setText("no file loaded ...");

    this->codeWindow = new QGraphicsView(this);
    codeWindow->setGeometry(40, 140,CODE_QLABEL_W, CODE_QLABEL_H);
    codeWindow->setStyleSheet("QGraphicsView { background-color : white; border: 1px solid gray; border-radius: 10px; color : black; }");
    scnCode = new QGraphicsScene(codeWindow);
    codeWindow->setScene(scnCode);

    load->show();
    drawWindow->show();
    labelResult->show();
    labelFileName->show();
    codeWindow->show();

    connect(this->load, SIGNAL(clicked(bool)), this, SLOT(buttonClicked()));
}

void IOView::buttonClicked()
{
    QString path = getPath();
    qDebug() << "file browsed : " << path ;
    onButtonLoadPressed(path);
}

void IOView::onButtonLoadPressed(QString path)
{
    thePortUI->onButtonLoadPressed(path);
}
