#include "vvector.h"
#include "activity.h"

template class vvector<Activity>;
template class vvector<int>;

template<class T>
void vvector<T>::resize() {
	int NN = 2 * N;
	T* w = new T[NN];
	for (int i = 0; i < n; ++i)
		w[i] = v[i];
	delete[] v;
	N = NN;
	v = w;
}

template<class T>
vvector<T>::vvector(int cp) : N(cp) {
	v = new T[cp];
}

template<class T>
vvector<T>::~vvector<T>() noexcept {
	delete[] v;
}


template<class T>
int vvector<T>::size() const noexcept {
	return n;
}


template<class T>
T& vvector<T>::operator[](int i) const noexcept {
	return v[i];
}

template<class T>
void vvector<T>::emplace_back(const T& e) noexcept {
	if (n == N)
		resize();
	v[n++] = e;
}

template<class T>
void vvector<T>::erase(int i) noexcept {
	for (int j = i + 1; j < n; ++j)
		v[j - 1] = v[j];
	--n;
}
