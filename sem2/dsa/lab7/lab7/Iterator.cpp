#include "Iterator.h"
#include "DO.h"
#include <exception>
#include <iostream>

using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	prim();
}

void Iterator::prim() {
	cur = dict.root;
	while (!st.empty())
		st.pop();
	while (cur != -1) {
		st.push(cur);
		cur = dict.t[cur].left;
	}
	if (!st.empty()) 
		cur = st.top();
}

void Iterator::urmator() {
	st.pop();
	if (dict.t[cur].right != -1) {
		cur = dict.t[cur].right;
		while (cur != -1) {
			st.push(cur);
			cur = dict.t[cur].left;
		}
	}
	if (!st.empty()) 
		cur = st.top();
	else
		cur = -1;
}

bool Iterator::valid() const {
	return cur != -1;
}

TElem Iterator::element() const {
	if (!valid())
		throw std::exception("a");
	return make_pair(dict.t[cur].key, dict.t[cur].val);
}