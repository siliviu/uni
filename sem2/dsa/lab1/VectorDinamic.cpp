#include "VectorDinamic.h"
#include <stdexcept>
#include "IteratorVectorDinamic.h"

using namespace std;

void VectorDinamic::redim() {
	int NN = 2 * N;
	TElem* w = new TElem[NN];
	for (int i = 0; i < n; ++i)
		w[i] = v[i];
	delete[] v;
	N = NN;
	v = w;
}


VectorDinamic::VectorDinamic(int cp) : N(cp) {
	if (cp <= 0)
		throw runtime_error("Capacitatea trebuie sa fie mai mare ca 0");
	v = new TElem[cp];
}



VectorDinamic::~VectorDinamic() {
	delete[] v;
}



int VectorDinamic::dim() const {
	return n;
}



TElem VectorDinamic::element(int i) const {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	return v[i];
}



void VectorDinamic::adaugaSfarsit(TElem e) {
	if (n == N)
		redim();
	v[n++] = e;
}


void VectorDinamic::adauga(int i, TElem e) {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	TElem last = v[n - 1];
	for (int j = n - 1; j > i; --j)
		v[j] = v[j - 1];
	adaugaSfarsit(last);
	v[i] = e;
}


TElem VectorDinamic::modifica(int i, TElem e) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElem old = v[i];
	v[i] = e;
	return old;
}


TElem VectorDinamic::sterge(int i) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElem val = v[i];
	for (int j = i + 1; j < n; ++j)
		v[j - 1] = v[j];
	--n;
	return val;
}

IteratorVectorDinamic VectorDinamic::iterator() const {
	return IteratorVectorDinamic(*this);
}
