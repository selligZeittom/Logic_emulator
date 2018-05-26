#ifndef LOGIC_H
#define LOGIC_H

#include "data.h"
#include <QString>

class Logic
{
public:
	Logic();
	void initRelations(Data* d);
	void onInput(QString data);
private:
	Data* pData;
};

#endif // LOGIC_H
