#pragma once
#include "repo.h"
#include <fstream>

template<class T>
class FileRepo : public Repo<T> {
	const std::string file_name;
	void Load() { Repo<T>::Load(file_name); }
	void Save() const override { Repo<T>::Save(file_name); }
public:
	~FileRepo() {
		if (file_name.find("TEST1234") != std::string::npos)
			remove(file_name.c_str());
	}
	FileRepo(const std::string& name) : Repo<T>(), file_name(name) { Load(); };
};

