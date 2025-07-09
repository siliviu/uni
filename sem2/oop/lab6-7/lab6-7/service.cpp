#include "service.h"

Service::Service() noexcept {}

void Service::Add(const std::string& title, const std::string& desc, const std::string& type, int length) {
	if (!Activity::Validate(title, desc, type, length))
		throw std::runtime_error("a");
	Activity a(title, desc, type, length);
	for (const auto& x : GetAll())
		if (x == a)
			throw std::runtime_error("d");
	r.AddElement(a);
}

void Service::Remove(int position) {
	if (!r.Validate(position))
		throw std::runtime_error("b");
	r.RemoveElement(position);
}

void Service::Modify(int position, const std::string& title, const std::string& desc, const std::string& type, int length) {
	if (!r.Validate(position))
		throw std::runtime_error("b");
	if (!Activity::Validate(title, desc, type, length))
		throw std::runtime_error("a");
	r.ModifyEement(position, Activity(title, desc, type, length));
}

std::vector<Activity> Service::GetAll() const noexcept {
	return r.GetAllElements();
}

std::vector<Activity> Service::Search(const std::string& s) const {
	return r.GetElements([&](const Activity& a) {return a.GetTitle().find(s) != std::string::npos; });
}

std::vector<Activity> Service::Filter(const std::string& s, int mode) const {
	return r.GetElements([&](const Activity& a) {return mode == 0 ? a.GetDescription() == s : a.GetType() == s; });
}

std::vector<Activity> Service::Sort(int mode) const
{
	auto s = GetAll();
	std::sort(s.begin(), s.end(), [&](const Activity& a, const Activity& b) {
		return
			mode == 0 ? a.GetTitle() < b.GetTitle() :
			mode == 1 ? a.GetDescription() < b.GetDescription() :
			std::make_pair(a.GetType(), a.GetLength()) < std::make_pair(b.GetType(), b.GetLength());
		});
	return s;
}

