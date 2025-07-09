#include "GUI.h"
#include "Service.h"
#include "Tests.h"
#include <QtWidgets/QApplication>


int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	Tests::TestAll();
	Repo r;
	Service s(r);
	GUI w(s);
	w.show();
	return a.exec();
}
