#include "repo.h"
#include "util.h"

template class Repo<Activity>;
template class Repo<int>;

template<class T>
int Repo<T>::Length() const noexcept {
	return (int)v.size();
}
template<class T>
bool Repo<T>::Validate(const int position) const noexcept {
	return 0 <= position && position < Length();
}

template<class T>
T Repo<T>::GetElement(const int position) const {
	return v[position];
}
template<class T>
void Repo<T>::AddElement(const T& element) {
	v.emplace_back(element);
}
template<class T>
void Repo<T>::RemoveElement(const int position) {
	v.erase(position);
}
template<class T>
void Repo<T>::ModifyEement(const int position, const T& element) noexcept {
	v[position] = element;
}

template<class T>
std::vector<T> Repo<T>::GetAllElements() const noexcept {
	std::vector<T> a;
	for (int i = 0; i < v.size(); ++i)
		a.emplace_back(v[i]);
	return a;
}

template<class T>
std::vector<T> Repo<T>::GetElements(std::function<bool(const T&)> f) const {
	std::vector<T> ans;
	for (int i = 0; i < v.size(); ++i)
		if (f(v[i]))
			ans.emplace_back(v[i]);
	return ans;
}
