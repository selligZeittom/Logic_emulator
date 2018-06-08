#include "ioview.h"
#include "portui.h"

#define RELEASEe

IOView::IOView(QWidget *parent)
{
    this->thePortUI = NULL;

    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    this->height = screenGeometry.height()-35;
    this->width = screenGeometry.width();

    this->setWindowTitle("Logic Emulator V0.0");
    this->setVisible(true);
    this->showMaximized();
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

void IOView::drawGates(QVector<Gate> &gates, int maxLevel)
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
    int xOffset = 250;
    int yOffset = 150;


    //draw the pixmap of the gates, and the connections and set the coordinates
    for (int _level = 0; _level <= maxLevel; ++_level)
    {
        int _usedGates = 0;
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
                    y = yOffset * _usedGates * ratio + (_level) * yOffset/2;
                }
                else
                {
                    y =  yOffset * (itemPerLevel[0]/2) - yOffset/2;
                }
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
                item->setPos(x, y);
                gates[i].setXY(x, y);
                item->setPixmap(gates[i].getQPixMap().scaled(80, 80));
                scnGates->addItem(item);

                QGraphicsTextItem* item2 = new QGraphicsTextItem();
                item2->setPos(x + 20, y + 30);
                item2->setPlainText(gates[i].getID());
                this->scnGates->addItem(item2);
                _usedGates++;

            }
        }
    }
    drawWires(gates, maxLevel);
}

void IOView::drawWires(QVector<Gate> &gates, int maxLevel)
{
    //draw the wires between the gates
    for (int i = 0; i < gates.count(); ++i)
    {
        int x1 = 0;
        int y1 = 0;

        int x2 = 0;
        int y2 = 0;

        QPen* pen;

        //logical inputs
        if(gates[i].getLevel() == 0)
        {
            for(int j = 0; j < gates[i].getInputPins().count(); j++)
            {
                x1 = gates[i].getInputPins()[j].getX();
                y1 = gates[i].getInputPins()[j].getY();

                x2 = x1 - 50;
                y2 = y1;

                if(gates[i].getInputPins()[j].getState())
                {
                    pen = new QPen(QColor(Qt::green))  ;
                }
                else
                {
                    pen = new QPen(QColor(Qt::red))  ;
                }

                pen->setWidth(3);
                scnGates->addLine(x1, y1, x2, y2, *pen);
            }
        }

        //between the gates
        if(gates[i].getLevel() != maxLevel)
        {
            x1 = gates[i].getOutputPin()->getX();
            y1 = gates[i].getOutputPin()->getY();

            x2 = ((gates[i].getOutputPin())->getConnectedPin())->getX();
            y2 = ((gates[i].getOutputPin())->getConnectedPin())->getY();


            if(gates[i].getOutputPin()->getState())
            {
                pen = new QPen(QColor(Qt::green))  ;
            }
            else
            {
                pen = new QPen(QColor(Qt::red))  ;
            }

            pen->setWidth(3);
            //scnGates->addLine(x1, y1, x2, y2, *pen);
            drawLineBetweenP1P2(x1, y1, x2, y2, *scnGates, *pen);
        }
        else
        {
            x1 = gates[i].getOutputPin()->getX();
            y1 = gates[i].getOutputPin()->getY();

            x2 = x1 + 50;
            y2 = y1;

            if(gates[i].getOutputPin()->getState())
            {
                pen = new QPen(QColor(Qt::green))  ;
            }
            else
            {
                pen = new QPen(QColor(Qt::red))  ;
            }

            pen->setWidth(3);
            scnGates->addLine(x1, y1, x2, y2, *pen);
        }
    }
    drawLabel(gates, maxLevel);
}

void IOView::drawLabel(QVector<Gate> &gates, int maxLevel)
{
    for(int i = 0; i < gates.count(); i++)
    {

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
    load->setGeometry(170, height - 150, 340, 80);
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

void IOView::drawLineBetweenP1P2(int x1, int y1, int x2, int y2, QGraphicsScene& scn, QPen& pen)
{
    int x3 = (x2-x1)/2 + x1;
    scn.addLine(x1, y1, x3, y1, pen);
    qDebug() << "drawed line from " << x1 <<";" <<y1 << " to " <<x3 <<";"<<y1;
    scn.addLine(x3, y1, x3, y2, pen);
    qDebug() << "drawed line from " << x3 <<";" <<y1 << " to " <<x3 <<";"<<y2;
    scn.addLine(x3, y2, x2, y2, pen);
    qDebug() << "drawed line from " << x3 <<";" <<y2 << " to " <<x2 <<";"<<y2;
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
