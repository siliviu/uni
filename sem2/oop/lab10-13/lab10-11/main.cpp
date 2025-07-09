#include <iostream>
#include <crtdbg.h>
#include "util.h"
#include "tests.h"
#include "gui.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[]) {
	TestAll();
	QApplication a(argc, argv);
	FileRepo<Activity> r("activities.txt");
	Service s(r);
	GUI w(s);
	w.show();
	return a.exec();
}
