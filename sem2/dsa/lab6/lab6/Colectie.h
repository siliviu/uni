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

	int hash(TElem x) const {
		return (unsigned)(2654435761LL * x) >> (32 - MAX_POW);
	}
	void DeleteNode(int pos, int before) {
		int last = pos;
		for (int cur = a[pos].next; cur != -1; cur = a[cur].next) {
			if (hash(a[cur].val) == pos) {
				a[pos].val = a[cur].val;
				a[pos].freq = a[cur].freq;
				DeleteNode(cur, last);
				return;
			}
			last = cur;
		}
		if (before != -1) {
			a[before].next = a[pos].next;
			if (a[pos].next != -1)
				a[a[pos].next].prev = before;
		}
		a[pos].freq = a[pos].next = a[pos].prev = -1;
	}
	void UpdateFree() {
		while (free < MAX_SIZE && a[free].freq != -1)
			++free;
	}
public:
	//constructorul implicit
	Colectie();

	//adauga un element in colectie
	void adauga(TElem e);

	//sterge o aparitie a unui element din colectie
	//returneaza adevarat daca s-a putut sterge
	bool sterge(TElem e);

	//verifica daca un element se afla in colectie
	bool cauta(TElem elem) const;

	//returneaza numar de aparitii ale unui element in colectie
	int nrAparitii(TElem elem) const;


	//intoarce numarul de elemente din colectie;
	int dim() const;

	//verifica daca colectia e vida;
	bool vida() const;

	//returneaza un iterator pe colectie
	IteratorColectie iterator() const;

	// destructorul colectiei
	~Colectie();

};

