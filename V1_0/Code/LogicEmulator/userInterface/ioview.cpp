#include "ioview.h"
#include "portui.h"

#define RELEASEs

IOView::IOView(QWidget *parent)
{
    this->thePortUI = NULL;

    //get the dimension of the screen
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect  screenGeometry = screen->geometry();
    this->height = screenGeometry.height()-35;
    this->width = screenGeometry.width();

    this->setWindowTitle("Logic Emulator V0.0");
    this->setVisible(true);
    this->showMaximized(); //full screen

    //used to set the appearance of qlabel
    this->styleSheetQLabel = "QLabel { background-color : white; border: 1px solid gray; border-radius: 10px; color : black; }";
}

//destroy the pointer at the end
IOView::~IOView()
{
    if(load)
    {
        delete load;
        load = NULL;
    }
    if(drawWindow)
    {
        delete drawWindow;
        drawWindow = NULL;
    }
    if(scnGates)
    {
        delete scnGates;
        scnGates = NULL;
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
    if(load)
    {
        delete load;
        load = NULL;
    }
    if(codeWindow)
    {
        delete codeWindow;
        codeWindow = NULL;
    }
    if(scnCode)
    {
        delete scnCode;
        scnCode = NULL;
    }
}

//make the global connections
void IOView::initRelations(PortUI *p1)
{
    this->thePortUI = p1;

    //initialize the objects on the screen
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

    //set the filter for only getting .json files
    QString filter = "File Description (*.json)";

    //get the opened file's path
    QString filePath =  QFileDialog::getOpenFileName(
                this,
                "Open Json file",
                QDir::homePath(), filter);
    return filePath;

#else
    return "C:/Users/Gilles Mottiez/Documents/HES/Informatique/Projet_inf2/Logic_emulator/JSON/TEST3_4l.json";
#endif
}

void IOView::drawGates(QVector<Gate *> &gates, int maxLevel)
{
    //clear the scene
    scnGates->clear();

    //store the number of item per level
    int itemPerLevel[maxLevel+1];
    for (int i = 0; i < maxLevel+1; ++i)
    {
        itemPerLevel[i] = 0;
    }

    //get the number of thoses items per level
    for(int i = 0; i < gates.count(); i++)
    {
        itemPerLevel[gates[i]->getLevel()]++; //incr the index corresponding to the level
    }
    int xOffset = 250;
    int yOffset = 150;


    //draw the pixmap of the gates, and the connections and set the coordinates
    for (int _level = 0; _level <= maxLevel; ++_level)
    {
        int _usedGates = 0; //needed because gates aren't stored by level
        for (int i = 0; i < gates.count(); ++i)
        {
            //do sth only when the level is corresponding
            if(gates[i]->getLevel() == _level)
            {
                //used to adapt the vertical gap between gates
                double ratio = 1;
                if(_level != 0)
                {
                    ratio = itemPerLevel[_level-1] / itemPerLevel[_level];
                }
                int x = xOffset * _level; //horizontal gap
                int y = 0;
                if(itemPerLevel[_level] != 1) //if there is more than one gate on this level
                {
                    y = yOffset * _usedGates * ratio + (_level) * yOffset/2;
                }
                else //for one gate per level
                {
                    y =  yOffset * (itemPerLevel[0]/2) - yOffset/2;
                }

                //create an item to draw the qpixmap of the gate
                QGraphicsPixmapItem* item = new QGraphicsPixmapItem();
                item->setPos(x, y);
                gates[i]->setXY(x, y); //used to store the coordinates for the next pins
                item->setPixmap(gates[i]->getQPixMap().scaled(80, 80));
                scnGates->addItem(item);

                //write the id of the gate
                QGraphicsTextItem* item2 = new QGraphicsTextItem();
                item2->setPos(x + 20, y + 30);
                item2->setPlainText(gates[i]->getID());
                this->scnGates->addItem(item2);

                //incr it because one gate has been used
                _usedGates++;
            }
        }
    }

    //next  : make the graphical connections between gates
    drawWires(gates, maxLevel);
}

//draw lines between gates
void IOView::drawWires(QVector<Gate*> &gates, int maxLevel)
{
    for (int i = 0; i < gates.count(); ++i)
    {
        int x1 = 0;
        int y1 = 0;

        int x2 = 0;
        int y2 = 0;

        QPen* pen;

        //logical inputs like 0 or 1
        if(gates[i]->getLevel() == 0)
        {
            for(int j = 0; j < gates[i]->getInputPins().count(); j++)
            {
                x1 = gates[i]->getInputPins()[j]->getX();
                y1 = gates[i]->getInputPins()[j]->getY();

                x2 = x1 - 50;
                y2 = y1;

                //if it's a 1 : green
                if(gates[i]->getInputPins()[j]->getState())
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
        if(gates[i]->getLevel() != maxLevel)
        {
            x1 = gates[i]->getOutputPin()->getX();
            y1 = gates[i]->getOutputPin()->getY();

            x2 = ((gates[i]->getOutputPin())->getConnectedPin())->getX();
            y2 = ((gates[i]->getOutputPin())->getConnectedPin())->getY();


            if(gates[i]->getOutputPin()->getState())
            {
                pen = new QPen(QColor(Qt::green))  ;
            }
            else
            {
                pen = new QPen(QColor(Qt::red))  ;
            }

            pen->setWidth(3);

            //use this fonction instead of scnGates->addLine(...) to get a better look
            drawLineBetweenP1P2(x1, y1, x2, y2, *scnGates, *pen);
        }
        else //at the end of the design
        {
            x1 = gates[i]->getOutputPin()->getX();
            y1 = gates[i]->getOutputPin()->getY();

            x2 = x1 + 50;
            y2 = y1;

            if(gates[i]->getOutputPin()->getState())
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
}

//used to display the text of the .json file
void IOView::onNewCode(QString labelCode)
{
    this->scnCode->clear();
    QGraphicsTextItem* item = new QGraphicsTextItem();
    item->setPlainText(labelCode);

    //set the text editable and selectable
    item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
    item ->setTextInteractionFlags(Qt::TextEditorInteraction);
    this->scnCode->addItem(item);
}

//used to display the .json file's name
void IOView::onNewFileName(QString filename)
{
    this->labelFileName->setText(filename);
}

//used to write the results
void IOView::onNewResults(QString results)
{
    this->labelResult->setText(results);
}

//clear the scenes
void IOView::onDeleteOldGatesAndCode()
{
    this->scnGates->clear();
    this->scnCode->clear();
}

//create and init the qpushbutton, qlabel, ...
void IOView::initGraphicalObject()
{
    this->load = new QPushButton(this);
    load->setGeometry(40, height - 150, 250, 80);
    load->setStyleSheet("QPushButton { background-color : rgb(110, 187, 177); border: 1px solid gray; border-radius: 10px; color : black; }");
    load->setText("Browse a file");

    this->check = new QPushButton(this);
    check->setGeometry(390, height - 150, 250, 80);
    check->setStyleSheet("QPushButton { background-color : rgb(253, 223, 171); border: 1px solid gray; border-radius: 10px; color : black; }");
    check->setText("Check modifications");

    this->drawWindow = new QGraphicsView(this);
    drawWindow->setGeometry(680, 40, GATES_QLABEL_W, GATES_QLABEL_H);
    drawWindow->setStyleSheet("QGraphicsView { background-color : white; border: 1px solid gray; border-radius: 10px; color : black; }");
    scnGates = new QGraphicsScene(drawWindow);
    drawWindow->setScene(scnGates);

    this->labelResult = new QLabel(this);
    labelResult->setGeometry(680, 680, RESULT_QLABEL_W, RESULT_QLABEL_H);
    labelResult->setStyleSheet(styleSheetQLabel);
    labelResult->setText("no results ...");

    this->labelFileName = new QLabel(this);
    labelFileName->setGeometry(40, 40, FILENAME_QLABEL_W, FILENAME_QLABEL_H);
    labelFileName->setStyleSheet(styleSheetQLabel);
    labelFileName->setText("no file loaded ...");

    this->codeWindow = new QGraphicsView(this);
    codeWindow->setGeometry(40, 140,CODE_QLABEL_W, CODE_QLABEL_H);
    codeWindow->setStyleSheet("QGraphicsView { background-color : white; border: 1px solid gray; border-radius: 10px; color : black; }");
    scnCode = new QGraphicsScene(codeWindow);
    codeWindow->setScene(scnCode);

    load->show();
    check->show();
    drawWindow->show();
    labelResult->show();
    labelFileName->show();
    codeWindow->show();

    //connect the buttons to the slot
    connect(this->load, SIGNAL(clicked(bool)), this, SLOT(loadButtonClicked()));
    connect(this->check, SIGNAL(clicked(bool)), this, SLOT(checkButtonClicked()));


}

//used to get some nice lines between gates
void IOView::drawLineBetweenP1P2(int x1, int y1, int x2, int y2, QGraphicsScene& scn, QPen& pen)
{
    int x3 = (x2-x1)/2 + x1;
    scn.addLine(x1, y1, x3, y1, pen);
    scn.addLine(x3, y1, x3, y2, pen);
    scn.addLine(x3, y2, x2, y2, pen);
}

//called when the button is clicked, forwards the path to the controller
void IOView::loadButtonClicked()
{
    QString path = getPath();
    qDebug() << "file browsed : " << path ;
    onButtonLoadPressed(path);

}

void IOView::checkButtonClicked()
{
    QString code;
    QGraphicsTextItem* item = (QGraphicsTextItem*)codeWindow->itemAt(40, 140);
    QTextDocument* doc = item->document();
    code = doc->toPlainText();
    qDebug() << code;
}

void IOView::onButtonLoadPressed(QString path)
{
    thePortUI->onButtonLoadPressed(path);
}
