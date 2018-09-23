#pragma once
#include "btstrategy.h"


class DecoratorStrategy : public BtStrategy{

protected:
virtual BtState _process(float delta);

};
