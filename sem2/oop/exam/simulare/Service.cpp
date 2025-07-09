#include "Service.h"

std::vector<Task> Service::Get(std::string filter) const {
	std::vector<Task> ans;
	if (filter == "")
		ans = r.GetAll();
	else
		for (auto& x : r.GetAll())
			for (auto& y : x.getProgrammers())
				if (y.find(filter) != std::string::npos)
					ans.emplace_back(x);
	std::sort(ans.begin(), ans.end(), [&](const Task& a, const Task& b) {return a.getState() > b.getState(); });
	return ans;
}

void Service::Add(const int id, const std::string& _desc, const std::vector<std::string>& _pr, const std::string& _state) {
	if (!Task::Validate(_desc, _pr, _state))
		throw std::exception("Eroare");
	for (auto& x : r.GetAll())
		if (x.getId() == id)
			throw std::exception("Eroare");
	r.Add(Task(id, _desc, _pr, _state));
	Notify();
}

std::vector<Task> Service::Filter(std::string filter) const {
	std::vector<Task> ans;
	for (const auto& x : r.GetAll())
		if (x.getState() == filter)
			ans.emplace_back(x);
	return ans;

}

void Service::ChangeState(int id, std::string state) {
	r.Modify(id, state);
	Notify();
}
