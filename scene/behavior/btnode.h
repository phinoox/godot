#ifndef BTNODE_H
#define BTNODE_H

#include "scene/main/node.h"
#include "scene/main/scene_tree.h"
#include "btstrategy.h"
#include "BtSate.h"



class BtNode : public Node {
GDCLASS(BtNode, Node);
OBJ_CATEGORY("Behavior");


    public:
  enum BtNodeType {
	  BT_TYPE_NONE,
      BT_TYPE_SELECTOR,
      BT_TYPE_SEQUENCE,
      BT_TYPE_LEAF
  };



private:
  struct Data{
  BtNode* bt_parent;
  BtNode* bt_root;
  int current_running=0;
  Node* bt_owner;
//  Vector<BtNode*> children;
  BtNodeType node_type;
  BtState node_state;
  BtStrategy* strategy;

  } data;
  virtual BtState _process_bt(float delta);
protected:

static void _bind_methods();
void _notification(int p_what);
virtual void  add_child_notify(Node * p_child) override;
virtual void  remove_child_notify(Node * p_child) override;
virtual void _interrupt(String reason,Variant data);


public:
  void set_bt_root(BtNode* new_root);
  BtNode* get_bt_root() const;
  void set_bt_parent(BtNode* new_parent);
  BtNode* get_bt_parent() const;
  Node* get_bt_owner() const;
  int get_current_running() const;
  void set_current_running(int p_index);
  void set_type(BtNodeType nd_type);
  BtNodeType get_type() const;
  void set_state(BtState);
  BtState get_state() const;
  BtState process_bt(float delta);
  void interrupt(String reason,Variant msg_data=NULL);

  BtNode();
  ~BtNode();
};


#endif
