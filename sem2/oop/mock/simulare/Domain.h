#include <string>

#pragma once
class Article {
public:
	const std::string name, type, colour;
	const int stock;
	/// <summary>
	/// constructor
	/// </summary>
	/// <param name="_name"></param>
	/// <param name="_type"></param>
	/// <param name="_colour"></param>
	/// <param name="_stock"></param>
	Article(std::string _name, std::string _type, std::string _colour, int _stock) : name(_name), type(_type), colour(_colour), stock(_stock) {};
};

