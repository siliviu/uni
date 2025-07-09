#pragma once
#include <vector>
#include <algorithm>

class Observer {
	friend class Subject;
protected:
	virtual void Update() = 0;
public:
	virtual ~Observer() = default;
};

class Subject {
	std::vector<Observer*> v;
public:
	void AddObserver(Observer* o) {
		v.emplace_back(o);
	}
	void RemoveObserver(Observer* o) {
		std::erase(v, o);
	}
	virtual ~Subject() = default;
	void Notify() {
		for (auto& x : v)
			x->Update();
	}
};

