#pragma once
#include<vector>
#include<utility>

using namespace std;

typedef int TCheie;
typedef int TValoare;

typedef std::pair<TCheie, TValoare> TElem;

class IteratorMD;

struct node {
	pair<TCheie, TValoare> a;
	node* prev, * next;
};

class MD
{
	friend class IteratorMD;

private:
	node* root;
	int size = 0;
public:
	// constructorul implicit al MultiDictionarului
	MD();

	// adauga o pereche (cheie, valoare) in MD
	// θ(1)
	void adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza vectorul de valori asociate
	// θ(n),
	vector<TValoare> cauta(TCheie c) const;

	//sterge o cheie si o valoare 
	//returneaza adevarat daca s-a gasit cheia si valoarea de sters
	// O(n), θ(1) best case
	bool sterge(TCheie c, TValoare v);

	//returneaza numarul de perechi (cheie, valoare) din MD 
	// θ(1)
	int dim() const;

	//verifica daca MultiDictionarul e vid 
	// θ(1)
	bool vid() const;

	// se returneaza iterator pe MD
	// θ(1)
	IteratorMD iterator() const;

	// adauga in multidictionarul curent toate perechile din md care nu se afla deja in multidictionar
	// returneaza numarul de perechi adaugate
	// O(n*m), θ(m) best case
	int adaugaInexistente(MD& md);

	// destructorul MultiDictionarului	
	~MD();



};

