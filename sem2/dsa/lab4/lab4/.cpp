#include "VectorDinamic.h"
#include <stdexcept>

using namespace std;

template<class TElem>
void VectorDinamic<TElem>::redim() {
	int NN = 2 * N;
	TElem* w = new TElem[NN];
	for (int i = 0; i < n; ++i)
		w[i] = v[i];
	delete[] v;
	N = NN;
	v = w;
}

template<class TElem>
VectorDinamic<TElem>::VectorDinamic(int cp) : N(cp) {
	if (cp <= 0)
		throw runtime_error("Capacitatea trebuie sa fie mai mare ca 0");
	v = new TElem[cp];
}


template<class TElem>
VectorDinamic<TElem>::~VectorDinamic() {
	delete[] v;
}


template<class TElem>
int VectorDinamic<TElem>::dim() const {
	return n;
}


template<class TElem>
TElem VectorDinamic<TElem>::element(int i) const {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	return v[i];
}

template<class TElem>
void VectorDinamic<TElem>::adaugaSfarsit(TElem e) {
	if (n == N)
		redim();
	v[n++] = e;
}

template<class TElem>
void VectorDinamic<TElem>::adauga(int i, TElem e) {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	TElem last = v[n - 1];
	for (int j = n - 1; j > i; --j)
		v[j] = v[j - 1];
	adaugaSfarsit(last);
	v[i] = e;
}

template<class TElem>
TElem VectorDinamic<TElem>::modifica(int i, TElem e) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElem old = v[i];
	v[i] = e;
	return old;
}

template<class TElem>
TElem VectorDinamic<TElem>::sterge(int i) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElem val = v[i];
	for (int j = i + 1; j < n; ++j)
		v[j - 1] = v[j];
	--n;
	return val;
}

template<class TElem>
IteratorVectorDinamic VectorDinamic<TElem>::iterator() const {
	return IteratorVectorDinamic(*this);
}
