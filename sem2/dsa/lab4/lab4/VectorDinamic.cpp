#include "VectorDinamic.h"
#include <stdexcept>

using namespace std;

void VectorDinamic::redim() {
	int NN = 2 * N;
	TElemV* w = new TElemV[NN];
	for (int i = 0; i < n; ++i)
		w[i] = v[i];
	delete[] v;
	N = NN;
	v = w;
}


VectorDinamic::VectorDinamic(int cp) : N(cp) {
	if (cp <= 0)
		throw runtime_error("Capacitatea trebuie sa fie mai mare ca 0");
	v = new TElemV[cp];
}



VectorDinamic::~VectorDinamic() {
	delete[] v;
}



int VectorDinamic::dim() const {
	return n;
}



TElemV VectorDinamic::element(int i) const {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	return v[i];
}



void VectorDinamic::adaugaSfarsit(TElemV e) {
	if (n == N)
		redim();
	v[n++] = e;
}


void VectorDinamic::adauga(int i, TElemV e) {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	TElemV last = v[n - 1];
	for (int j = n - 1; j > i; --j)
		v[j] = v[j - 1];
	adaugaSfarsit(last);
	v[i] = e;
}


TElemV VectorDinamic::modifica(int i, TElemV e) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElemV old = v[i];
	v[i] = e;
	return old;
}


TElemV VectorDinamic::sterge(int i) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElemV val = v[i];
	for (int j = i + 1; j < n; ++j)
		v[j - 1] = v[j];
	--n;
	return val;
}

void VectorDinamicLibere::redim() {
	int NN = 2 * N;
	TElemV2* w = new TElemV2[NN];
	for (int i = 0; i < n; ++i)
		w[i] = v[i];
	delete[] v;
	N = NN;
	v = w;
}


VectorDinamicLibere::VectorDinamicLibere(int cp) : N(cp) {
	if (cp <= 0)
		throw runtime_error("Capacitatea trebuie sa fie mai mare ca 0");
	v = new TElemV2[cp];
}



VectorDinamicLibere::~VectorDinamicLibere() {
	delete[] v;
}



int VectorDinamicLibere::dim() const {
	return n;
}



TElemV2 VectorDinamicLibere::element(int i) const {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	return v[i];
}



void VectorDinamicLibere::adaugaSfarsit(TElemV2 e) {
	if (n == N)
		redim();
	v[n++] = e;
}


void VectorDinamicLibere::adauga(int i, TElemV2 e) {
	if (i<0 || i>n)
		throw runtime_error("Index invalid");
	TElemV2 last = v[n - 1];
	for (int j = n - 1; j > i; --j)
		v[j] = v[j - 1];
	adaugaSfarsit(last);
	v[i] = e;
}


TElemV2 VectorDinamicLibere::modifica(int i, TElemV2 e) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElemV2 old = v[i];
	v[i] = e;
	return old;
}


TElemV2 VectorDinamicLibere::sterge(int i) {
	if (i < 0 || i >= n)
		throw runtime_error("Index invalid");
	TElemV2 val = v[i];
	for (int j = i + 1; j < n; ++j)
		v[j - 1] = v[j];
	--n;
	return val;
}
