#include "Test.h"

void TestDomain() {
	Task a(1, "2", { "2","3" }, "open");
	assert(a.getId() == 1 && a.getDesc() == "2" && a.getProgrammers().size() == 2 && a.getState() == "open");
	assert(Task::Validate("2", { "2","3" }, "open"));
	assert(!Task::Validate("2", { "2","3","4","5","6" }, "open"));
	assert(!Task::Validate("2", { }, "open"));
	assert(!Task::Validate("2", { "2" }, "ha"));
	assert(!Task::Validate("", { "2" }, "closed"));
}

void TestRepoService() {
	{
		Repo r("test.txt");
		r.Add(Task(1, "2", { "Ana", "Gigel" }, "open"));
		r.Add(Task(3, "4", { "Ionel", "Ana" }, "closed"));
		assert(r.GetAll().size() == 2);
		Service s(r);
		assert(s.Get("Gigel").size() == 1);
		assert(s.Get().size() == 2);
		try {
			s.Add(3, "4", { "Ionel", "Ana" }, "closed"); assert(0);
		}
		catch (std::exception) {
		}
		try {
			s.Add(4, "5", { }, "inprogress"); assert(0);
		}
		catch (std::exception) {

		}
		s.Add(4, "5", { "Viorel" }, "inprogress");
		s.ChangeState(4, "open");
		assert(s.Filter("open").size() == 2);
	}
	std::ofstream cout("test.txt");
	cout << " ";
}

void Test::TestAll() {
	TestDomain();
	TestRepoService();
}
