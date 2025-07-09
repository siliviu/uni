#pragma once
#include "List.h"

typedef struct {
	List* costs, * undo;
} Service;

// Returneaza 1 daca exista vreun cost, 0 altfel
int isEmpty(Service* s);

/*
* Adauga o cheltuiala
*
* l - lista data
* zi - ziua
* suma - suma
* tip - tipul cheltuielii
* returneaza 1 daca a fost adaugata, 0 altfel
*/
int addCost(Service* s, int zi, int suma, char* tip);

/*
* Sterge o cheltuiala
*
* l - lista data
* zi - ziua
* tip - tipul cheltuielii
* returneaza 1 daca a fost stearsa, 0 altfel
*/
int deleteCost(Service* s, int zi, char* tip);

/**
 * @brief Gaseste o cheltuiala
 * @param l - lista
 * @param zi - ziua
 * @param tip - tipul
 * @return pozitia pe care se afla
*/
int findCost(Service* s, int zi, char* tip);

/**
 * @brief Modifica o cheltuiala
 * @param l - lista data
 * @param zi - ziua
 * @param suma - suma
 * @param tip - tipul cheltuielii
 * @return 1 daca cheltuiala a fost modificata, 0 altfel
*/
int modifyCost(Service* s, int zi, int suma, char* tip);

/**
 * @brief Sorteaza o lista dupa tip
 * @param l - lista
 * @return o copie a listei sortata
*/
List* sorting_tip(Service* s);

/**
 * @brief Sorteaza o lista dupa suma
 * @param l - lista
 * @return o copie a listei sortata
*/
List* sorting_suma(Service* s);


// Create Service
Service createService();

// Destroy Service
void closeService(Service* S);

// undo ; returneaza 1 daca operatia a avut loc, 0 altfel
int undo(Service* s);

void TestaddService();
void TestdeleteService();
void TestfindService();
void TestmodifyService();
void TestsortingService();
void TestundoService();