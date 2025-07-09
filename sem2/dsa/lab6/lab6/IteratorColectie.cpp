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
	if (indexv < 0 || indexv >= MAX_SIZE)
		throw std::exception("Iteratorul nu este valid");
	++indexf;
	if (indexf >= col.a[indexv].freq) {
		indexf = 0;
		++indexv;
		while (indexv < MAX_SIZE && col.a[indexv].freq == -1)
			++indexv;
	}
}

void IteratorColectie::anterior() {
	if (indexv < 0 || indexv >= MAX_SIZE)
		throw std::exception("Iteratorul nu este valid");
	--indexf;
	if (indexf < 0) {
		--indexv;
		while (indexv >= 0 && col.a[indexv].freq == -1)
			--indexv;
		if (indexv >= 0)
			indexf = col.a[indexv].freq - 1;
	}
}


bool IteratorColectie::valid() const {
	return 0 <= indexv && indexv < MAX_SIZE;
}



TElem IteratorColectie::element() const {
	if (indexv < 0 || indexv == MAX_SIZE)
		throw std::exception("Iteratorul nu este valid");
	return col.a[indexv].val;
}
