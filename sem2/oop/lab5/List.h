#pragma once

#include "Cost.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

typedef void* ElemType;
typedef void (*DestroyFct)(ElemType);
typedef ElemType(*CopyFct)(ElemType);

typedef struct {
	ElemType* elems;
	int lungime;
	int capacitate;
	DestroyFct destroy;
	CopyFct copy;
} List;


/*
* creeaza  lista goala
* d - functie de distrugere a elementului
* c - functie de copiere a elementului
* returneaza o lista de tip List
*/
List* createNewList(DestroyFct d, CopyFct c);

/*
* distruge lista
* 
* l - lista pe care o vrem distruge
*/
void destroyList(List* l);

/*
* Returneaza elementul de pe pozitia poz
* 
* l - lista data
* poz - pozitie
*/
ElemType get(List* l, int poz);

/*
* Pune un elemente pe o pozitie
* 
* l - lista data
* poz - pozitie
* el - elementul de adaugat
*/
ElemType setElem(List* l, int poz, ElemType el);

/*
* Returneaza nr de elemente din lista
* 
* l - lista data
*/
int size(List* l);

/*
* Adauga un element
* 
* l - lista data
* el - elemntul de adaugat
*/
void add(List* l, ElemType el);

/*
* Sterge un element
*
* l - lista data
* el - elemntul de sters
*/
ElemType delete(List* l, int poz);

/*
* face o copie la lista
* 
* l = lista data
* returneaza o copie a liste date
*/
List* copyList(List* l);

void TestcreateList();
void TestIterate();
void TestCopy();
