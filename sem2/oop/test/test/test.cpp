#include "test.h"
#include <QtWidgets/QApplication>
#include <qpushbutton.h>
#include <qdialog.h>
#include <qlabel.h>

test::test(QWidget* parent)
	: QMainWindow(parent) {
	auto q = new QWidget(parent);
	auto btn = new QPushButton(q);
	btn->setText("haha");
	btn->show();
	auto btn2 = new QPushButton(q);
	btn2->setText("haha2");
	btn2->show();
	QObject::connect(btn, &QPushButton::clicked, [] {
		auto x = new QWidget();
		auto l = new QLabel(x);
		l->setText("haha");
		x->show();
		QObject::connect(x, &QWidget::close, [] {
			});
		l->show();
		});
	q->show();
	ui.setupUi(this);
}

test::~test()
{}
