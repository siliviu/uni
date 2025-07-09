#include "Iterator.h"
#include "DO.h"
#include <iostream>
#include <cassert>
#include <exception>
using namespace std;

DO::DO(Relatie _r) : rr(_r) {
	for (int i = MAX - 1; i >= 0; --i)
		st.push(i);
}


int DO::minim(int root) const {
	while (t[root].left != -1)
		root = t[root].left;
	return root;
}

int DO::maxim(int root) const {
	while (t[root].right != -1)
		root = t[root].right;
	return root;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	int cur = root, last = -1;
	while (cur != -1) {
		int key = t[cur].key;
		if (equals(c, key)) {
			int old = t[cur].val;
			t[cur].val = v;
			return old;
		}
		last = cur;
		if (less(c, key))
			cur = t[cur].left;
		else
			cur = t[cur].right;
	}
	++sz;
	int id = st.pop();
	if (last != -1)
		(less(c, t[last].key) ? t[last].left : t[last].right) = id;
	else
		root = id;
	t[id] = { c,v };
	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	int cur = root;
	while (cur != -1) {
		int key = t[cur].key;
		if (equals(c, key))
			return t[cur].val;
		if (less(c, key))
			cur = t[cur].left;
		else
			cur = t[cur].right;
	}
	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	int cur = root, last = -1;
	while (cur != -1) {
		int key = t[cur].key;
		if (equals(c, key)) {
			int old = t[cur].val;
			if (t[cur].left == -1 || t[cur].right == -1) {
				--sz;
				int son = t[cur].left != -1 ? t[cur].left : t[cur].right;
				if (last == -1)
					root = son;
				else
					(t[last].left == cur ? t[last].left : t[last].right) = son;
				st.push(cur);
			}
			else {
				int succ = minim(t[cur].right);
				t[cur].val = t[succ].val;
				t[cur].key = t[succ].key;
				sterge(succ);
			}
			return old;
		}
		last = cur;
		if (less(c, key))
			cur = t[cur].left;
		else
			cur = t[cur].right;
	}
	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return sz;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	return !sz;
}

Iterator DO::iterator() const {
	return Iterator(*this);
}

int DO::diferentaValoareMaxMin() const {
	if (vid())
		return -1;
	int maxim = INT_MIN, minim = INT_MAX;
	for (auto it = iterator(); it.valid(); it.urmator()) {
		minim = min(minim, it.element().second);
		maxim = max(maxim, it.element().second);
	}
	return maxim - minim;
}

DO::~DO() {}