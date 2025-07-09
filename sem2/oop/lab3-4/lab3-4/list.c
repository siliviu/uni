#include "list.h"


void ResizeList(List* l) {
	Transaction* v = (Transaction*)malloc(sizeof(Transaction) * (l->capacity *= 2));
	for (int i = 0; i < l->length; ++i)
		v[i] = l->v[i];
	free(l->v);
	l->v = v;
}

List CreateList() {
	List l;
	l.length = 0;
	l.capacity = 1;
	l.v = (Transaction*)malloc(sizeof(Transaction));
	ResizeList(&l);
	return l;
}

void AddListTransaction(List* l, Transaction e) {
	if (l->length == l->capacity)
		ResizeList(l);
	l->v[l->length++] = e;
}

void ModifyListTransaction(List* l, int pos, Transaction e) {
	DeleteTransaction(&(l->v[pos]));
	l->v[pos] = e;
}

void DeleteListTransaction(List* l, int pos) {
	DeleteTransaction(&(l->v[pos]));
	for (int i = pos; i < l->length; ++i)
		l->v[i] = l->v[i + 1];
	--l->length;
}

Transaction* GetListElement(List* l, int pos) {
	return &(l->v[pos]);
}

int GetListLength(List* l) {
	return l->length;
}


int ValidatePosition(List* l, int pos) {
	return pos >= 0 && pos < l->length;
}

void DeleteList(List* l) {
	for (int i = 0; i < l->length; ++i)
		DeleteTransaction(&(l->v[i]));
	free(l->v);
}

List CopyList(List* l) {
	List r;
	r.length = l->length;
	r.capacity = l->capacity;
	r.v = (Transaction*)malloc(r.capacity * sizeof(Transaction));
	for (int i = 0; i < r.length; ++i)
		r.v[i] = CopyTransaction(&(l->v[i]));
	return r;
}