#include "Service.h"

void Service::Add(std::string _name, std::string _type, std::string _colour, int _stock) {
	r.Add(Article(_name, _type, _colour, _stock));
}

std::vector<Article> Service::GetAll() {
	return r.GetAll();
}

void Service::Export(std::string file_name, int number) {
	static std::mt19937 mt(std::random_device{}());
	std::ofstream cout(file_name);
	std::vector<Article> all = r.GetAll(), ans;
	std::uniform_int_distribution<> dist(0, all.size() - 1);
	while (number--) 
		ans.emplace_back(all[dist(mt)]);
	for (auto x : ans)
		cout << x.name << ' ' << x.colour << ' ' << x.colour << ' ' << x.type << '\n';
}
