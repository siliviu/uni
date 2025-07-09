#pragma once
#include <tuple>
#include <algorithm>
#include "VectorDinamic.h"

#define NULL_TELEMENT 0

class Matrice {

private:
	int n, m;
	int first;
	VectorDinamic v;
	VectorDinamicLibere l;
	void AddList(TElemL e);
	void RemoveList(int pos);
public:

	//constructor
	//se arunca exceptie daca nrLinii<=0 sau nrColoane<=0
	Matrice(int nrLinii, int nrColoane);


	//destructor
	~Matrice() {};

	//returnare element de pe o linie si o coloana
	//se arunca exceptie daca (i,j) nu e pozitie valida in Matrice
	//indicii se considera incepand de la 0
	// O(n), n - number of non zero elements
	TElem element(int i, int j) const;


	// returnare numar linii
	// θ(1)
	int nrLinii() const;

	// returnare numar coloane
	// θ(1)
	int nrColoane() const;


	// modificare element de pe o linie si o coloana si returnarea vechii valori
	// se arunca exceptie daca (i,j) nu e o pozitie valida in Matrice
	// O(n), n - number of non zero elements
	TElem modifica(int i, int j, TElem e);

	// gaseste si returneaza valoarea maxima din matrice
	// da ca matricea este vida, se returneaza NULL_TVALOARE
	// O(n), n - number of non zero elements
	int valoareMaxima() const;
};







