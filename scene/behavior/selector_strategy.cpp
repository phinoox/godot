#include "selector_strategy.h"
#include "btnode.h"

BtState SelectorStrategy::_process(float delta)
{

	BtNode* owner = get_owner();
	if(!owner)
		return BtState::BT_STATE_FAILURE;
	for(int i=get_current_child_index();i<owner->get_child_count();i++){

		BtNode* child = Object::cast_to<BtNode>(owner->get_child(i));
		BtState child_state= child->process_bt(delta);
		switch (child_state){
			case BtState::BT_STATE_SUCCESS:return BtState::BT_STATE_SUCCESS;
			case BtState::BT_STATE_RUNNING:set_current_child(i);return BtState::BT_STATE_RUNNING;
			case BtState::BT_STATE_FAILURE:continue;


		}
		//resetting tree and return failure, if no child succeeded
		set_current_child(0);
		return BtState::BT_STATE_FAILURE;

	}
}

