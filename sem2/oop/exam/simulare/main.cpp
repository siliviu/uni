#include "GUI.h"
#include <QtWidgets/QApplication>
#include "Test.h"
#include <iostream>

int main(int argc, char* argv[]) {
	Test::TestAll();
	QApplication a(argc, argv);
	Repo r;
	Service s(r);
	GUI w(s);
	w.show();
	return a.exec();
}
