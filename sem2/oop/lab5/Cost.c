#pragma once
#include "Cost.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>


Cost* createCost(int zi, int suma, char* tip) {
	Cost* c = (Cost*)malloc(sizeof(Cost));
	c->zi = zi;
	c->suma = suma;
	int nrc = (int)strlen(tip) + 1;
	c->tip = malloc(nrc * sizeof(char));
	strcpy_s(c->tip, nrc, tip);
	return c;
}

void destroyCost(Cost* c) {
	free(c->tip);
	free(c);
}

Cost* copyCost(Cost* c) {
	return createCost(c->zi, c->suma, c->tip);
}

int valideazaCost(Cost* c) {
	if (c->zi <= 0 || c->zi > 30)
		return 0;
	if (c->suma <= 0)
		return 0;
	if (!(strcmp("mancare", c->tip) == 0 || strcmp("transport", c->tip) == 0 || strcmp("telefon", c->tip) == 0 ||
		strcmp("imbracaminte", c->tip) == 0 || strcmp("altele", c->tip) == 0))
		return 0;
	return 1;
}

void TestcreatedestroyCost() {
	Cost* c = createCost(1, 50, "telefon");

	assert(c->zi == 1);
	assert(c->suma == 50);
	assert(strcmp(c->tip, "telefon") == 0);

	destroyCost(c);
	//assert(c.zi == -1);
	//assert(c.suma == -1);
	//assert(strlen(c.tip) == 0);

}
void TestvalideazaCost() {
	Cost* c1 = createCost(-1, -1, "b");
	assert(valideazaCost(c1) == 0);

	Cost* c2 = createCost(-1, -1, "altele");
	assert(valideazaCost(c2) == 0);

	Cost* c3 = createCost(-1, 50, "altele");
	assert(valideazaCost(c3) == 0);

	Cost* c4 = createCost(1, 50, "altele");
	assert(valideazaCost(c4) == 1);

	Cost* c5 = createCost(1, 50, "b");
	assert(valideazaCost(c5) == 0);

	Cost* c6 = createCost(1, 0, "altele");
	assert(valideazaCost(c6) == 0);

	destroyCost(c1);
	destroyCost(c2);
	destroyCost(c3);
	destroyCost(c4);
	destroyCost(c5);
	destroyCost(c6);
}