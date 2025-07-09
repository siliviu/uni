#pragma once
#include <stdexcept>
#include <ostream>

class AppException {
	std::string msg;
public:
	AppException(const std::string& s) : msg(s) {};
	friend std::ostream& operator<<(std::ostream& out, const AppException& e) {
		out << e.msg;
		return out;
	}
};

