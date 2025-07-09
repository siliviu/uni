#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);
constexpr int MAX = 100'000;

template<class T>
struct stack {
	T v[MAX];
	int cur = MAX;
	stack() {
		cur = MAX;
	};
	bool empty() const {
		return cur == MAX;
	}
	T top() const {
		return v[cur];
	}
	T pop() {
		return v[cur++];
	}
	void push(T val) {
		v[--cur] = val;
	}
};

class DO {
	friend class Iterator;
private:
	Relatie rr;

	stack<int> st;
	bool equals(TCheie a, TCheie b) const {
		return rr(a, b) && rr(b, a);
	}
	bool less(TCheie a, TCheie b) const {
		return !rr(b, a);
	}
	struct {
		int key, val;
		int left = -1, right = -1;
	} t[MAX];
	int root = -1, sz = 0;

	int minim(int root) const;
	int maxim(int root) const;

public:

	// constructorul implicit al dictionarului
	DO(Relatie _r);

	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	// O(h) | θ(1) best case
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	// O(h) | θ(1) best case
	TValoare cauta(TCheie c) const;

	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	// O(h) | θ(1) best case
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	// θ(1)
	int dim() const;

	//verifica daca dictionarul e vid
	// θ(1)
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	// O(h) | θ(1) best case
	Iterator iterator() const;

	// returneaza dif dintre val max si val min
	// θ(n)
	int diferentaValoareMaxMin() const;


	// destructorul dictionarului
	~DO();

};
