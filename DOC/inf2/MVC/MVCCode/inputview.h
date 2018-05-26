#ifndef INPUTVIEW_H
#define INPUTVIEW_H

#include "view.h"
#include <QLineEdit>

class InputView : public View
{
	Q_OBJECT
public:
	InputView(int x, int y, int width, int heigth, QString title);


private:
	void setupUI();

private:
	QLineEdit* le;

private slots:
	void onCommandEntered();

};

#endif // INPUTVIEW_H
