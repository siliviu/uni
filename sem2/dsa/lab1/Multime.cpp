#include "Multime.h"
#include "IteratorMultime.h"
#include <iostream>

Multime::Multime() : v(1) {
}


bool Multime::adauga(TElem elem) {
	if (!cauta(elem)) {
		v.adaugaSfarsit(elem);
		return true;
	}
	return false;
}


bool Multime::sterge(TElem elem) {
	int n = v.dim();
	for (int i = 0; i < n; ++i)
		if (v.element(i) == elem) {
			v.sterge(i);
			return true;
		}
	return false;
}


bool Multime::cauta(TElem elem) const {
	auto it = v.iterator();
	for (it.prim(); it.valid(); it.urmator())
		if (it.element() == elem)
			return true;
	return false;
}


int Multime::dim() const {
	return v.dim();
}

bool Multime::vida() const {
	return dim() == 0;
}

int Multime::diferentaMaxMin() const {
	if (vida())
		return -1;
	int n = v.dim(), min = INT_MAX, max = INT_MIN;
	for (int i = 0; i < n; ++i) {
		if (v.element(i) < min)
			min = v.element(i);
		if (v.element(i) > max)
			max = v.element(i);
	}
	return max - min;
}


Multime::~Multime() {
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

