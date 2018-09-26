#include "btstrategy.h"
#include "btnode.h"

BtState BtStrategy::process(float delta)
{

   return	_process(delta);
}

void BtStrategy::init(BtNode* owner)
{

	this->owner=owner;
}



BtStrategy::BtStrategy()
{

}

void BtStrategy::_on_init()
{
}

BtState BtStrategy::_process(float delta)
{
	return BtState::BT_STATE_SUCCESS;
}


BtNode * BtStrategy::get_owner() const
{

	return owner;
}

BtStrategy::~BtStrategy()
{


}

int BtStrategy::get_current_child_index()
{
return owner->get_current_running();

}

void BtStrategy::set_current_child(int child_index)
{
	owner->set_current_running(child_index);;

}

