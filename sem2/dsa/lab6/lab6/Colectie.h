#pragma once

#define NULL_TELEM -1
typedef int TElem;

class IteratorColectie;

constexpr int MAX_POW = 16, MAX_SIZE = 1 << MAX_POW;

class Colectie
{
	friend class IteratorColectie;
private:
	struct {
		int val, freq = -1, next = -1, prev = -1;
	} a[MAX_SIZE];
	int nr = 0, free = 0;

	int hash(TElem x) const;
	void DeleteNode(int pos, int before);
	void UpdateFree();

public:
	//constructorul implicit
	Colectie() = default;

	//adauga un element in colectie
	// O(n) - θ(1) average
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	// O(n) - θ(1) average
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	// O(n) - θ(1) average
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	// O(n) - θ(1) average
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	//θ(1)
	int dim() const;

	//verifica daca colectia e vida;
	//θ(1)
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie() = default;
};