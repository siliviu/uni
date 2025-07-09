#include "Repo.h"
void Repo::Add(const Task& t) {
	v.emplace_back(t);
	Write();
}

void Repo::Modify(int id, std::string state) {
	for (auto& x : v)
		if (x.getId() == id)
			x.changeState(state);
	Write();
}

Repo::Repo(std::string _name) :FILE_NAME(_name) {
	std::ifstream cin(FILE_NAME);
	int id;
	std::string desc;
	std::string state;
	while (cin >> id) {
		cin >> desc;
		std::string programmer;
		std::vector<std::string> pr;
		while (!!(cin >> programmer) && programmer != "|")
			pr.emplace_back(programmer);
		cin >> state;
		Add(Task(id, desc, pr, state));
	}
};

std::vector<Task> Repo::GetAll() const {
	return v;
}

void Repo::Write() {
	std::ofstream cout(FILE_NAME);
	for (const auto& x : v) {
		cout << x.getId() << ' ' << x.getDesc() << ' ';
		for (auto& y : x.getProgrammers())
			cout << y << ' ';
		cout << "| ";
		cout << x.getState() << '\n';

	}
}