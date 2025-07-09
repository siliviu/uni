#pragma once
#include <fstream>
#include <string>
#include "Task.h"

class Repo {
	std::vector<Task> v;
	const std::string FILE_NAME;
public:
	/// <summary>
	/// add to repo
	/// </summary>
	/// <param name="t"></param>
	void Add(const Task& t);
	/// Modify State
	void Modify(int id, std::string state);
	/// <summary>
	/// constructor
	/// </summary>
	Repo(std::string _name = "file.txt");
	/// <summary>
	/// get all
	/// </summary>
	/// <returns></returns>
	std::vector<Task> GetAll() const;
	/// <summary>
	/// save to file
	/// </summary>
	void Write();
};

