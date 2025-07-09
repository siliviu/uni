#include "VectorDinamic.h"
#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorMultime;

class Multime {
	friend class IteratorMultime;

    private:
		VectorDinamic v;
		/* aici e reprezentarea */

    public:
 		// constructorul implicit
		Multime();

		// adauga un element in multime
		// returneaza adevarat daca elementul a fost adaugat (nu exista deja in multime)
		// complexitate = θ(1) Best Case, θ(n) Worse Case -> O(n) overall


		bool adauga(TElem e);

		// sterge un element din multime
		// returneaza adevarat daca elementul a existat si a fost sters
		// complexitate = θ(1) Best Case, θ(n) Worse Case -> O(n) overall
		bool sterge(TElem e);

		// verifica daca un element se afla in multime
		// complexitate = θ(1) Best Case, θ(n) Worse Case -> O(n) overall
		bool cauta(TElem elem) const;


		// intoarce numarul de elemente din multime;
		// complexitate = θ(1)
		int dim() const;

		// verifica daca multimea e vida;
		// complexitate = θ(1)
		bool vida() const;

		// returneaza un iterator pe multime
		// complexitate = θ(1)
		IteratorMultime iterator() const;

		// returneaza diferenta dintre valoarea maxima si cea minima (presupunem valori intregi)
		// daca multimea este vida, se returneaza -1
		// complexitate = θ(n)
		int diferentaMaxMin() const;

		// destructorul multimii
		~Multime();
};




