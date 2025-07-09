#include <vector>
#include "domain.h"

#pragma once
class Repo {
public:
	std::vector<Article> v;
	/// <summary>
	/// Add item to repo
	/// </summary>
	/// <param name="a"></param>
	void Add(const Article& a);
	/// <summary>
	/// Get all items
	/// </summary>
	/// <returns></returns>
	std::vector<Article> GetAll();
};

