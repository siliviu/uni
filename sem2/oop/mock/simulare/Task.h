#pragma once
#include <string>
#include <vector>

class Task {
	int id;
	std::string desc;
	std::vector<std::string> pr;
	std::string state;
public:
	/// <summary>
	/// constructor for task
	/// </summary>
	/// <param name="_id"></param>
	/// <param name="_desc"></param>
	/// <param name="_pr"></param>
	/// <param name="_state"></param>
	Task(int _id, const std::string& _desc, const std::vector<std::string>& _pr, const std::string& _state) : id(_id), desc(_desc), pr(_pr), state(_state) {};
	/// <summary>
	/// get id
	/// </summary>
	/// <returns>int, id</returns>
	int getId() const {
		return id;
	}
	/// <summary>
	/// get description
	/// </summary>
	/// <returns>string, desc</returns>
	std::string getDesc() const {
		return desc;
	}
	/// <summary>
	/// get list of programemrs
	/// </summary>
	/// <returns>vector of programmers</returns>
	std::vector<std::string> getProgrammers() const {
		return pr;
	}
	/// <summary>
	/// get state
	/// </summary>
	/// <returns>string, state</returns>
	std::string getState() const {
		return state;
	}
	/// <summary>
	/// validate object
	/// </summary>
	/// <param name="_desc"></param>
	/// <param name="_pr"></param>
	/// <param name="_state"></param>
	/// <returns>bool, if valid or not</returns>
	static bool Validate(const std::string& _desc, const std::vector<std::string>& _pr, const std::string& _state) {
		return _desc.length() > 0 && 1 <= _pr.size() && _pr.size() <= 4 && (_state == "open" || _state == "inprogress" || _state == "closed");
	}
	/// <summary>
	/// Change state
	/// </summary>
	/// <param name="_state"></param>
	void changeState(std::string _state) {
		state = _state;
	}
};


