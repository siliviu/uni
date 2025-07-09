#pragma once
#include <map>
#include "abstract_repo.h"

//template class AbstractRepo<Activity>;
//template class AbstractRepo<int>;
//template class AbstractRepo<UndoAction*>;

template<class T>
class LabRepo : public AbstractRepo<T> {
private:
	std::map<int, T> m;
	double p;
	/// <summary>
	/// Returns true if an exception should be thrown
	/// </summary>
	/// <returns></returns>
	bool GetRandom() const;
public:
	LabRepo(double _p) : p(_p) {}
	~LabRepo();
	/// <summary>
	/// Returns number of elements
	/// </summary>
	/// <returns></returns>
	int Length() const noexcept;
	/// <summary>
	/// Returns true or false if the position is valid
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	bool Validate(const int position) const noexcept;
	/// <summary>
	/// Returns element based on position
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	T GetElement(const int position = -1) const;
	/// <summary>
	/// Adds element to list
	/// </summary>
	/// <param name="element"></param>
	void AddElement(const T& element, const int position = -1);
	/// <summary>
	/// Removes element
	/// </summary>
	/// <param name="position"></param>
	void RemoveElement(const int position = -1);
	/// <summary>
	/// Modifies element
	/// </summary>
	/// <param name="position"></param>
	/// <param name="element"></param>
	void ModifyEement(const int position, const T& element);
	/// <summary>
	/// Get all elements
	/// </summary>
	/// <returns></returns>
	std::vector<T> GetAllElements() const noexcept;
	/// <summary>
	/// Gets all elements based on function
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	std::vector<T> GetElements(std::function<bool(const T&)> f = [](const T&) noexcept {return true; }) const;
};