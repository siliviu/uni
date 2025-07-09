#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


int Colectie::hash(TElem x) const {
	return (unsigned)(2654435761LL * x) >> (32 - MAX_POW);
}
void Colectie::DeleteNode(int pos, int before) {
	int last = pos;
	for (int cur = a[pos].next; cur != -1; cur = a[cur].next) {
		if (hash(a[cur].val) == pos) {
			a[pos].val = a[cur].val;
			a[pos].freq = a[cur].freq;
			DeleteNode(cur, last);
			return;
		}
		last = cur;
	}
	if (before != -1) {
		a[before].next = a[pos].next;
		if (a[pos].next != -1)
			a[a[pos].next].prev = before;
	}
	if (pos < free)
		free = pos;
	a[pos].freq = a[pos].next = a[pos].prev = -1;
}
void Colectie::UpdateFree() {
	while (free < MAX_SIZE && a[free].freq != -1)
		++free;
}

void Colectie::adauga(TElem elem) {
	++nr;
	int key = hash(elem);
	// not added already + array empty at key
	if (a[key].freq == -1) {
		a[key].val = elem;
		a[key].freq = 1;
		UpdateFree();
		return;
	}
	// ? added + not empty at key
	int last = key;
	for (int cur = key; cur != -1; cur = a[cur].next) {
		// added
		if (a[cur].val == elem) {
			++a[cur].freq;
			return;
		}
		last = cur;
	}
	// not added
	a[free].val = elem;
	a[free].freq = 1;
	a[last].next = free;
	a[free].prev = last;
	UpdateFree();
}


bool Colectie::sterge(TElem elem) {
	int key = hash(elem);
	if (a[key].freq == -1)
		return false;
	int last = -1;
	for (int cur = key; cur != -1; cur = a[cur].next) {
		// added
		if (a[cur].val == elem) {
			--nr;
			--a[cur].freq;
			if (a[cur].freq == 0)
				DeleteNode(cur, a[cur].prev);
			return true;
		}
		last = cur;
	}
	return false;
}


bool Colectie::cauta(TElem elem) const {
	int key = hash(elem);
	if (a[key].freq == -1)
		return false;
	for (int cur = key; cur != -1; cur = a[cur].next)
		if (a[cur].val == elem)
			return true;
	return false;
}

int Colectie::nrAparitii(TElem elem) const {
	int key = hash(elem);
	if (a[key].freq == -1)
		return 0;
	for (int cur = key; cur != -1; cur = a[cur].next)
		if (a[cur].val == elem)
			return a[cur].freq;
	return 0;
}


int Colectie::dim() const {
	return nr;
}


bool Colectie::vida() const {
	return nr == 0;
}

IteratorColectie Colectie::iterator() const {
	return IteratorColectie(*this);
}