#pragma once

#include <QtWidgets/QWidget>
#include "ui_Practice.h"
#include <qtablewidget.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qlistwidget.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qslider.h>
#include <qcheckbox.h>
#include <qspinbox.h>
#include <qcombobox.h>
#include <qgroupbox.h>
#include <qradiobutton.h>
#include <qformlayout.h>
#include <qlineedit.h>

class Practice : public QWidget
{
	Q_OBJECT
protected:
	QTableWidget* a;
	QListWidget* b;
	QLabel* l;
	QSlider* slider;
	QCheckBox* c;
	QSpinBox* s;
	QHBoxLayout* aa;
	QRadioButton* b1, * b2;
	int nrtogen = 10;
	QBrush color1 = Qt::blue, color2 = Qt::white;
	QLineEdit* l1, * l2;
public:
	void Reset() {
		a->setRowCount(0);
		a->setRowCount(nrtogen);
		b->clear();
		for (int i = 0; i < nrtogen; ++i) {
			int A = rand() % (slider->value() + 1), B = rand() % 6;
			auto item = new QTableWidgetItem(QString::number(A));
			if (A <= 5 && c->isChecked())
				item->setBackground(Qt::red);
			a->setItem(i, 0, item);
			auto item2 = new QTableWidgetItem(QString::number(B));
			if (B <= 2 && c->isChecked())
				item2->setBackground(Qt::green);
			a->setItem(i, 1, item2);
			auto item3 = new QListWidgetItem(QString::number(A) + " " + QString::number(B));
			item3->setFont(QFont("das", 10 + rand() % 20));
			if (c->isChecked()) {
				if (A + B <= 7)
					item3->setBackground(color1);
				else
					item3->setBackground(color2);
			}
			b->addItem(item3);
		}
	}

	void ClearLayout(QLayout* layout) {
		//if (layout == NULL)
			//return;
		QLayoutItem* item;
		while ((item = layout->takeAt(0))) {
			delete item->widget();
			//delete item;
		}
	}

	Practice() {
		auto MainLayout = new QHBoxLayout();
		auto Layout = new QVBoxLayout();
		MainLayout->addLayout(Layout);
		a = new QTableWidget(0, 2);
		a->setHorizontalHeaderLabels(QStringList({ "1","2" }));
		Layout->addWidget(a);
		b = new QListWidget();
		connect(b, &QListWidget::itemSelectionChanged, [&]() {
			if (b->selectedItems().size() == 0)
				return;
			auto a = b->selectedItems()[0];
			l->setText("Selected: " + a->text());
			});
		Layout->addWidget(b);
		auto Button = new QPushButton("Reload");
		connect(Button, &QPushButton::pressed, [&] {
			QMessageBox::information(this, "App", "Reloaded!\nglhf");
			Reset();
			});
		l = new QLabel("Selected: ");
		Layout->addWidget(l);
		Layout->addWidget(Button);
		c = new QCheckBox("Color (true)");
		c->setChecked(1);
		connect(c, &QCheckBox::stateChanged, [&](int state) {
			c->setText("Color (" + QString::fromStdString(state ? "true" : "false") + ")");
			});
		Layout->addWidget(c);
		auto gl = new QGridLayout();
		slider = new QSlider();
		slider->setRange(5, 10);
		connect(slider, &QSlider::valueChanged, [&](int val) {
			QMessageBox::information(this, "App", "Changed: " + QString::number(val));
			});
		gl->addWidget(slider, 0, 0, 6, 1);
		gl->addWidget(new QLabel("10"), 0, 1, 1, 1);
		gl->addWidget(new QLabel("5"), 5, 1, 1, 1);
		MainLayout->addLayout(gl);
		auto hl = new QVBoxLayout();
		auto g = new QGroupBox("Others");
		s = new QSpinBox();
		s->setValue(10);
		s->setMinimum(10);
		s->setMaximum(20);
		connect(s, &QSpinBox::valueChanged, [&](int v) {
			nrtogen = v;
			});
		auto lg = new QHBoxLayout();
		g->setLayout(lg);
		lg->addWidget(s);
		hl->addWidget(g);
		auto cb = new QComboBox();
		cb->addItem("blue");
		cb->addItem("purple");
		connect(cb, &QComboBox::currentIndexChanged, [&](int index) {
			color1 = index ? Qt::darkMagenta : Qt::blue;
			});
		b1 = new QRadioButton("white");
		b2 = new QRadioButton("yellow");
		b1->setChecked(1);
		auto btn = new QPushButton("update");
		connect(btn, &QPushButton::clicked, [&] {
			color2 = b1->isChecked() ? Qt::white : Qt::yellow;
			});
		hl->addWidget(cb);
		hl->addWidget(b1);
		hl->addWidget(b2);
		hl->addWidget(btn);
		auto ll = new QFormLayout();
		l1 = new QLineEdit();
		l2 = new QLineEdit();
		ll->addRow(new QLabel("a"), l1);
		ll->addRow(new QLabel("b"), l2);
		auto bbtn = new QPushButton("show");

		connect(bbtn, &QPushButton::clicked, [&] {
			QMessageBox::information(this, "App", l1->text() + l2->text());
			//auto bb = new QHBoxLayout;
			//hl->removeItem(aa);
			//ClearLayout(aa);
			QLayoutItem* x;
			while (x = aa->takeAt(0))
				delete x->widget();
			auto l1 = new QLabel({ (char)('a' + rand() % 26) });
			auto l2 = new QLabel({ (char)('a' + rand() % 26) });
			auto l3 = new QLabel({ (char)('a' + rand() % 26) });
			aa->addWidget(l1);
			aa->addWidget(l2);
			aa->addWidget(l3);
			//ClearLayout(aa);
			//delete aa->layout();
			//aa = new QHBoxLayout;
			//hl->addLayout(bb);
			});
		ll->addWidget(bbtn);
		hl->addLayout(ll);
		MainLayout->addLayout(hl);
		setLayout(MainLayout);
		aa = new QHBoxLayout;
		auto l1 = new QLabel("a");
		auto l2 = new QLabel("b");
		auto l3 = new QLabel("c");
		aa->addWidget(l1);
		aa->addWidget(l2);
		aa->addWidget(l3);
		hl->addLayout(aa);

	}
	~Practice();

private:
	Ui::PracticeClass ui;
};
