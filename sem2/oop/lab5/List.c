#pragma once

#include "List.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

List* createNewList(DestroyFct d, CopyFct c) {
	List* l = (List*)malloc(sizeof(List));
	l->capacitate = 2;
	l->lungime = 0;
	l->elems = malloc(l->capacitate * sizeof(ElemType));
	l->destroy = d;
	l->copy = c;
	return l;
}

void destroyList(List* l) {
	for (int i = 0; i < l->lungime; i++)
		l->destroy(l->elems[i]);
	free(l->elems);
	free(l);
}

ElemType get(List* l, int poz) {
	return l->elems[poz];
}

ElemType setElem(List* l, int poz, ElemType el) {
	ElemType oldElem = l->elems[poz];
	l->elems[poz] = el;

	return oldElem;
}

int size(List* l) {
	return l->lungime;
}

void add(List* l, ElemType el) {
	if (l->lungime == l->capacitate) {
		int newcapacitate = l->capacitate * 2;
		ElemType* aux_elems = malloc(sizeof(ElemType) * newcapacitate);
		for (int i = 0; i < l->lungime; i++) {
			aux_elems[i] = l->elems[i];
		}
		free(l->elems);
		l->elems = aux_elems;
		l->capacitate = newcapacitate;
	}
	l->elems[l->lungime] = el;
	l->lungime++;
}

ElemType delete(List* l, int poz) {
	ElemType el = l->elems[poz];
	for (int i = poz; i < l->lungime - 1; i++) {
		l->elems[i] = l->elems[i + 1];
	}
	l->lungime--;
	return el;
}

List* copyList(List* l) {
	List* copy_list = createNewList(l->destroy, l->copy);
	for (int i = 0; i < l->lungime; i++) {
		ElemType el = get(l, i);
		add(copy_list, l->copy(el));
	}
	return copy_list;
}

void TestcreateList() {
	List* l = createNewList(0, 0);
	assert(size(l) == 0);
	destroyList(l);

}
void TestIterate() {
	List* l = createNewList(destroyCost, copyCost);
	Cost* m1 = createCost(1, 50, "altele");
	Cost* m2 = createCost(2, 50, "telefon");
	Cost* m3 = createCost(3, 100, "imbracaminte");

	add(l, m1);
	add(l, m2);
	add(l, m3);

	assert(size(l) == 3);
	Cost m = *(Cost*)get(l, 0);

	assert(m.zi == 1);
	assert(m.suma == 50);
	assert(strcmp(m.tip, "altele") == 0);

	destroyList(l);
}

void TestCopy() {
	List* v1 = createNewList(destroyCost, copyCost);
	Cost* c1 = createCost(1, 50, "altele");
	Cost* c2 = createCost(2, 100, "telefon");
	add(v1, c1);
	add(v1, c2);

	assert(size(v1) == 2);
	List* v2 = copyList(v1);
	assert(size(v2) == 2);
	Cost m = *(Cost*)get(v2, 0);
	assert(strcmp(m.tip, "altele") == 0);

	destroyList(v1);
	destroyList(v2);

}
