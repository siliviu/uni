#pragma once
#include <string>
#include <iostream>

class Activity {
private:
	std::string title, desc, type;
	int length;
public:
	bool operator==(const Activity& a) const = default;
	Activity() = default;
	Activity(const std::string& title, const std::string& desc, const std::string& type, const int length);
	Activity(const Activity& a) : title(a.title), desc(a.desc), type(a.type), length(a.length) { /*std::cerr << "COPY\n";*/ }
	std::string GetTitle() const;
	std::string GetDescription() const;
	std::string GetType() const;
	int GetLength() const noexcept;
	/// <summary>
	/// Returns true or false if the fields could be a valid activity
	/// </summary>
	/// <param name="title"></param>
	/// <param name="desc"></param>
	/// <param name="type"></param>
	/// <param name="length"></param>
	/// <returns></returns>
	static bool Validate(const std::string& title, const std::string& desc, const std::string& type, const int length) noexcept;
	/// <summary>
	/// Overload for streams
	/// </summary>
	/// <param name="os"></param>
	/// <param name="a"></param>
	/// <returns></returns>
	friend std::ostream& operator<<(std::ostream& os, const Activity& a);
};
