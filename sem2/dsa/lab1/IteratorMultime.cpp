#include "IteratorMultime.h"
#include "Multime.h"


IteratorMultime::IteratorMultime(const Multime& m) : multime(m), it(m.v.iterator()) {
}


void IteratorMultime::prim() {
	it.prim();
}


void IteratorMultime::urmator() {
	it.urmator();
}


TElem IteratorMultime::element() const {
	return it.element();
}

bool IteratorMultime::valid() const {
	return it.valid();
}
