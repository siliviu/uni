#pragma once
#include <iostream>
#include <iomanip>
#include "service.h"

class Console {
private:
	void AddMenu(Service& s) const;
	void RemoveMenu(Service& s) const;
	void ModifyMenu(Service& s) const;
	void PrintAll(const Service& s) const;
	void SearchMenu(const Service& s) const;
	void FilterMenu(const Service& s) const;
	void SortMenu(const Service& s) const;
	void SelectedMenu(Service& s) const;
	void ReportMenu(const Service& s) const;
	void UndoMenu(Service& s) const;
public:
	Console() noexcept;
	~Console() noexcept;
	void Run() const;
};