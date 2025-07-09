#include <iostream>
#include "Do.h"
#include "Iterator.h"
#include <cassert>

#include "TestScurt.h"
#include "TestExtins.h"

bool relatie2(TCheie cheie1, TCheie cheie2) {
	if (cheie1 <= cheie2) {
		return true;
	}
	else {
		return false;
	}
}


int main() {
	testAll();
	testAllExtins();

		//DO dictOrd = DO(relatie2);
		//dictOrd.adauga(3, 2);
		//dictOrd.adauga(9, 2);
		//dictOrd.adauga(7, 2);
		//dictOrd.adauga(16, 2);
		//dictOrd.adauga(18, 2);
		//dictOrd.adauga(14, 2);
		//dictOrd.adauga(11, 2);
		//dictOrd.adauga(13, 2);
		//std::cout << dictOrd.sterge(9);

	std::cout << "Finished Tests!" << std::endl;
}
