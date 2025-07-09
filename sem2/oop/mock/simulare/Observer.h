#pragma once
#include <vector>
class Observer {
public:
	virtual void Update() = 0;
};

class Subject {
	std::vector<Observer*> obs;
public:
	void AddObserver(Observer* o) {
		obs.push_back(o);
	}
	void Notify() {
		for (auto& x : obs)
			x->Update();
	}
};

