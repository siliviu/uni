#pragma once
#include "List.h"

/**
* @brief Functie de comparare a 2 elemente 
* @return returneaza 1 daca c1>c2, 0 altfel
*/
typedef int(*FunctieComparare)(Cost* c1, Cost* c2);

/** 
* @brief  Sorteaza o lista dupa un anumit criteriu
* @param l  - lista
* @param cmp - relatia dupa care se sorteaza
*/
void sort(List* l, FunctieComparare cmp);