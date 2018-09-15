#include "btnode.h"
#include "core/core_string_names.h"

#include "io/resource_loader.h"
#include "message_queue.h"
#include "print_string.h"

VARIANT_ENUM_CAST(BtNode::BtNodeState);
VARIANT_ENUM_CAST(BtNode::BtNodeType);

BtNode::BtNode(){

}

BtNode::~BtNode(){
    data.children.clear();
}



void BtNode::set_state(BtNodeState new_state){
    data.node_state=new_state;
}

BtNode::BtNodeState BtNode::get_state() const{
    return data.node_state;
}

void BtNode::set_name(StringName new_name){
    data.name=new_name;
}

StringName BtNode::get_name() const{
    return data.name;
}

void BtNode::set_parent(BtNode* new_parent){
    data.parent=new_parent;
}

BtNode* BtNode::get_parent() const{
   return data.parent;
}

void BtNode::set_root(BtNode* new_root){
    data.root=new_root;
}

BtNode* BtNode::get_root() const{
    return data.root;
}

void BtNode::set_type(BtNodeType new_type){
    data.node_type=new_type;
}

BtNode::BtNodeType BtNode::get_type() const {
    return data.node_type;
}




void BtNode::_bind_methods() {
    

	//ProjectSettings::get_singleton()->set_custom_property_info("node/name_casing", PropertyInfo(Variant::INT, "node/name_casing", PROPERTY_HINT_ENUM, "PascalCase,camelCase,snake_case"));
BIND_ENUM_CONSTANT(BT_TYPE_SELECTOR);
    BIND_ENUM_CONSTANT(BT_TYPE_SEQUENCE);
    BIND_ENUM_CONSTANT(BT_TYPE_DECORATOR);
    BIND_ENUM_CONSTANT(BT_TYPE_LEAF);
    BIND_ENUM_CONSTANT(BT_STATE_FAILURE);
    BIND_ENUM_CONSTANT(BT_STATE_PAUSED);
    BIND_ENUM_CONSTANT(BT_STATE_RUNNING);
    BIND_ENUM_CONSTANT(BT_STATE_SUCCESS);

	//ClassDB::bind_method(D_METHOD("add_child_below_node", "node", "child_node", "legible_unique_name"), &Node::add_child_below_node, DEFVAL(false));
    ADD_GROUP("Behavior", "");
	//ADD_PROPERTYNZ(PropertyInfo(Variant::TRANSFORM, "transform", PROPERTY_HINT_NONE, ""), "set_transform", "get_transform");
	ADD_PROPERTYNZ(PropertyInfo(Variant::INT, "node_type", PROPERTY_HINT_ENUM, "Selector,Sequence,Decorator,Leaf"), "set_type", "get_type");
    ADD_PROPERTYNZ(PropertyInfo(Variant::INT, "node_state", PROPERTY_HINT_ENUM, "Success,Failure,Running,Paused"), "set_state", "get_state");
    ADD_PROPERTYNZ(PropertyInfo(Variant::STRING, "name", PROPERTY_HINT_TYPE_STRING), "set_name", "get_name");
    ADD_PROPERTYNZ(PropertyInfo(Variant::OBJECT, "parent", PROPERTY_HINT_NONE), "set_parent", "get_parent");
    ADD_PROPERTYNZ(PropertyInfo(Variant::OBJECT, "root", PROPERTY_HINT_NONE), "set_root", "get_root");

    //
    ClassDB::bind_method(D_METHOD("get_root"), &BtNode::get_root);
    ClassDB::bind_method(D_METHOD("set_root","new_root"), &BtNode::set_root);
    ClassDB::bind_method(D_METHOD("get_parent"), &BtNode::get_parent);
    ClassDB::bind_method(D_METHOD("set_parent","new_parent"), &BtNode::set_parent);
    ClassDB::bind_method(D_METHOD("get_type"), &BtNode::get_type);
    ClassDB::bind_method(D_METHOD("set_type","new_type"), &BtNode::set_type);
    ClassDB::bind_method(D_METHOD("get_state"), &BtNode::get_state);
    ClassDB::bind_method(D_METHOD("set_state","new_state"), &BtNode::set_state);

    //BIND_CONSTANT(NOTIFICATION_TRANSFORM_CHANGED);
    
    //ADD_SIGNAL(MethodInfo("visibility_changed"));
}