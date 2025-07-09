#include "tests.h"

void TestDomain() {
	assert(Activity::Validate("1", "2", "3", 4));
	assert(!Activity::Validate("1", "2", "3", -4));
	Activity a("1", "2", "3", 4);
	assert(a.GetTitle() == "1" && a.GetDescription() == "2" && a.GetType() == "3" && a.GetLength() == 4);
	std::stringstream s;
	s << a;
	assert(s.str() == "Title: 1, Description: 2, Type: 3, Length: 4");
}

void TestRepo() {
	Repo<int> a;
	a.AddElement(2);
	a.AddElement(4);
	a.AddElement(5);
	assert(a.Validate(1));
	assert(!a.Validate(-1));
	assert(a.Length() == 3);
	assert(a.GetElement(1) == 4);
	a.RemoveElement(1);
	assert(a.Length() == 2);
	assert(a.GetElement(1) == 5);
	a.ModifyEement(1, 12);
	assert(a.GetElement(1) == 12);
	assert((a.GetElements() == std::vector<int>{2, 12}));
	assert((a.GetElements([&](int a) noexcept {return a < 5; }) == std::vector<int>{2}));
}

void TestService() {
	Service s;
	s.Add("1", "2", "3", 4);
	s.Add("2", "3", "4", 5);
	try {
		s.Add("1", "2", "3", -1); assert(0);
	}
	catch (std::exception e) {
	};
	try {
		s.Add("1", "2", "3", 4); assert(0);
	}
	catch (std::exception e) {
	};
	assert(s.GetAll().size() == 2);
	try {
		s.Remove(-1); assert(0);
	}
	catch (std::exception e) {
	};
	s.Remove(1);
	assert(s.GetAll().size() == 1);
	s.Modify(0, "11", "2", "3", 4);
	try {
		s.Modify(-1, "1", "2", "3", 4); assert(0);
	}
	catch (std::exception e) {
	};
	try {
		s.Modify(0, "1", "2", "3", -4); assert(0);
	}
	catch (std::exception e) {
	};
	assert(s.Search("11").size() == 1);
	Service t;
	t.Add("1", "2", "3", 4);
	t.Add("2", "2", "2", 5);
	t.Add("5", "5", "1", 8);
	t.Add("3", "3", "3", 6);
	t.Add("6", "4", "3", 2);
	t.Add("4", "4", "2", 12);
	assert(t.Filter("2", 0).size() == 2);
	assert(t.Filter("3", 1).size() == 3);
	assert(t.Sort(0)[2].GetTitle() == "3");
	assert(t.Sort(1)[2].GetDescription() == "3");
	assert(t.Sort(2)[2].GetLength() == 12);
}

void TestAll() {
	TestDomain();
	TestRepo();
	TestService();
}