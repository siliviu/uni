#pragma once

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

typedef struct {
	int zi, suma;
	char* tip;
} Cost;

/*
* 
* Creeaza melodie
	zi - int, ziua cheltuielii
	suma - int, suma cheltuielii
	tip - char, tipul cheltuielii

	returneaza cheltuiala (cost)
*/
Cost* createCost(int zi, int suma, char* tip);

/*
	Distruge cheltuiala
*/
void destroyCost(Cost* c);

/**
 * @brief aaaa
 * @param c - cheltuiala pe car evrem sa o validanm (Cost)
 * @return 1 daca e valida, 0 altfel
*/
int valideazaCost(Cost* c);

/**
 * @brief Copiaza o cheltuiala
 * @param c cheltuiala pe care vrem sa o copiem (Cost)
 * @return cheltuiala copiata
*/
Cost* copyCost(Cost* c);


void TestcreatedestroyCost();
void TestvalideazaCost();
