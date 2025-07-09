#include "Sort.h"
#include "Cost.h"
#include "List.h"

void sort(List* l, FunctieComparare cmp) {
	int i, j;
	for (i = 0; i < size(l); i++) {
		for (j = i + 1; j < size(l); j++) {
			ElemType c1 = get(l, i);
			ElemType c2 = get(l, j);
			if (cmp(c1, c2)) {
				//interschimbam
				setElem(l, i, c2);
				setElem(l, j, c1);
			}
		}
	}
}