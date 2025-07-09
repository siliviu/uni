#include "Tests.h"
#include <assert.h>

void Tests::TestAll() {
	Repo r;
	assert(r.GetAll().size() == 0);
	r.Add(Article("a", "b", "c", 2));
	assert(r.GetAll().size() == 1);
	Service s(r);
	s.Add("b", "c", "d", 3);
	assert(s.GetAll().size() == 2);
	s.Export("testing_only.txt", 3);
}