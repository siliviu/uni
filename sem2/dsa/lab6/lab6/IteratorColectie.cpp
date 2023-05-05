#include "IteratorColectie.h"
#include "Colectie.h"


IteratorColectie::IteratorColectie(const Colectie& c) : col(c) {
	prim();
}

void IteratorColectie::prim() {
	indexv = indexf = 0;
	while (indexv < MAX_SIZE && col.a[indexv].freq == -1)
		++indexv;
}


void IteratorColectie::urmator() {
	++indexf;
	if (indexf >= col.a[indexv].freq) {
		indexf = 0;
		++indexv;
		while (indexv < MAX_SIZE && col.a[indexv].freq == -1)
			++indexv;
	}
}


bool IteratorColectie::valid() const {
	return 0 <= indexv && indexv < MAX_SIZE;
}



TElem IteratorColectie::element() const {
	return col.a[indexv].val;
}
