#include "Repo.h"

void Repo::Add(const Article& a) {
	v.emplace_back(a);
}

std::vector<Article> Repo::GetAll() {
	return v;
}
