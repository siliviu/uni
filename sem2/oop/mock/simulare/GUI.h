#pragma once
#include "Service.h"
#include <QtWidgets/QWidget>
#include <qlistwidget.h>
#include <qlineedit>
#include <qpushbutton.h>
#include <qcheckbox.h>
#include <qlayout>
#include <qgroupbox.h>
#include <qmessagebox.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qspinbox.h>

class GUI : public QWidget {
	Q_OBJECT
private:
	Service& s;
	QListWidget* l;
	QLineEdit* name, * colour, * stock, * file;
	QSpinBox* number;
	QCheckBox* type1, * type2, * type3;
	bool showColour = false;
	void Reload();
public:
	GUI(Service& _s) : s(_s) {
		auto MainLayout = new QHBoxLayout();

		auto LeftLayout = new QVBoxLayout();

		auto g = new QGroupBox("Add item");
		auto gLayout = new QFormLayout();
		name = new QLineEdit();
		colour = new QLineEdit();
		stock = new QLineEdit();
		type1 = new QCheckBox("Elegant");
		type2 = new QCheckBox("Casual");
		type3 = new QCheckBox("Sport");
		auto gBtn = new QPushButton("Add");
		connect(gBtn, &QPushButton::clicked, [&] {
			std::string n = name->text().toStdString();
			std::string c = colour->text().toStdString();
			if (type1->isChecked() + type2->isChecked() + type3->isChecked() != 1) {
				QMessageBox::warning(this, "Warning", "You must select exactly one type!");
				return;
			}
			std::string t = type1->isChecked() ? "Elegant" : type2->isChecked() ? "Casual" : "Sport";
			int st = stock->text().toInt();
			s.Add(n, t, c, st);
			Reload();
			});
		gLayout->addRow(new QLabel("Name: "), name);
		gLayout->addWidget(type1);
		gLayout->addWidget(type2);
		gLayout->addWidget(type3);
		gLayout->addRow(new QLabel("Colour: "), colour);
		gLayout->addRow(new QLabel("Stock: "), stock);
		gLayout->addWidget(gBtn);
		g->setLayout(gLayout);
		LeftLayout->addWidget(g);

		l = new QListWidget();
		LeftLayout->addWidget(l);

		MainLayout->addLayout(LeftLayout);


		auto RightLayout = new QVBoxLayout();

		auto c = new QGroupBox("View Options");
		auto cLayout = new QVBoxLayout();
		auto vBt = new QPushButton("Show coloured");
		connect(vBt, &QPushButton::clicked, [&] {
			showColour = 1;
			Reload();
			});
		auto rBt = new QPushButton("Reset");
		connect(rBt, &QPushButton::clicked, [&] {
			showColour = 0;
			Reload();
			});
		cLayout->addWidget(vBt);
		cLayout->addWidget(rBt);
		c->setLayout(cLayout);
		RightLayout->addWidget(c);


		auto e = new QGroupBox("Export");
		auto eLayout = new QFormLayout();
		file = new QLineEdit();
		number = new QSpinBox();
		number->setMinimum(1);
		auto eBtn = new QPushButton("Export");
		connect(eBtn, &QPushButton::clicked, [&] {
			std::string file_name = file->text().toStdString();
			int nr = number->value();
			s.Export(file_name, nr);
			});
		eLayout->addRow(new QLabel("File name: "), file);
		eLayout->addRow(new QLabel("Number: "), number);
		eLayout->addWidget(eBtn);

		e->setLayout(eLayout);
		RightLayout->addWidget(e);


		MainLayout->addLayout(RightLayout);

		setLayout(MainLayout);
	};
};
