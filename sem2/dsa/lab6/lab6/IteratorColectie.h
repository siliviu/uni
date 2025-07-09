#pragma once
#include "Colectie.h"
#include <exception>

class Colectie;
typedef int TElem;

class IteratorColectie
{
	friend class Colectie;
private:
	//constructorul primeste o referinta catre Container
	//iteratorul va referi primul element din container
	IteratorColectie(const Colectie& c);

	//contine o referinta catre containerul pe care il itereaza
	const Colectie& col;

	int indexv = 0, indexf = 0;


public:

	//reseteaza pozitia iteratorului la inceputul containerului
	//θ(1)
	void prim();

	//muta iteratorul in container
	// arunca exceptie daca iteratorul nu e valid
	// O(m)
	void urmator();

	// muta iteratorul inapoi
	// arunca exceptie daca iteratorul nu e valid
	// O(m)
	void anterior();

	//verifica daca iteratorul e valid (indica un element al containerului)
	//θ(1)
	bool valid() const;

	//returneaza valoarea elementului din container referit de iterator
	//arunca exceptie daca iteratorul nu e valid
	//θ(1)
	TElem element() const;
};

