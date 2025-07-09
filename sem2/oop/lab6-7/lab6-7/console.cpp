#include "console.h"

template<class T>
void PrintVector(const std::vector<T>& v) {
	int index = 0;
	for (const auto& x : v)
		std::cout << "No. " << index++ << " | " << x << '\n';
}

void Console::PrintAll(const Service& s) const {
	PrintVector(s.GetAll());
}

void Console::AddMenu(Service& s) const {
	std::string title, desc, type;
	int len;
	std::cout << "Enter the title, description, type and length of the activity: ";
	std::cin >> title >> desc >> type >> len;
	try {
		s.Add(title, desc, type, len);
		PrintAll(s);
	}
	catch (std::exception e) {
		std::cout << "Error\n";
	}
}

void Console::RemoveMenu(Service& s) const {
	int pos;
	std::cout << "Enter the position you would like to remove: ";
	std::cin >> pos;
	try {
		s.Remove(pos);
		PrintAll(s);
	}
	catch (std::exception e) {
		std::cout << "Error\n";
	}
}

void Console::ModifyMenu(Service& s) const {
	int pos;
	std::cout << "Enter the position you would like to modify: ";
	std::cin >> pos;
	std::string title, desc, type;
	int len;
	std::cout << "Enter the title, description, type and length of the activity: ";
	std::cin >> title >> desc >> type >> len;
	try {
		s.Modify(pos, title, desc, type, len);
		PrintAll(s);
	}
	catch (std::exception e) {
		std::cout << "Error\n";
	}
}

void Console::SearchMenu(const Service& s) const {
	std::string w;
	std::cout << "Enter the title you wish to search: ";
	std::cin >> w;
	PrintVector(s.Search(w));
}

void Console::FilterMenu(const Service& s) const {
	std::cout << "Choose an option:" << '\n'
		<< "0. Filter by description" << '\n'
		<< "1. Filter by type" << '\n';
	int option;
	std::cin >> option;
	std::cout << "Enter the filter query: ";
	std::string a;
	std::cin >> a;
	PrintVector(s.Filter(a, option));
}

void Console::SortMenu(const Service& s) const {
	std::cout << "Choose an option:" << '\n'
		<< "0. Sort by title" << '\n'
		<< "1. Sort by description" << '\n'
		<< "2. Sort by type + length" << '\n';
	int option;
	std::cin >> option;
	PrintVector(s.Sort(option));
}

Console::Console() noexcept {
}

Console::~Console() noexcept {
}

void Console::Run() const {
	std::cout << "Welcome to the activity manager: " << '\n';
	Service s;
	s.Add("1", "2", "3", 4);
	s.Add("2", "2", "2", 5);
	s.Add("5", "5", "1", 8);
	s.Add("3", "3", "3", 6);
	s.Add("6", "4", "3", 2);
	s.Add("4", "4", "2", 12);
	PrintAll(s);
	while (1) {
		std::cout << "Choose an option:" << '\n'
			<< "0. Exit the application" << '\n'
			<< "1. Add an activity" << '\n'
			<< "2. Remove an activity" << '\n'
			<< "3. Modify an activity" << '\n'
			<< "4. Show all activities" << '\n'
			<< "5. Search activities" << '\n'
			<< "6. Filter activities" << '\n'
			<< "7. Sort activities" << '\n';
		int option;
		std::cin >> option;
		switch (option) {
		case 1:
			AddMenu(s);
			break;
		case 2:
			RemoveMenu(s);
			break;
		case 3:
			ModifyMenu(s);
			break;
		case 4:
			PrintAll(s);
			break;
		case 5:
			SearchMenu(s);
			break;
		case 6:
			FilterMenu(s);
			break;
		case 7:
			SortMenu(s);
			break;
		default:
			return;
		}
	}
	std::cout << "Goodbye!";
}
