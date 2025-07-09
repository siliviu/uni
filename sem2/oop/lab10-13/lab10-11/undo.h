#pragma once

#include "repo.h"
#include "activity.h"

class UndoAction {
protected:
	AbstractRepo<Activity>& r;
	UndoAction(AbstractRepo<Activity>& r_) :r(r_) {};
public:
	virtual ~UndoAction() = default;
	virtual void DoUndo() = 0;
};

class UndoAdd : public UndoAction {
	int position;
	void DoUndo() override { r.RemoveElement(position); };
public:
	UndoAdd(AbstractRepo<Activity>& r, int p) :position(p), UndoAction(r) {};
};

class UndoRemove : public UndoAction {
	int position;
	Activity a;
	void DoUndo() override { r.AddElement(a, position); };
public:
	UndoRemove(AbstractRepo<Activity>& r, int p, const Activity& _a) : a(_a), position(p), UndoAction(r) {};
};

class UndoModify : public UndoAction {
	int position;
	Activity a;
	void DoUndo() override { r.ModifyEement(position, a); };
public:
	UndoModify(AbstractRepo<Activity>& r, int p, const Activity& _a) : a(_a), position(p), UndoAction(r) {};
};

