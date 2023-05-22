#include "test.h"
#include <QtWidgets/QApplication>
#include <qpushbutton.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qboxlayout.h>

int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	//test w;
	//w.show();
	auto window = new QWidget();
	auto layout = new QHBoxLayout();
	auto btn = new QPushButton();
	int cnt = 0;
	btn->setText("haha" + QString::number(cnt));
	layout->addWidget(btn);
	auto btn2 = new QPushButton();
	btn2->setText("haha2");
	layout->addWidget(btn2);
	window->setLayout(layout);
	QObject::connect(btn, &QPushButton::clicked, [&] {
		auto x = new QWidget();
		auto l = new QPushButton(x);
		l->setText("click");
		x->show();
		QObject::connect(l, &QPushButton::clicked, [btn, &cnt] {
			//x->show();
			++cnt;
			btn->setText("haha" + QString::number(cnt));
			});
		l->show();
		});
	window->show();
	return a.exec();
}
