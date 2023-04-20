#pragma once
#include "service.h"

Service::Service() noexcept {}

void Service::Add(const std::string& title, const std::string& desc, const std::string& type, int length) {
	if (!Activity::Validate(title, desc, type, length))
		throw std::runtime_error("a");
	r.AddElement(Activity(title, desc, type, length));
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

const std::vector<Activity>& Service::GetAll() const noexcept{
	return r.GetAllElements();
}

std::vector<Activity> Service::Search(const std::string& s) const {
	return r.GetElements([&](const Activity& a) {return a.GetTitle().find(s) != std::string::npos; });
}