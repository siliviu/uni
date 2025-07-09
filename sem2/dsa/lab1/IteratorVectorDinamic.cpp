#include "IteratorVectorDinamic.h"
#include "VectorDinamic.h"


IteratorVectorDinamic::IteratorVectorDinamic(const VectorDinamic& _v) : v(_v), index(0) {}



void IteratorVectorDinamic::prim() {
	index = 0;
}



bool IteratorVectorDinamic::valid() const {
	return index < v.n&& v.n != 0;
}



TElem IteratorVectorDinamic::element() const {
	return v.v[index];
}



void IteratorVectorDinamic::urmator() {
	++index;
}

