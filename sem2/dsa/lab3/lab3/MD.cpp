#include "MD.h"
#include "IteratorMD.h"
#include <exception>
#include <iostream>
#include <cassert>

using namespace std;


MD::MD() {
}


void MD::adauga(TCheie c, TValoare v) {
	++size;
	if (!root) {
		root = new node();
		root->prev = 0;
		root->next = 0;
		root->a = { c,v };
		return;
	}
	node* n = new node();
	n->a = { c,v };
	n->prev = 0;
	n->next = root;
	root->prev = n;
	root = n;
}


bool MD::sterge(TCheie c, TValoare v) {
	for (node* cur = root; cur; cur = cur->next) {
		if (cur->a == make_pair(c, v)) {
			node* p = cur->prev, * n = cur->next;
			if (p)
				p->next = n;
			else
				root = n;
			if (n)
				n->prev = p;
			--size;	
			delete cur;
			return true;
		}
	}
	return false;
}


vector<TValoare> MD::cauta(TCheie c) const {
	vector<TValoare> ans;
	int it = 0;
	for (node* cur = root; cur; cur = cur->next)
		if (cur->a.first == c)
			ans.emplace_back(cur->a.second);
	return ans;
}


int MD::dim() const {
	return size;
}


bool MD::vid() const {
	return size == 0;
}

IteratorMD MD::iterator() const {
	return IteratorMD(*this);
}

int MD::adaugaInexistente(MD& md) {
	int nr = 0;
	for (auto it = md.iterator(); it.valid(); it.urmator()) {
		auto x = it.element();
		int found = 0;
		for (node* cur = root; cur; cur = cur->next)
			if (cur->a == x) {
				found = 1;
				break;
			}
		if (!found)
			adauga(x.first, x.second);
	}
	return nr;
}


MD::~MD() {
	if (!root)
		return;
	node* cur = root;
	for (; cur->next; cur = cur->next);
	while (cur) {
		node* p = cur->prev;
		delete cur;
		cur = p;
	}
}

