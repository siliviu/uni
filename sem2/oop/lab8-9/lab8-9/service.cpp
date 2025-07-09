#pragma once
#include "service.h"

Service::Service(AbstractRepo<Activity>& r) : list(r) { };

void Service::Add(const std::string& title, const std::string& desc, const std::string& type, const int length) {
	if (!Activity::Validate(title, desc, type, length))
		throw AppException("Activity is not valid");
	Activity a(title, desc, type, length);
	const auto& x = GetAll();
	if (std::find_if(x.begin(), x.end(), [a](const Activity& x) {return x == a; }) != x.end())
		throw AppException("Activity already added");
	list.AddElement(a);
	undolist.AddElement(new UndoAdd(list, list.Length() - 1));
}

void Service::Remove(const int position) {
	if (!list.Validate(position))
		throw AppException("Position doesn't exist");
	undolist.AddElement(new UndoRemove(list, position, list.GetElement(position)));
	list.RemoveElement(position);
}

void Service::Modify(const int position, const std::string& title, const std::string& desc, const std::string& type, const int length) {
	if (!list.Validate(position))
		throw AppException("Position doesn't exist");
	if (!Activity::Validate(title, desc, type, length))
		throw AppException("Activity not valid");
	undolist.AddElement(new UndoModify(list, position, list.GetElement(position)));
	list.ModifyEement(position, Activity(title, desc, type, length));
}

std::vector<Activity> Service::GetAll() const noexcept {
	return list.GetAllElements();
}

std::vector<Activity> Service::Search(const std::string& s) const {
	return list.GetElements([&](const Activity& a) {return a.GetTitle().find(s) != std::string::npos; });
}

std::vector<Activity> Service::Filter(const std::string& s, const int mode) const {
	return list.GetElements([&](const Activity& a) {return mode == 0 ? a.GetDescription() == s : a.GetType() == s; });
}

std::vector<Activity> Service::Sort(const int mode) const {
	auto s = GetAll();
	std::sort(s.begin(), s.end(), [mode](const Activity& a, const Activity& b) {
		return
			mode == 0 ? a.GetTitle() < b.GetTitle() :
			mode == 1 ? a.GetDescription() < b.GetDescription() :
			std::make_pair(a.GetType(), a.GetLength()) < std::make_pair(b.GetType(), b.GetLength());
		});
	return s;
}

void Service::ClearSelected() noexcept {
	selected = Repo<Activity>();
}

void Service::AddSelected(const std::string& title) {
	for (const auto& x : Search(title))
		selected.AddElement(x);
}

void Service::PopulateSelected(const int nr) {
	static std::mt19937 rng((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	const int n = list.Length();
	std::vector<int> ind(n);
	std::iota(ind.begin(), ind.end(), 0);
	shuffle(ind.begin(), ind.end(), rng);
	for (int i = 0; i < nr; ++i)
		selected.AddElement(list.GetElement(i));
}

void Service::SaveSelected(const std::string& name) const {
	selected.Save(name + ".csv");
}

std::vector<Activity> Service::GetSelected() const noexcept {
	return selected.GetAllElements();
}

std::vector<DTO> Service::Report() const {
	std::unordered_map<std::string, DTO> mp;
	for (const auto& x : list.GetAllElements()) {
		if (!mp.count(x.GetTitle()))
			mp.emplace(x.GetTitle(), x.GetTitle());
		else
			++mp[x.GetTitle()].count;
	}
	std::vector<DTO> ans;
	for (auto& [x, y] : mp)
		ans.emplace_back(y);
	return ans;
}

void Service::Undo() {
	if (undolist.Length() == 0)
		throw AppException("Nothing left to undo");
	UndoAction* a = undolist.GetElement();
	a->DoUndo();
	undolist.RemoveElement();
	delete a;
}

