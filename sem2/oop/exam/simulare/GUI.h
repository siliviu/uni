#pragma once

#include <QtWidgets/QWidget>
#include <qtablewidget.h>
#include <qboxlayout.h>
#include <qformlayout.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qlistwidget.h>
#include "Service.h"
#include <iostream>

class Window : public QWidget, public Observer {
	QListWidget* list;
	Service& s;
	std::string state;
	void Reload() {
		const auto& all = s.Filter(state);
		list->clear();
		for (const auto& x : all)
			list->addItem(new QListWidgetItem("Id: " + QString::number(x.getId()) + ", State: " + QString::fromStdString(state)));
	}
public:

	Window(Service& _s, std::string _state) : s(_s), state(_state) {
		list = new QListWidget();
		auto Layout = new QHBoxLayout();
		Layout->addWidget(list);
		auto BLayout = new QVBoxLayout();
		auto btn1 = new QPushButton("Open");
		connect(btn1, &QPushButton::clicked, [&] {
			int index = list->currentIndex().row();
			int id = s.Filter(state)[index].getId();
			s.ChangeState(id, "open");
			});
		auto btn2 = new QPushButton("Inprogress");
		connect(btn2, &QPushButton::clicked, [&] {
			int index = list->currentIndex().row();
			int id = s.Filter(state)[index].getId();
			s.ChangeState(id, "inprogress");
			});
		auto btn3 = new QPushButton("Close");
		connect(btn3, &QPushButton::clicked, [&] {
			int index = list->currentIndex().row();
			int id = s.Filter(state)[index].getId();
			s.ChangeState(id, "closed");
			});
		BLayout->addWidget(btn1);
		BLayout->addWidget(btn2);
		BLayout->addWidget(btn3);
		Layout->addLayout(BLayout);
		setLayout(Layout);
	}
	void Update() override {
		Reload();
	}
};

class GUI : public QWidget, public Observer
{
	Q_OBJECT
private:
	Service& s;
	QTableWidget* table;
	QLineEdit* id, * desc, * state, * p1, * p2, * p3, * p4, * search;
	QPushButton* btn;
	void Reload() {
		const auto& all = s.Get(search->text().toStdString());
		table->setRowCount(all.size());
		table->setColumnCount(4);
		int i = 0;
		for (const auto& x : all) {
			table->setItem(i, 0, new QTableWidgetItem(QString::number(x.getId())));
			table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(x.getDesc())));
			table->setItem(i, 2, new QTableWidgetItem(QString::fromStdString(x.getState())));
			table->setItem(i, 3, new QTableWidgetItem(QString::number(x.getProgrammers().size())));
			i++;
		}
		table->update();
	}
public:
	void Update() {
		Reload();
	}
	GUI(Service& _s) :s(_s) {
		s.AddObserver(this);
		table = new QTableWidget();
		table->setHorizontalHeaderLabels(QStringList{ "ID","Descriere","Stare","Numar programatori" });
		auto Layout = new QHBoxLayout();
		Layout->addWidget(table);
		auto FLayout = new QFormLayout();
		id = new QLineEdit();
		desc = new QLineEdit();
		state = new QLineEdit();
		p1 = new QLineEdit();
		p2 = new QLineEdit();
		p3 = new QLineEdit();
		p4 = new QLineEdit();
		FLayout->addRow(new QLabel("Id: "), id);
		FLayout->addRow(new QLabel("Desc: "), desc);
		FLayout->addRow(new QLabel("Stare: "), state);
		FLayout->addRow(new QLabel("Programator 1: "), p1);
		FLayout->addRow(new QLabel("Programator 2: "), p2);
		FLayout->addRow(new QLabel("Programator 3: "), p3);
		FLayout->addRow(new QLabel("Programator 4: "), p4);
		btn = new QPushButton("Adauga");
		FLayout->addWidget(btn);
		connect(btn, &QPushButton::clicked, [&] {
			int _id = id->text().toInt();
			std::string _desc = desc->text().toStdString();
			std::string _state = state->text().toStdString();
			std::string _p1 = p1->text().toStdString();
			std::string _p2 = p2->text().toStdString();
			std::string _p3 = p3->text().toStdString();
			std::string _p4 = p4->text().toStdString();
			std::vector<std::string> p;
			if (!_p1.empty()) p.emplace_back(_p1);
			if (!_p2.empty()) p.emplace_back(_p2);
			if (!_p3.empty()) p.emplace_back(_p3);
			if (!_p4.empty()) p.emplace_back(_p4);
			try {
				s.Add(_id, _desc, p, _state);
				Reload();
			}
			catch (std::exception) {
				QMessageBox::warning(0, "Eroare", "Date introduse nevalide!");
			}
			});
		Layout->addLayout(FLayout);
		auto Search = new QLabel("Cauta: ");
		search = new QLineEdit();
		connect(search, &QLineEdit::textChanged, [&] {
			Reload();
			});
		Layout->addWidget(Search);
		Layout->addWidget(search);
		setLayout(Layout);
		Window* a = new Window(s, "open");
		a->show();
		s.AddObserver(a);
		Window* b = new Window(s, "inprogress");
		b->show();
		s.AddObserver(b);
		Window* c = new Window(s, "closed");
		c->show();
		s.AddObserver(c);
		s.Notify();
	}
};
