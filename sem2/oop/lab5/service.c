#pragma once

#include "service.h"
#include "Sort.h"
#include <assert.h>
#include <string.h>

int isEmpty(Service* s) {
	return size(s->costs) == 0;
}
Service createService() {
	Service s;
	s.costs = createNewList(destroyCost, copyCost);
	s.undo = createNewList(destroyList, copyList);
	return s;
}

void closeService(Service* S) {
	destroyList(S->costs);
	destroyList(S->undo);
}

int undo(Service* s) {
	if (size(s->undo) == 0)
		return 0;
	destroyList(s->costs);
	s->costs = get(s->undo, size(s->undo) - 1);
	delete(s->undo, size(s->undo) - 1);
	return 1;
}

int findCost(Service* s, int zi, char* tip) {
	int poz = -1;
	for (int i = 0; i < size(s->costs); i++) {
		Cost c = *(Cost*)get(s->costs, i);
		if (c.zi == zi && strcmp(c.tip, tip) == 0) {
			poz = i;
			break;
		}
	}
	return poz;
}

int addCost(Service* s, int zi, int suma, char* tip) {
	Cost* c = createCost(zi, suma, tip);
	int ok = valideazaCost(c);
	int poz = findCost(s, zi, tip);
	if (!ok || poz != -1) {
		destroyCost(c);
		return 0;
	}
	add(s->undo, copyList(s->costs));
	add(s->costs, c);
	return 1;
}

int deleteCost(Service* s, int zi, char* tip) {
	int poz = findCost(s, zi, tip);
	if (poz != -1) {
		add(s->undo, copyList(s->costs));
		Cost* c = delete(s->costs, poz);
		destroyCost(c);
	}
	else
		return 0;
	return 1;
}

int modifyCost(Service* s, int zi, int suma, char* tip) {
	int poz = findCost(s, zi, tip);
	if (poz != -1) {
		add(s->undo, copyList(s->costs));
		Cost* newc = createCost(zi, suma, tip);
		Cost* c = get(s->costs, poz);
		destroyCost(c);
		setElem(s->costs, poz, newc);

		return 1;
	}
	return 0;
}

int comp_suma(void* c1, void* c2) {
	return ((Cost*)c1)->suma > ((Cost*)c2)->suma;
}

int comp_tip(void* c1, void* c2) {
	return strcmp(((Cost*)c1)->tip, ((Cost*)c2)->tip) > 0;
}

List* sorting_suma(Service* s) {
	List* sortedlist = copyList(s->costs);
	sort(sortedlist, comp_suma);
	return sortedlist;
}

List* sorting_tip(Service* s) {
	List* sortedlist = copyList(s->costs);
	sort(sortedlist, comp_tip);
	return sortedlist;
}

void TestfindService() {
	Service s = createService();

	int ok1 = addCost(&s, 1, 50, "altele");
	assert(ok1 == 1);

	int ok2 = addCost(&s, 2, 60, "telefon");
	assert(ok2 == 1);

	assert(size(s.costs) == 2);

	int poz1 = findCost(&s, 2, "telefon");
	assert(poz1 == 1);

	int poz2 = findCost(&s, 1, "telefon");
	assert(poz2 == -1);

	closeService(&s);

}

void TestaddService() {
	Service s = createService();
	assert(isEmpty(&s));

	int successful1 = addCost(&s, 1, 50, "altele");
	assert(successful1 == 1);

	int successful2 = addCost(&s, -1, -1, "a");
	assert(successful2 == 0);

	assert(size(s.costs) == 1);
	Cost* m = get(s.costs, 0);

	assert(strcmp(m->tip, "altele") == 0);
	assert(m->zi == 1);
	assert(m->suma == 50);
	closeService(&s);

}

void TestdeleteService() {
	Service s = createService();
	int ok1 = addCost(&s, 1, 50, "altele");
	assert(ok1 == 1);

	int ok2 = addCost(&s, 2, 60, "telefon");
	assert(ok2 == 1);

	assert(size(s.costs) == 2);

	int ok3 = deleteCost(&s, 3, "imbracaminte");
	assert(ok3 == 0);

	int ok4 = deleteCost(&s, 1, "altele");
	assert(ok4 == 1);

	assert(size(s.costs) == 1);

	int ok5 = findCost(&s, 2, "telefon");
	assert(ok5 == 0);

	closeService(&s);
}

void TestmodifyService() {
	Service s = createService();

	int ok1 = addCost(&s, 1, 50, "altele");
	assert(ok1 == 1);

	int ok2 = addCost(&s, 2, 60, "telefon");
	assert(ok2 == 1);

	assert(size(s.costs) == 2);

	int ok3 = modifyCost(&s, 1, 60, "altele");
	assert(ok3 == 1);

	int ok4 = modifyCost(&s, 2, 60, "altele");
	assert(ok4 == 0);

	closeService(&s);
}

void TestsortingService() {
	Service s = createService();

	int ok1 = addCost(&s, 1, 4, "mancare");
	assert(ok1 == 1);

	int ok2 = addCost(&s, 2, 3, "transport");
	assert(ok2 == 1);

	int ok3 = addCost(&s, 3, 2, "altele");
	assert(ok3 == 1);

	int ok4 = addCost(&s, 4, 1, "telefon");
	assert(ok4 == 1);

	assert(size(s.costs) == 4);

	List* sortedlist1 = sorting_suma(&s);
	assert(((Cost*)get(sortedlist1, 0))->suma == 1);
	assert(((Cost*)get(sortedlist1, 1))->suma == 2);
	assert(((Cost*)get(sortedlist1, 2))->suma == 3);
	assert(((Cost*)get(sortedlist1, 3))->suma == 4);

	destroyList(sortedlist1);

	List* sortedlist2 = sorting_tip(&s);
	assert(strcmp(((Cost*)get(sortedlist2, 0))->tip, "altele") == 0);
	assert(strcmp(((Cost*)get(sortedlist2, 1))->tip, "mancare") == 0);
	assert(strcmp(((Cost*)get(sortedlist2, 2))->tip, "telefon") == 0);
	assert(strcmp(((Cost*)get(sortedlist2, 3))->tip, "transport") == 0);

	destroyList(sortedlist2);
	closeService(&s);
}

void TestundoService() {
	Service s = createService();
	addCost(&s, 1, 2, "altele");
	addCost(&s, 2, 3, "altele");
	assert(size(s.costs) == 2);
	assert(undo(&s));
	assert(size(s.costs) == 1);
	assert(((Cost*)get(s.costs, 0))->suma == 2);
	modifyCost(&s, 1, 5, "altele");
	assert(((Cost*)get(s.costs, 0))->suma == 5);
	assert(undo(&s));
	assert(((Cost*)get(s.costs, 0))->suma == 2);
	assert(size(s.costs) == 1);
	deleteCost(&s, 1, "altele");
	assert(isEmpty(&s));
	assert(undo(&s));
	assert(undo(&s));
	assert(!undo(&s));
	closeService(&s);
}