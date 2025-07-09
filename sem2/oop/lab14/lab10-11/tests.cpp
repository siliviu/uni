#include "tests.h"

void TestDomain() {
	assert(Activity::Validate("1", "2", "3", 4));
	assert(!Activity::Validate("1", "2", "3", -4));
	Activity a("1", "2", "3", 4);
	assert(a.GetTitle() == "1" && a.GetDescription() == "2" && a.GetType() == "3" && a.GetLength() == 4);
	std::stringstream s;
	s << a;
	assert(s.str() == "1, 2, 3, 4");
}

void TestRepo() {
	Repo<int> a;
	a.AddElement(2);
	a.AddElement(5);
	a.AddElement(4, 1);
	assert(a.Validate(1));
	assert(!a.Validate(-1));
	assert(a.Length() == 3);
	assert(a.GetElement(1) == 4);
	a.RemoveElement(1);
	assert(a.Length() == 2);
	assert(a.GetElement() == 5);
	a.ModifyEement(1, 12);
	assert(a.GetElement(1) == 12);
	assert((a.GetElements() == std::vector<int>{2, 12}));
	assert((a.GetElements([&](int a) noexcept {return a < 5; }) == std::vector<int>{2}));
	a.RemoveElement(), a.RemoveElement();
	assert(a.Length() == 0);
	Repo<UndoAction*> dummy;
	try {
		dummy.Load("nada");
	}
	catch (const AppException&) {
	};
	try {
		dummy.Save("12312");
	}
	catch (const AppException&) {
	};
}

void TestSelected() {
	Repo<Activity> r;
	Service ActivityTable(r);
	ActivityTable.Add("1", "2", "3", 4);
	ActivityTable.Add("2", "2", "2", 5);
	ActivityTable.Add("5", "5", "1", 8);
	ActivityTable.Add("3", "3", "3", 6);
	ActivityTable.Add("6", "4", "3", 2);
	ActivityTable.Add("4", "4", "2", 12);
	ActivityTable.AddSelected("1");
	ActivityTable.PopulateSelected(2);
	assert(ActivityTable.GetSelected().size() == 3);
	ActivityTable.SaveSelected("test");
	ActivityTable.ClearSelected();
	assert(ActivityTable.GetSelected().size() == 0);
	ActivityTable.PopulateSelected(200);
}

void TestUndo() {
	FileRepo<Activity> r("TEST123457.txt");
	Service ActivityTable(r);
	ActivityTable.Add("1", "2", "3", 4);
	ActivityTable.Add("2", "2", "2", 5);
	ActivityTable.Add("5", "5", "1", 8);
	assert(ActivityTable.GetAll().size() == 3);
	ActivityTable.Undo();
	assert(ActivityTable.GetAll().size() == 2);
	ActivityTable.Modify(0, "1", "22", "33", 44);
	ActivityTable.Remove(1);
	assert(ActivityTable.GetAll().size() == 1);
	ActivityTable.Undo();
	assert(ActivityTable.GetAll().size() == 2);
	assert(ActivityTable.GetAll()[0].GetDescription() == "22");
	ActivityTable.Undo();
	assert(ActivityTable.GetAll()[0].GetDescription() == "2");
	ActivityTable.Undo();
	ActivityTable.Undo();
	assert(ActivityTable.GetAll().size() == 0);
	try {
		ActivityTable.Undo(); assert(0);
	}
	catch (const AppException&) {
	};
}

void TestService() {
	FileRepo<Activity> r("TEST1234.txt");
	Service s(r);
	s.Add("1", "2", "3", 4);
	s.Add("2", "3", "4", 5);
	try {
		s.Add("1", "2", "3", -1); assert(0);
	}
	catch (const AppException& e) {
		std::stringstream ss;
		ss << e;
		assert(!ss.str().empty());
	};
	try {
		s.Add("1", "2", "3", 4); assert(0);
	}
	catch (const AppException&) {
	};
	assert(s.GetAll().size() == 2);
	try {
		s.Remove(-1); assert(0);
	}
	catch (const AppException&) {
	};
	s.Remove(1);
	assert(s.GetAll().size() == 1);
	s.Modify(0, "11", "2", "3", 4);
	try {
		s.Modify(-1, "1", "2", "3", 4); assert(0);
	}
	catch (const AppException&) {
	};
	try {
		s.Modify(0, "1", "2", "3", -4); assert(0);
	}
	catch (const AppException&) {
	};
	assert(s.Search("11").size() == 1);
	FileRepo<Activity> rr("TEST12346.txt");
	Service ActivityTable(rr);
	ActivityTable.Add("1", "2", "3", 4);
	ActivityTable.Add("2", "2", "2", 5);
	ActivityTable.Add("5", "5", "1", 8);
	ActivityTable.Add("3", "3", "3", 6);
	ActivityTable.Add("6", "4", "3", 2);
	ActivityTable.Add("4", "4", "2", 12);
	assert(ActivityTable.Filter("2", 0).size() == 2);
	assert(ActivityTable.Filter("3", 1).size() == 3);
	assert(ActivityTable.Sort(0)[2].GetTitle() == "3");
	assert(ActivityTable.Sort(1)[2].GetDescription() == "3");
	assert(ActivityTable.Sort(2)[2].GetLength() == 12);
	TestSelected();
	ActivityTable.Add("1", "4", "2", 12);
	auto ans = ActivityTable.Report();
	assert(ans.size() == 6);
	DTO o;
	o = ans[0];
	assert(ans[0].title == "1" && ans[0].count == 2);
	assert(ans[1].count == 1);
	TestUndo();
}

void TestAll() {
	TestDomain();
	TestRepo();
	TestService();
}