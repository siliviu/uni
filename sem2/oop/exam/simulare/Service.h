#pragma once
#include "Repo.h"
#include "Observer.h"
#include <algorithm>

class Service : public Subject {
	Repo& r;
public:
	Service(Repo& _r) :r(_r) {}
	/// <summary>
	/// Get tasks based on programmers sorted by state
	/// By default, returns all
	/// </summary>
	/// <param name="filter">string</param>
	/// <returns></returns>
	std::vector<Task> Get(std::string filter = "") const;
	/// <summary>
	/// Add new task; may throw exception if invalid
	/// </summary>
	/// <param name="_desc">string</param>
	/// <param name="_pr">vector</param>
	/// <param name="_state">string</param>
	void Add(const int id, const std::string& _desc, const std::vector<std::string>& _pr, const std::string& _state);
	/// <summary>
	/// Filter based on state
	/// </summary>
	/// <param name="filter">string</param>
	/// <returns></returns>
	std::vector<Task> Filter(std::string filter = "") const;
	/// <summary>
	/// Change state of task
	/// </summary>
	/// <param name="id">int</param>
	/// <param name="state">string</param>
	void ChangeState(int id, std::string state);
};

