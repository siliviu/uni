#pragma once
#include <vector>
#include <functional>
#include <string>


template<class T>
class AbstractRepo {
public:
	virtual ~AbstractRepo() = default;
	/// <summary>
	/// Returns number of elements
	/// </summary>
	/// <returns></returns>
	virtual int Length() const noexcept = 0;
	/// <summary>
	/// Returns true or false if the position is valid
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	virtual bool Validate(const int position) const noexcept = 0;
	/// <summary>
	/// Returns element based on position
	/// </summary>
	/// <param name="position"></param>
	/// <returns></returns>
	virtual T GetElement(const int position = -1) const = 0;
	/// <summary>
	/// Adds element to list
	/// </summary>
	/// <param name="element"></param>
	virtual void AddElement(const T& element, const int position = -1) = 0;
	/// <summary>
	/// Removes element
	/// </summary>
	/// <param name="position"></param>
	virtual void RemoveElement(const int position = -1) = 0;
	/// <summary>
	/// Modifies element
	/// </summary>
	/// <param name="position"></param>
	/// <param name="element"></param>
	virtual void ModifyEement(const int position, const T& element) = 0;
	/// <summary>
	/// Get all elements
	/// </summary>
	/// <returns></returns>
	virtual std::vector<T> GetAllElements() const noexcept = 0;
	/// <summary>
	/// Gets all elements based on function
	/// </summary>
	/// <param name="f"></param>
	/// <returns></returns>
	virtual std::vector<T> GetElements(std::function<bool(const T&)> f = [](const T&) noexcept {return true; }) const = 0;
};


