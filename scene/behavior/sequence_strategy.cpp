#include "sequence_strategy.h"
#include "btnode.h"

BtState SequenceStrategy::_process(float delta)
{

	BtNode* owner = get_owner();
	if(!owner)
		return BtState::BT_STATE_FAILURE;
	for(int i=get_current_child_index();i<owner->get_child_count();i++){
		set_current_child(i);
		BtNode* child = Object::cast_to<BtNode>(owner->get_child(i));
		BtState child_state= child->process_bt(delta);

		switch (child_state){
			case BtState::BT_STATE_SUCCESS:continue;break;
			case BtState::BT_STATE_RUNNING:return BtState::BT_STATE_RUNNING;
			case BtState::BT_STATE_FAILURE:set_current_child(0);return BtState::BT_STATE_FAILURE;


		}
	}
		print_line("finished sequence");
		//resetting tree and return SUCCESS, cause no child has returned failure
		set_current_child(0);
		return BtState::BT_STATE_SUCCESS;


}

