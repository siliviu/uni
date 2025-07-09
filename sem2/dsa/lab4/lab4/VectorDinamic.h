#pragma once
#include <algorithm>
//tip de data generic (pentru moment este intreg)

typedef int TElem;
typedef std::tuple<int,int,TElem> TElemL;
typedef std::pair<TElemL, int> TElemV;

typedef int TElemV2;


class VectorDinamic {
private:
	/* aici e reprezentarea */
	int n = 0, N = 0;
	TElemV* v;
	// redimensionare
	void redim();
public:
	// constructor
	//arunca exceptie in cazul in care capacitate e <=0
	VectorDinamic(int capacitate);

	// returnare dimensiune
	int dim() const;

	// returnare element
	//arunca exceptie daca i nu e valid
	//indicii ii consideram de la 0
	TElemV element(int i) const;

	// modifica element de pe pozitia i si returneaza vechea valoare
	//arunca exceptie daca i nu e valid
	TElemV modifica(int i, TElemV e);

	// adaugare element la sfarsit
	void adaugaSfarsit(TElemV e);

	// adaugare element pe o pozitie i
	//arunca exceptie daca i nu e valid
	void adauga(int i, TElemV e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElemV sterge(int i);


	//destructor
	~VectorDinamic();
};

class VectorDinamicLibere {
private:
	/* aici e reprezentarea */
	int n = 0, N = 0;
	TElemV2* v;
	// redimensionare
	void redim();
public:
	// constructor
	//arunca exceptie in cazul in care capacitate e <=0
	VectorDinamicLibere(int capacitate);

	// returnare dimensiune
	int dim() const;

	// returnare element
	//arunca exceptie daca i nu e valid
	//indicii ii consideram de la 0
	TElemV2 element(int i) const;

	// modifica element de pe pozitia i si returneaza vechea valoare
	//arunca exceptie daca i nu e valid
	TElemV2 modifica(int i, TElemV2 e);

	// adaugare element la sfarsit
	void adaugaSfarsit(TElemV2 e);

	// adaugare element pe o pozitie i
	//arunca exceptie daca i nu e valid
	void adauga(int i, TElemV2 e);

	// sterge element de pe o pozitie i si returneaza elementul sters
	//arunca exceptie daca i nu e valid
	TElemV2 sterge(int i);

	//destructor
	~VectorDinamicLibere();
};