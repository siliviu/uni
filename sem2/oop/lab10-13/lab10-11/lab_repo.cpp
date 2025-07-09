#include "lab_repo.h"
#include "util.h"
#include "undo.h"
#include "exceptions.h"


template class LabRepo<Activity>;
template class LabRepo<int>;

template<class T>
int LabRepo<T>::Length() const noexcept {
	return (int)m.size();
}
template<class T>
bool LabRepo<T>::Validate(const int position) const noexcept {
	return 0 <= position && position < Length();
}

template<class T>
T LabRepo<T>::GetElement(const int position) const {
	if (GetRandom())
		throw AppException("Bad luck");
	if (position == -1)
		return m.rbegin()->second;
	auto it = m.begin();
	std::advance(it, position);
	return it->second;
}

template<class T>
void LabRepo<T>::AddElement(const T& element, const int position) {
	if (GetRandom())
		throw AppException("Bad luck");
	if (position == -1)
		m[Length()] = element;
	else
		m[position] = element;
}
template<class T>
void LabRepo<T>::RemoveElement(const int position) {
	if (GetRandom())
		throw AppException("Bad luck");
	if (position == -1)
		m.erase(Length() - 1);
	else {
		m.erase(position);
		std::vector<std::pair<int, T>> v;
		for (auto& [key, val] : m)
			if (key > position)
				v.emplace_back(key, val);
		for (const auto& [key, val] : v) {
			m.erase(key);
			m[key - 1] = val;
		}
	}
}

template<class T>
void LabRepo<T>::ModifyEement(const int position, const T& element) {
	if (GetRandom())
		throw AppException("Bad luck");
	m[position] = element;
}

template<class T>
std::vector<T> LabRepo<T>::GetAllElements() const noexcept {
	std::vector<T> ans;
	for (const auto& [key, x] : m)
		ans.emplace_back(x);
	return ans;
}

template<class T>
std::vector<T> LabRepo<T>::GetElements(std::function<bool(const T&)> f) const {
	std::vector<T> ans;
	for (const auto& [key, val] : m)
		if (f(val))
			ans.emplace_back(val);
	return ans;
}

template<class T>
bool LabRepo<T>::GetRandom() const{
	static std::mt19937 rng((unsigned int)std::chrono::steady_clock::now().time_since_epoch().count());
	double nr = std::uniform_real_distribution<double>(0, 1)(rng);
	return nr < p;
}

template<class T>
LabRepo<T>::~LabRepo() {}