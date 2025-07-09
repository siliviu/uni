#pragma once
#include "activity.h"
#include "exceptions.h"
#include "file_repo.h"
#include "lab_repo.h"
#include "undo.h"
#include "observer.h"

#include <stdexcept>
#include <algorithm>
#include <random>
#include <chrono>
#include <numeric>
#include <fstream>

class Service : public Subject {
private:
	Repo<Activity> selected;
	Repo<UndoAction*> undolist;
	AbstractRepo<Activity>& list;
public:
	Service(AbstractRepo<Activity>& r);
	/// <summary>
	/// Adds activity
	/// </summary>
	/// <param name="title"></param>
	/// <param name="desc"></param>
	/// <param name="type"></param>
	/// <param name="length"></param>
	void Add(const std::string& title, const std::string& desc, const std::string& type, const int length);
	/// <summary>
	/// Removes activity based on position
	/// </summary>
	/// <param name="position"></param>
	void Remove(const int position);
	/// <summary>
	/// Modifies activity based on activity
	/// </summary>
	/// <param name="position"></param>
	/// <param name="title"></param>
	/// <param name="desc"></param>
	/// <param name="type"></param>
	/// <param name="length"></param>
	void Modify(const int position, const std::string& title, const std::string& desc, const std::string& type, const int length);
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
	std::vector<Activity> Filter(const std::string& s, const int mode) const;
	/// <summary>
	/// Sort depending on the mode (0 = title, 1 = desc, 2 = type+length)
	/// </summary>
	/// <param name="mode"></param>
	/// <returns></returns>
	std::vector<Activity> Sort(const int mode) const;
	/// <summary>
	/// Clear all selected elements from list
	/// </summary>
	void ClearSelected() noexcept;
	/// <summary>
	/// Add to selected list based on title
	/// </summary>
	/// <param name="title"></param>
	void AddSelected(const std::string& title);
	/// <summary>
	/// Fill selected list with random activities from list
	/// </summary>
	/// <param name="nr"></param>
	void PopulateSelected(const int nr);
	/// <summary>
	/// Save all selected activities to a cvs file
	/// </summary>
	/// <param name="name"></param>
	void SaveSelected(const std::string& name) const;
	/// <summary>
	/// Get all selected activities;
	/// </summary>
	std::vector<Activity> GetSelected() const noexcept;
	/// <summary>
	/// Create report counting the number of action of each type
	/// </summary>
	/// <returns></returns>
	std::vector<DTO> Report() const;
	/// <summary>
	/// Undoes the last modification
	/// </summary>
	void Undo();
};