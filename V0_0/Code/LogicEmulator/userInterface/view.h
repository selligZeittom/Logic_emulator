#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>

#include "interfaces/iviewupdate.h"

class OutputView;
class PortUI;


class View : public QWidget, public IViewUpdate
{

    Q_OBJECT

public:
    explicit View(QWidget* parent = 0);
    virtual ~View();
    void initRelations(OutputView* p1, PortUI* p2);
    int getWidth() const;
    int getHeight() const;

private:
    OutputView* outputView;
    PortUI* thePortUI;
    int width;
    int height;

    // IViewUpdate interface
public:
    virtual void onButtonLoadPressed(QString path);
    virtual void onPathSelected();
};

#endif // VIEW_H
