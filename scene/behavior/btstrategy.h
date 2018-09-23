#ifndef BTSTRATEGY_H
#define BTSTRATEGY_H

#include "class_db.h"
#include "map.h"
#include "object.h"
#include "BtSate.h"

class BtNode;
class BtStrategy : public Object{


private:
BtNode* owner;
int current_child=0;

protected:
	virtual BtState _process(float delta);
	BtNode* get_owner() const;
	virtual void _on_init();
public:
	void init(BtNode* owner);
    BtState process(float delta);
	void set_current_child(int child_index);
	int get_current_child_index();
    BtStrategy();
	~BtStrategy();

};


#endif
