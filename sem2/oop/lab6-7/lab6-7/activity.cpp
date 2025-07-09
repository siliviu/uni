#include "activity.h"

Activity::Activity(const std::string& _title, const std::string& _desc, const std::string& _type, const int length) : title(_title), desc(_desc), type(_type), length(length) {}

std::string Activity::GetTitle() const { return title; }
std::string Activity::GetDescription() const { return desc; }
std::string Activity::GetType() const { return type; }
int Activity::GetLength() const noexcept { return length; }

bool Activity::Validate (const std::string& title, const std::string& desc, const std::string& type, const int length) noexcept {
	return !title.empty() && !desc.empty() && !type.empty() && length > 0;
}

std::ostream& operator<<(std::ostream& os, const Activity& x) {
	os << "Title: " << x.title << ", Description: " << x.desc << ", Type: " << x.type << ", Length: " << x.length;
	return os;
}