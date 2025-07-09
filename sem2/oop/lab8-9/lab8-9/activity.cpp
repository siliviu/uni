#include "activity.h"
#include "exceptions.h"

Activity::Activity(const std::string& _title, const std::string& _desc, const std::string& _type, const int length) : title(_title), desc(_desc), type(_type), length(length) {}

std::string Activity::GetTitle() const { return title; }
std::string Activity::GetDescription() const { return desc; }
std::string Activity::GetType() const { return type; }
int Activity::GetLength() const noexcept { return length; }

bool Activity::Validate(const std::string& title, const std::string& desc, const std::string& type, const int length) noexcept {
	return !title.empty() && !desc.empty() && !type.empty() && length > 0;
}

std::ostream& operator<<(std::ostream& os, const Activity& x) {
	const auto w = os.width();
	os << std::setw(w) << x.title << ", " << std::setw(w) << x.desc << ", " << std::setw(w) << x.type << ", " << std::setw(w) << x.length;
	return os;
}

std::istream& operator>>(std::istream& is, Activity& a) {
	std::string title, desc, type;
	int length;
	is >> title;
	if (title.empty())
		return is;
	title.pop_back();
	is >> desc;
	desc.pop_back();
	is >> type;
	type.pop_back();
	is >> length;
	a = Activity(title, desc, type, length);
	return is;
}
