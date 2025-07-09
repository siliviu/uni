#include "IteratorMD.h"
#include "MD.h"

using namespace std;

IteratorMD::IteratorMD(const MD& _md): md(_md) {
	cur = md.root;
}

TElem IteratorMD::element() const{
	if (!valid())
		throw runtime_error("Invalid");
	return cur->a;
}

bool IteratorMD::valid() const {
	return cur != 0;
}

void IteratorMD::urmator() {
	cur = cur->next;
}

void IteratorMD::prim() {
	cur = md.root;
}

