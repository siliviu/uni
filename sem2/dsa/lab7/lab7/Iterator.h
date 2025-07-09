#pragma once

#include "DO.h"

class Iterator {
	friend class DO;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	Iterator(const DO& dictionar);
	//contine o referinta catre containerul pe care il itereaza
	const DO& dict;
	stack<int> st;
	int cur;
	/* aici e reprezentarea specifica a iteratorului */

public:

	//reseteaza pozitia iteratorului la inceputul containerului
	//O(h) | θ(1) best case
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	// θ(1) amortizat (O(h))
	void urmator();

	//verifica daca iteratorul e valid (indica un element al containerului)
	// θ(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	// θ(1)
	TElem element() const;
};

