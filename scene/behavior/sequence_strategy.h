#pragma once
#include "btstrategy.h"

class BtNode;
class SequenceStrategy : public BtStrategy{

protected:
virtual BtState _process(float delta);

};
