#pragma once
#include "activity.h"
#include "repo.h"
#include <stdexcept>
#include <algorithm>

class Service {
private:
	Repo<Activity> r;

public:
	Service() noexcept;
	/// <summary>
	/// Adds activity
	/// </summary>
	/// <param name="title"></param>
	/// <param name="desc"></param>
	/// <param name="type"></param>
	/// <param name="length"></param>
	void Add(const std::string& title, const std::string& desc, const std::string& type, int length);
	/// <summary>
	/// Removes activity based on position
	/// </summary>
	/// <param name="position"></param>
	void Remove(int position);
	/// <summary>
	/// Modifies activity based on activity
	/// </summary>
	/// <param name="position"></param>
	/// <param name="title"></param>
	/// <param name="desc"></param>
	/// <param name="type"></param>
	/// <param name="length"></param>
	void Modify(int position, const std::string& title, const std::string& desc, const std::string& type, int length);
	/// <summary>
	/// Returns a vector of all activities
	/// </summary>
	/// <returns></returns>
	std::vector<Activity> GetAll() const noexcept;
	/// <summary>
	/// Searches based on title
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	std::vector<Activity> Search(const std::string& s) const;
	/// <summary>
	/// Filter based on desc if mode=0, type otherwise
	/// </summary>
	/// <param name="s"></param>
	/// <param name="mode"></param>
	/// <returns></returns>
	std::vector<Activity> Filter(const std::string& s, int mode) const;
	/// <summary>
	/// Sort depending on the mode (0 = title, 1 = desc, 2 = type+length)
	/// </summary>
	/// <param name="mode"></param>
	/// <returns></returns>
	std::vector<Activity> Sort(int mode) const;
};