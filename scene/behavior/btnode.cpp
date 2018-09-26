#include "btnode.h"
#include "core/core_string_names.h"

#include "io/resource_loader.h"
#include "message_queue.h"
#include "print_string.h"
#include "engine.h"

#include "selector_strategy.h"
#include "decorator_strategy.h"
#include "sequence_strategy.h"
#include "scene/scene_string_names.h"

VARIANT_ENUM_CAST ( BtState );
VARIANT_ENUM_CAST ( BtNode::BtNodeType );

BtNode::BtNode()
{

    data.bt_root=NULL;
    data.bt_owner=NULL;
    data.bt_parent=NULL;
    data.strategy=NULL;
    data.node_state=BtState::BT_STATE_INITIAL;
    data.node_type=BtNodeType::BT_TYPE_NONE;
}

BtNode::~BtNode()
{
    //data.children.clear();
}

void BtNode::add_child_notify ( Node* p_child )
{
    /*if(data.root==NULL){
    	set_root(this);
    	this->set_name("BtRoot");
    }*/
    BtNode* child=Object::cast_to<BtNode> ( p_child );
    if ( !child )
        remove_child ( p_child );
}

void BtNode::remove_child_notify ( Node* p_child )
{
}

BtState BtNode::process_bt(float delta)
{
	BtState nstate=BtState::BT_STATE_INITIAL;
	if ( data.strategy!=NULL ){
           nstate=data.strategy->process ( delta );
	}
	//nstate= _process_bt(delta);

	if (get_script_instance() && get_script_instance()->has_method(SceneStringNames::get_singleton()->process_bt))  {

				Variant time = get_process_delta_time();
				String name=get_name();
				int res= get_script_instance()->call(SceneStringNames::get_singleton()->process_bt, time);
				nstate= (BtState)res;

			}


	set_state(nstate);
	return nstate;
}

void BtNode::interrupt(String reason, Variant msg_data)
{

	if (get_script_instance() && get_script_instance()->has_method(SceneStringNames::get_singleton()->_interrupt))  {

		get_script_instance()->call(SceneStringNames::get_singleton()->_interrupt, reason,msg_data);
	}
for(int i=0;i<get_child_count();i++){

    _interrupt(reason,msg_data);
	Object::cast_to<BtNode>(get_child(i))->interrupt(reason,msg_data);
}

}

void BtNode::_interrupt(String reason, Variant data)
{
}

int BtNode::get_current_running() const
{
return data.current_running;

}
void BtNode::set_current_running(int p_index)
{
	data.current_running=p_index;
}





BtState  BtNode::_process_bt(float delta)
{
	return BtState::BT_STATE_SUCCESS;
}





void BtNode::set_state ( BtState new_state )
{
    data.node_state=new_state;
}

BtState BtNode::get_state() const
{
    return data.node_state;
}


void BtNode::set_type ( BtNodeType new_type )
{


	if(data.node_type==new_type)
		return;
    data.node_type=new_type;
    switch ( new_type ) {
	case BT_TYPE_LEAF:
    case BT_TYPE_NONE:{
        data.strategy=NULL;
        break;
	}
	case BT_TYPE_SELECTOR:{
	data.strategy=new SelectorStrategy();
	break;
	}
    case BT_TYPE_SEQUENCE:{
	data.strategy=new SequenceStrategy();
	break;
	}
    }
    if(data.strategy)
		data.strategy->init(this);

}

BtNode::BtNodeType BtNode::get_type() const
{
    return data.node_type;
}




void BtNode::set_bt_root ( BtNode* new_root )
{
    ERR_FAIL_NULL ( new_root );

    data.bt_root=new_root;
}

BtNode* BtNode::get_bt_root() const
{
    return data.bt_root;
}

void BtNode::set_bt_parent ( BtNode* new_parent )
{
    ERR_FAIL_NULL ( new_parent );

    data.bt_parent=new_parent;
}

BtNode* BtNode::get_bt_parent() const
{
    return data.bt_parent;
}

Node * BtNode::get_bt_owner() const
{
    return data.bt_owner;
}



void BtNode::_notification ( int p_what )
{
	if (Engine::get_singleton()->is_editor_hint())
		return;
    switch ( p_what ) {
    case NOTIFICATION_ENTER_TREE: {

        Node *p = get_parent();
        if ( p ) {
            BtNode* bt_parent	 = Object::cast_to<BtNode> ( p );
            if ( !bt_parent ) {
                data.bt_owner=p;
                data.bt_root=this;
				set_process(true);
            } else {
                data.bt_parent=bt_parent;
                data.bt_root=bt_parent->data.bt_root;
            }
        }



    }
    break;
    case NOTIFICATION_PROCESS: {
		process_bt(get_process_delta_time());
        break;
    }
    }
}





void BtNode::_bind_methods()
{


    //ProjectSettings::get_singleton()->set_custom_property_info("node/name_casing", PropertyInfo(Variant::INT, "node/name_casing", PROPERTY_HINT_ENUM, "PascalCase,camelCase,snake_case"));
    BIND_ENUM_CONSTANT ( BT_TYPE_NONE );
	BIND_ENUM_CONSTANT ( BT_TYPE_SELECTOR );
    BIND_ENUM_CONSTANT ( BT_TYPE_SEQUENCE );
    BIND_ENUM_CONSTANT ( BT_TYPE_LEAF );

    BIND_ENUM_CONSTANT ( BT_STATE_FAILURE );
    BIND_ENUM_CONSTANT ( BT_STATE_PAUSED );
    BIND_ENUM_CONSTANT ( BT_STATE_RUNNING );
    BIND_ENUM_CONSTANT ( BT_STATE_SUCCESS );
    BIND_ENUM_CONSTANT ( BT_STATE_INITIAL );

    //
    ClassDB::bind_method ( D_METHOD ( "get_bt_root" ), &BtNode::get_bt_root );
    // ClassDB::bind_method(D_METHOD("set_bt_root","new_root"), &BtNode::set_bt_root);
    ClassDB::bind_method ( D_METHOD ( "get_type" ), &BtNode::get_type );
    ClassDB::bind_method ( D_METHOD ( "set_type","new_type" ), &BtNode::set_type );
    ClassDB::bind_method ( D_METHOD ( "get_state" ), &BtNode::get_state );
    ClassDB::bind_method ( D_METHOD ( "set_state","new_state" ), &BtNode::set_state );
	ClassDB::bind_method ( D_METHOD ( "interrupt","reason","msg_data" ), &BtNode::interrupt );
	ClassDB::bind_method ( D_METHOD ( "set_current_running","index" ), &BtNode::set_current_running );
    ClassDB::bind_method ( D_METHOD ( "get_current_running" ), &BtNode::get_current_running );

	//ClassDB::add_virtual_method("process_bt",MethodInfo("delta" ), &BtNode::process_bt );
	//ClassDB::add_virtual_method(MethodInfo("process_bt", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo(PropertyInfo("BtState"), "_process_bt", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo("_interrupt", PropertyInfo(Variant::STRING, "reason"),PropertyInfo(Variant::OBJECT,"msg_data")));


    //ClassDB::bind_method(D_METHOD("add_child_below_node", "node", "child_node", "legible_unique_name"), &Node::add_child_below_node, DEFVAL(false));
    ADD_GROUP ( "Behavior", "" );
    //ADD_PROPERTYNZ(PropertyInfo(Variant::TRANSFORM, "transform", PROPERTY_HINT_NONE, ""), "set_transform", "get_transform");
    ADD_PROPERTYNZ ( PropertyInfo ( Variant::INT, "node_type", PROPERTY_HINT_ENUM, "None,Selector,Sequence,Leaf" ), "set_type", "get_type" );
    ADD_PROPERTYNZ ( PropertyInfo ( Variant::INT, "node_state", PROPERTY_HINT_ENUM, "Initial,Success,Running,Failure,Paused" ), "set_state", "get_state" );
	ADD_PROPERTYNZ ( PropertyInfo ( Variant::INT, "current_running", PROPERTY_HINT_NONE ), "set_current_running", "get_current_running" );

    //ADD_PROPERTYNZ(PropertyInfo(Variant::OBJECT, "root", PROPERTY_HINT_NONE), "set_root", "get_root");


    //BIND_CONSTANT(NOTIFICATION_TRANSFORM_CHANGED);

    //ADD_SIGNAL(MethodInfo("visibility_changed"));
}
