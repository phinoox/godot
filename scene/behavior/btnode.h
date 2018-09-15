#ifndef BTNODE_H
#define BTNODE_H

#include "class_db.h"
#include "map.h"
#include "node_path.h"
#include "object.h"
#include "project_settings.h"
#include "scene/main/scene_tree.h"
#include "btstrategy.h"
#include "script_language.h"


class BtNode : public Object{
GDCLASS(BtNode, Object);
	OBJ_CATEGORY("Behavior");

    public:
  enum BtNodeType {
      BT_TYPE_SELECTOR,
      BT_TYPE_SEQUENCE,
      BT_TYPE_DECORATOR,
      BT_TYPE_LEAF
  };

  enum BtNodeState{
      BT_STATE_SUCCESS,
      BT_STATE_RUNNING,
      BT_STATE_FAILURE,
      BT_STATE_PAUSED
  };

private:
  struct Data{
  BtNode* parent;
  BtNode* root;
  Vector<BtNode*> children;
  BtNodeType node_type;
  BtNodeState node_state;
  BtStrategy strategy;
  StringName name;
  } data;
protected:

static void _bind_methods();

public:
  void set_parent(BtNode* new_parent);
  BtNode* get_parent() const;
  void set_root(BtNode* new_root); 
  BtNode* get_root() const;
  void set_type(BtNodeType nd_type);
  BtNodeType get_type() const;
  void set_state(BtNodeState);
  BtNodeState get_state() const;
  void set_name(StringName name);
  StringName get_name() const;
  BtNode();
  ~BtNode();
};


#endif