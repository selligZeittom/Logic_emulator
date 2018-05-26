#include "factory.h"

Factory::Factory()
{
    data = new Data();
    logic = new Logic();
    v1a = new OutputView(100,100,400,300,"Drawing Window");
#ifdef V1B
    v1b = new ListView(550,100,200,300,"List Window");
#endif
#ifdef V1X
    v1x = new OutputView(100,100,400,300,"Drawing Window");
#endif
    v2 = new InputView(100,450,400,50,"Command Window");
}

Factory::~Factory()
{
    delete data;
    delete logic;
    delete v1a;
#ifdef V1B
    delete v1b;
#endif
#ifdef V1X
    delete v1x;
#endif
    delete v2;
}

void Factory::build()
{
    logic->initRelations(data);
    v1a->initRelations(data, logic);
#ifdef V1B
    v1b->initRelations(data, logic);
#endif
#ifdef V1X
    v1x->initRelations(data, logic);
#endif
    v2->initRelations(data, logic);

    data->subscribe(v1a);
#ifdef V1B
    data->subscribe(v1b);
#endif
#ifdef V1X
    data->subscribe(v1x);
#endif
}
