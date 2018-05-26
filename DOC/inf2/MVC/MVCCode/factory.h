#ifndef FACTORY_H
#define FACTORY_H

#include "data.h"
#include "logic.h"
#include "inputview.h"
#include "outputview.h"
#include "listview.h"

#define V1B
#define V1X

class Factory
{
public:
	Factory();
	~Factory();
	void build();
private:
	Data* data;
	Logic* logic;
    OutputView* v1a;
#ifdef V1X
    OutputView* v1x;
#endif
#ifdef V1B
    ListView* v1b;
#endif
    InputView* v2;
};

#endif // FACTORY_H
