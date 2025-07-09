#include "Matrice.h"

#include <exception>
#include <iostream>

using namespace std;



void Matrice::AddList(TElemL e) {
	if (l.dim() == 0)
		l.adaugaSfarsit(v.dim()), v.adaugaSfarsit(make_pair(make_tuple(0, 0, 0), -1));
	int available = l.element(l.dim() - 1);
	l.sterge(l.dim() - 1);
	v.modifica(available, make_pair(e, first));
	first = available;
}

void Matrice::RemoveList(int posbefore) {
	if (posbefore == -1) {
		first = v.element(first).second;
		l.adaugaSfarsit(first);
		return;
	}
	int poscur = v.element(posbefore).second;
	auto before = v.element(posbefore), cur = v.element(poscur);
	before.second = cur.second;
	v.modifica(posbefore, before);
	l.adaugaSfarsit(poscur);
}

Matrice::Matrice(int _n, int _m) : n(_n), m(_m), first(-1), v(4), l(4) {}

int Matrice::nrLinii() const {
	return n;
}


int Matrice::nrColoane() const {
	return m;
}


TElem Matrice::element(int i, int j) const {
	if (i < 0 || j < 0 || i >= n || j >= m)
		throw std::exception("Pozitie invalida");
	if (v.dim() != 0)
		for (int cur = first; cur != -1; cur = v.element(cur).second) {
			auto [x, y, z] = v.element(cur).first;
			if (x == i && y == j)
				return z;
		}
	return NULL_TELEMENT;
}


TElem Matrice::modifica(int i, int j, TElem e) {
	if (i < 0 || j < 0 || i >= n || j >= m)
		throw std::exception("Pozitie invalida");
	int last = -1;
	if (v.dim() != 0)
		for (int cur = first; cur != -1; cur = v.element(cur).second) {
			auto [x, y, z] = v.element(cur).first;
			if (x == i && y == j) {
				if (e == NULL_TELEMENT)
					RemoveList(last);
				else {
					TElemV temp = v.element(cur);
					get<2>(temp.first) = e;
					v.modifica(cur, temp);
				}
				return z;
			}
			last = cur;
		}
	AddList(make_tuple(i, j, e));
	return NULL_TELEMENT;
}

int Matrice::valoareMaxima() const {
	int ans = INT_MIN;
	if (v.dim() != 0) {
		for (int cur = first; cur != -1; cur = v.element(cur).second) {
			auto [x, y, z] = v.element(cur).first;
			ans = max(ans, z);
		}
		return ans;
	}
	return NULL_TELEMENT;
}