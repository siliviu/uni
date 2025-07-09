template<class T>
class vvector {
private:
	int n = 0, N = 0;
	T* v;
	// resize
	void resize();
public:
	vvector(int cp = 2);

	// return size
	int size() const noexcept;

	// access element
	T& operator[](int i) const noexcept;

	// add element to the back
	void emplace_back(const T& e) noexcept;

	// delete element
	void erase(int i) noexcept;

	//destructor
	~vvector() noexcept;
};