#pragma once
#include <vector>
#include "vvector.h"
#include <functional>

template<class T>
class Repo {
private:
	vvector<T> v;
public:
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
	T GetElement(const int position) const;
	/// <summary>
	/// Adds element to list
	/// </summary>
	/// <param name="element"></param>
	void AddElement(const T& element);
	/// <summary>
	/// Removes element
	/// </summary>
	/// <param name="position"></param>
	void RemoveElement(const int position);
	/// <summary>
	/// Modifies element
	/// </summary>
	/// <param name="position"></param>
	/// <param name="element"></param>
	void ModifyEement(const int position, const T& element) noexcept;
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