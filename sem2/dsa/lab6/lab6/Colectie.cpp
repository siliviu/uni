#include "Colectie.h"
#include "IteratorColectie.h"
#include <exception>
#include <iostream>

using namespace std;


Colectie::Colectie() {
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
	UpdateFree();
}


bool Colectie::sterge(TElem elem) {
	int key = hash(elem);
	if (a[key].freq == -1)
		return false;
	int last = key;
	for (int cur = key; cur != -1; cur = a[cur].next) {
		// added
		if (a[cur].val == elem) {
			if (a[cur].freq == 0)
				return false;
			--nr;
			--a[cur].freq;
			if (a[cur].freq == 0) {
				// delete;
			}
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
			return a[cur].freq > 0;
			//return true;
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


Colectie::~Colectie() {
}


