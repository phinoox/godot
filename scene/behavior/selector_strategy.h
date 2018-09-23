#ifndef SELECTOR_STRATEGY_H
#define SELECTOR_STRATEGY_H
#include "btstrategy.h"


class SelectorStrategy : public BtStrategy{

protected:
virtual BtState _process(float delta);

};

#endif
