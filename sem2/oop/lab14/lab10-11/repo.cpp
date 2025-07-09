#include "repo.h"
#include "util.h"
#include "undo.h"


template class Repo<Activity>;
template class Repo<int>;
template class Repo<UndoAction*>;

template<class T>
int Repo<T>::Length() const noexcept {
	return (int)m.size();
}
template<class T>
bool Repo<T>::Validate(const int position) const noexcept {
	return 0 <= position && position < Length();
}

template<class T>
T Repo<T>::GetElement(const int position) const {
	if (position == -1)
		return m.back();
	return m[position];
}
template<class T>
void Repo<T>::AddElement(const T& element, const int position) {
	if (position == -1)
		m.emplace_back(element);
	else
		m.insert(m.begin() + position, element);
	Save();
}
template<class T>
void Repo<T>::RemoveElement(const int position) {
	if (position == -1)
		m.pop_back();
	else
		m.erase(m.begin() + position);
	Save();
}
template<class T>
void Repo<T>::ModifyEement(const int position, const T& element) {
	m[position] = element;
	Save();
}

template<class T>
std::vector<T> Repo<T>::GetAllElements() const noexcept {
	return m;
}

template<class T>
std::vector<T> Repo<T>::GetElements(std::function<bool(const T&)> f) const {
	std::vector<T> ans;
	std::copy_if(m.begin(), m.end(), std::back_inserter(ans), f);
	return ans;
}

void Repo<UndoAction*>::Save(const std::string& file) const { throw AppException("Cannot print to " + file + ", because object is not printable"); }

template<class T>
void Repo<T>::Save(const std::string& file) const {
	std::ofstream cout(file);
	for (const auto& x : GetAllElements())
		cout << x << '\n';
	cout.close();
}

void Repo<UndoAction*>::Load(const std::string& file) { throw AppException("Cannot read from " + file + ", because object is not readable"); }

template<class T>
void Repo<T>::Load(const std::string& file) {
	std::ifstream cin(file);
	T a;
	while (cin >> a)
		AddElement(a);
	cin.close();
}

Repo<UndoAction*>::~Repo() {
	for (const auto& x : GetAllElements())
		delete x;
}

template<class T>
Repo<T>::~Repo() {}