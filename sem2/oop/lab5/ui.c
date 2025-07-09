#pragma once
#include "service.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>


/*
3 Buget de familie

Creati o aplicatie care permite gestiunea bugetului pentru o familie. Aplicatia trebuie sa
stocheze cheltuielile pe o luna. Fiecare cheltuiala are: zi (ziua in care s-a efectuat), suma,
tip (mancare, transport, telefon&internet,inbracaminte,altele)
Aplicatia permite:
a) Adaugarea de cheltuieli noi (cand familia cumpara ceva sau plateste o factura)
b) Modificarea unei cheltuieli existente (ziua, tipul, suma)
c) Stergere cheltuiala
d) Vizualizare lista de cheltuieli filtrat dupa o proprietate (suma, ziua, tipul)
e) Vizualizare lista de cheltuieli ordonat dupa suma sau tip (crescator/descrescator)

*/

void test() {
	TestcreatedestroyCost();
	TestvalideazaCost();
	TestcreateList();
	TestIterate();
	TestCopy();
	TestaddService();
	TestdeleteService();
	TestfindService();
	TestmodifyService();
	TestsortingService();
	TestundoService();
}

void print_all_costs(List* l) {
	if (l->lungime == 0)
		printf("Nu exista cheltuieli in lista.\n");
	else {
		printf("Cheltuielile sunt:\n");
		for (int i = 0; i < l->lungime; i++) {
			Cost c = *(Cost*)get(l, i);
			printf("Zi: %d | Suma: %d | Tip: %s\n", c.zi, c.suma, c.tip);
		}

	}
}

void print_menu() {
	printf("1. Adauga cheltuiala\n2. Sterge cheltuiala\n");
	printf("3. Modifica cheltuiala\n4. Vezi cheltuieli totale\n");
	printf("5. Filtreaza cheltuieli\n6. Vezi cheltuieli ordonate dupa suma/tip\n");
	printf("7. Undo.\n");
	printf("8. Exit.\n");
}

void print_filtru() {
	printf("1. Dupa zi\n2. Dupa tip\n3. Dupa suma\n4. Dupa zi si tip\n5. Intre doua zile\n");
}

void print_ordoneaza() {
	printf("1. Dupa suma\n2. Dupa tip\n");
}

void add_ui(Service* s) {
	int zi = 0, suma = 0;
	char tip[30];
	char enter;
	printf("zi: ");
	scanf_s("%d", &zi);
	printf("suma: ");
	scanf_s("%d", &suma);
	printf("tip: ");
	scanf_s("%c", &enter, 1);
	fgets(tip, sizeof(tip), stdin);
	tip[strlen(tip) - 1] = '\0';

	int ok = addCost(s, zi, suma, tip);
	if (ok)
		printf("Cheltuiala a fost adaugata cu succes.\n");
	else
		printf("Cheltuiala invalida.\n");
}

void delete_ui(Service* s) {
	int zi = 0;
	char tip[30];
	char enter;
	printf("zi: ");
	scanf_s("%d", &zi);
	printf("tip: ");
	//scanf_s("%s", tip);
	scanf_s("%c", &enter, 1);
	fgets(tip, sizeof(tip), stdin);
	tip[strlen(tip) - 1] = '\0';

	int ok = deleteCost(s, zi, tip);
	if (ok)
		printf("Cheltuiala a fost stearsa cu succes.\n");
	else
		printf("Cheltuiala data nu exista.\n");
}

void modify_ui(Service* s) {
	int zi = 0, suma = 0;
	char tip[30];
	char enter;
	printf("zi: ");
	scanf_s("%d", &zi);
	printf("suma: ");
	scanf_s("%d", &suma);
	printf("tip: ");
	scanf_s("%c", &enter, 1);
	fgets(tip, sizeof(tip), stdin);
	tip[strlen(tip) - 1] = '\0';

	int ok = modifyCost(s, zi, suma, tip);
	if (ok)
		printf("Cheltuiala a fost modificata cu succes.\n");
	else
		printf("Cheltuiala data nu exista.\n");
}

void print_filtru_zi(List* l) {
	if (l->lungime == 0)
		printf("Nu exista cheltuieli in lista.\n");
	else {
		int zi = 0;
		printf("Alege o zi: ");
		scanf_s("%d", &zi);

		int nevida = 0;
		for (int i = 0; i < l->lungime; i++) {
			Cost c = *(Cost*)get(l, i);
			if (c.zi == zi) {
				printf("Zi: %d | Suma: %d | Tip: %s\n", c.zi, c.suma, c.tip);
				nevida = 1;
			}
		}
		if (!nevida)
			printf("Nu exista cheltuieli conform filtrului.\n");
	}
}

void print_filtru_tip(List* l) {
	if (l->lungime == 0)
		printf("Nu exista cheltuieli in lista.\n");
	else {
		char tip[30], enter;
		printf("Alege un tip: ");
		scanf_s("%c", &enter, 1);
		fgets(tip, sizeof(tip), stdin);
		tip[strlen(tip) - 1] = '\0';

		int nevida = 0;
		for (int i = 0; i < l->lungime; i++) {
			Cost c = *(Cost*)get(l, i);
			if (strcmp(c.tip, tip) == 0) {
				printf("Zi: %d | Suma: %d | Tip: %s\n", c.zi, c.suma, c.tip);
				nevida = 1;
			}
		}
		if (!nevida)
			printf("Nu exista cheltuieli conform filtrului.\n");
	}
}

void print_filtru_zi_tip(List* l) {
	if (l->lungime == 0)
		printf("Nu exista cheltuieli in lista.\n");
	else {
		char tip[30], enter;
		printf("Alege un tip: ");
		scanf_s("%c", &enter, 1);
		fgets(tip, sizeof(tip), stdin);
		tip[strlen(tip) - 1] = '\0';
		int zi = 0;
		printf("Alege o zi: ");
		scanf_s("%d", &zi);
		int nevida = 0;
		for (int i = 0; i < l->lungime; i++) {
			Cost c = *(Cost*)get(l, i);
			if (strcmp(c.tip, tip) == 0 && c.zi == zi) {
				printf("Zi: %d | Suma: %d | Tip: %s\n", c.zi, c.suma, c.tip);
				nevida = 1;
			}
		}
		if (!nevida)
			printf("Nu exista cheltuieli conform filtrului.\n");
	}
}

void print_filtru_suma(List* l) {
	if (l->lungime == 0)
		printf("Nu exista cheltuieli in lista.\n");
	else {
		int suma = 0;
		printf("Alege o suma: ");
		scanf_s("%d", &suma);

		int nevida = 0;
		for (int i = 0; i < l->lungime; i++) {
			Cost c = *(Cost*)get(l, i);
			if (c.suma == suma) {
				printf("Zi: %d | Suma: %d | Tip: %s\n", c.zi, c.suma, c.tip);
				nevida = 1;
			}
		}
		if (!nevida)
			printf("Nu exista cheltuieli conform filtrului.\n");
	}
}

void print_filtru_zile(List* l) {
	if (l->lungime == 0)
		printf("Nu exista cheltuieli in lista.\n");
	else {
		int sum = 0;
		int zi1 = 0;
		printf("Alege o zi de inceput: ");
		scanf_s("%d", &zi1);
		int zi2 = 0;
		printf("Alege o zi de final: ");
		scanf_s("%d", &zi2);
		for (int i = 0; i < l->lungime; i++) {
			Cost c = *(Cost*)get(l, i);
			if (zi1 <= c.zi && c.zi <= zi2) 
				sum += c.suma;
		}
		printf("Suma cheltuielilor din interval este: %d\n", sum);
	}
}


void print_ordoneaza_suma(Service* s) {
	if (isEmpty(s))
		printf("Nu exista cheltuieli in lista.\n");
	else {
		List* sortedlist = sorting_suma(s);
		print_all_costs(sortedlist);
	}

}

void print_ordoneaza_tip(Service* s) {
	if (isEmpty(s))
		printf("Nu exista cheltuieli in lista.\n");
	else {
		List* sortedlist = sorting_tip(s);
		print_all_costs(sortedlist);
	}
}

void print_undo(Service* s) {
	if (undo(s))
		printf("Operatia de undo a avut loc cu succes\n");
	else
		printf("Nimic ramas la dat undo\n5");
}

void run() {
	Service s = createService();
	int start = 1;
	while (start) {
		print_menu();
		int cmd = 0;
		printf("Comanda este: ");
		scanf_s("%d", &cmd);
		switch (cmd) {
		case 1:
			add_ui(&s);
			break;
		case 2:
			delete_ui(&s);
			break;
		case 3:
			modify_ui(&s);
			break;
		case 4:
			print_all_costs(s.costs);
			break;
		case 5:
			print_filtru();
			int filtru = 0;
			scanf_s("%d", &filtru);
			switch (filtru) {
			case 1:
				print_filtru_zi(s.costs);
				break;
			case 2:
				print_filtru_tip(s.costs);
				break;
			case 3:
				print_filtru_suma(s.costs);
				break;
			case 4:
				print_filtru_zi_tip(s.costs);
				break;
			case 5:
				print_filtru_zile(s.costs);
				break;
			default:
				printf("Comanda invalida.");
			}
			break;
		case 6:
			print_ordoneaza();
			int ordoneaza = 0;
			scanf_s("%d", &ordoneaza);
			switch (ordoneaza) {
			case 1:
				print_ordoneaza_suma(&s);
				break;
			case 2:
				print_ordoneaza_tip(&s);
				break;
			default:
				printf("Comanda invalida.");
			}
			break;
		case 7:
			print_undo(&s);
			break;
		case 8:
			start = 0;
			break;
		default:
			printf("Comanda invalida.");
		}
	}
	closeService(&s);
}

int main() {
	test();
	run();
	_CrtDumpMemoryLeaks();
}
	