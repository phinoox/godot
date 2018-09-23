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
	if (get_script_instance()) {

				Variant time = get_process_delta_time();
				String name=get_name();
				int res=get_script_instance()->call(SceneStringNames::get_singleton()->process_bt, time);
				print_line(name+",state:"+String::num(res));
				return (BtState)res;
			}
	if ( data.bt_root==this&&data.strategy!=NULL )
            return data.strategy->process ( delta );
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
    BIND_ENUM_CONSTANT ( BT_TYPE_DECORATOR );
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
	//ClassDB::add_virtual_method("process_bt",MethodInfo("delta" ), &BtNode::process_bt );
	//ClassDB::add_virtual_method(MethodInfo("process_bt", PropertyInfo(Variant::REAL, "delta")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::INT,"BtState",PROPERTY_HINT_ENUM,"Initial,Success,Running,Failure,Paused"), "process_bt", PropertyInfo(Variant::REAL, "delta")));


    //ClassDB::bind_method(D_METHOD("add_child_below_node", "node", "child_node", "legible_unique_name"), &Node::add_child_below_node, DEFVAL(false));
    ADD_GROUP ( "Behavior", "" );
    //ADD_PROPERTYNZ(PropertyInfo(Variant::TRANSFORM, "transform", PROPERTY_HINT_NONE, ""), "set_transform", "get_transform");
    ADD_PROPERTYNZ ( PropertyInfo ( Variant::INT, "node_type", PROPERTY_HINT_ENUM, "None,Selector,Sequence,Decorator,Leaf" ), "set_type", "get_type" );
    //ADD_PROPERTYNZ ( PropertyInfo ( Variant::INT, "node_state", PROPERTY_HINT_ENUM, "Success,Failure,Running,Paused,Initial" ), "set_state", "get_state" );

    //ADD_PROPERTYNZ(PropertyInfo(Variant::OBJECT, "root", PROPERTY_HINT_NONE), "set_root", "get_root");


    //BIND_CONSTANT(NOTIFICATION_TRANSFORM_CHANGED);

    //ADD_SIGNAL(MethodInfo("visibility_changed"));
}
