#include <fstream>
#include <random>
#include "Repo.h"

#pragma once
class Service {
	Repo& r;
public:
	/// <summary>
	/// Constructor
	/// </summary>
	/// <param name="_r"></param>
	Service(Repo& _r) :r(_r) {};
	/// <summary>
	/// Add item
	/// </summary>
	/// <param name="_name"></param>
	/// <param name="_type"></param>
	/// <param name="_colour"></param>
	/// <param name="_stock"></param>
	void Add(std::string _name, std::string _type, std::string _colour, int _stock);
	/// <summary>
	/// Get all items
	/// </summary>
	/// <returns></returns>
	std::vector<Article> GetAll();
	/// <summary>
	/// Export number random items to file_name
	/// </summary>
	/// <param name="file_name"></param>
	/// <param name="number"></param>
	void Export(std::string file_name, int number);
};

