#pragma once

#include <QtWidgets/QMainWindow>
#include <qboxlayout.h>
#include <qtablewidget.h>
#include <qheaderview.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include <qmenu.h>
#include <qgroupbox.h>
#include <qexception.h>
#include <qlistwidget.h>
#include <qradiobutton.h>
#include "util.h"

class ActivityTable : public QTableWidget {
public:
	ActivityTable();
	void Reload(const std::vector<Activity>& v);
protected:
	virtual void AddRow(const Activity& a);
};

class ActivityList : public QListWidget {
public:
	ActivityList();
	void Reload(const std::vector<Activity>& v);
protected:
	void AddRow(const Activity& a);
};

class GUI;

class MainActivityTable : public ActivityTable {
public:
	MainActivityTable(GUI* _g);
private:
	GUI* g;
	QMetaObject::Connection c;
protected:
	void AddRow(const Activity& a);
};

class GUI : public QWidget {
	friend class MainActivityTable;
private:
	Service& s;

	ActivityTable* ActivityTable;
	ActivityList* SelectedTable, * OperationTable;
	QWidget* q;
	QLineEdit* title, * desc, * type, * len, * file, * search, * filter;
	QRadioButton* Sort1, * Sort2, * Sort3, * Filter1, * Filter2;
	QVBoxLayout* DynLayout;
	std::vector<DTO> currentReport;

	void Initialise() {
		auto AppLayout = new QHBoxLayout;

		auto LeftPanel = new QWidget;
		auto LeftPanelLayout = new QVBoxLayout;
		LeftPanel->setLayout(LeftPanelLayout);
		AppLayout->addWidget(LeftPanel);

		// Activity Panel
		auto ActivityPanel = new QGroupBox("Activity list");
		auto ActivityLayout = new QVBoxLayout;
		ActivityPanel->setLayout(ActivityLayout);

		ActivityTable = new ::MainActivityTable(this);
		ActivityLayout->addWidget(ActivityTable);


		//Selected Panel
		auto SelectedPanel = new QGroupBox("Current Activity List");
		auto SelectedLayout = new QVBoxLayout;
		SelectedPanel->setLayout(SelectedLayout);

		SelectedTable = new ::ActivityList();
		SelectedLayout->addWidget(SelectedTable);

		auto PanelButtons = new QWidget(SelectedPanel);
		auto PanelButtonLayout = new QHBoxLayout;
		PanelButtons->setLayout(PanelButtonLayout);

		auto ClearButton = new QPushButton("Clear", PanelButtons);
		QObject::connect(ClearButton, &QPushButton::clicked, [&] {s.ClearSelected(); SelectedTable->Reload(s.GetSelected()); });
		PanelButtonLayout->addWidget(ClearButton);

		auto PopulateButton = new QPushButton("Populate", PanelButtons);
		QObject::connect(PopulateButton, &QPushButton::clicked, this, &GUI::PopulateMenu);
		PanelButtonLayout->addWidget(PopulateButton);

		auto ExportButton = new QPushButton("Export", PanelButtons);
		QObject::connect(ExportButton, &QPushButton::clicked, this, &GUI::ExportMenu);
		PanelButtonLayout->addWidget(ExportButton);

		SelectedLayout->addWidget(PanelButtons);

		// Dynamic Buttons
		auto DynButtons = new QGroupBox("Activity Titles");
		DynLayout = new QVBoxLayout;
		DynButtons->setLayout(DynLayout);
		AppLayout->addWidget(DynButtons);

		// Buttons
		auto RightPanel = new QWidget;
		auto RightPanelLayout = new QVBoxLayout;
		RightPanel->setLayout(RightPanelLayout);
		AppLayout->addWidget(RightPanel);

		auto ButtonsPanel = new QWidget;
		auto ButtonsLayout = new QHBoxLayout;
		ButtonsPanel->setLayout(ButtonsLayout);
		auto bAdd = new QPushButton("Add");
		QObject::connect(bAdd, &QPushButton::clicked, this, &GUI::AddMenu);
		ButtonsLayout->addWidget(bAdd);

		auto bOperations = new QPushButton("Operations");
		QObject::connect(bOperations, &QPushButton::clicked, this, &GUI::OperationMenu);
		ButtonsLayout->addWidget(bOperations);

		auto bReport = new QPushButton("Report");
		QObject::connect(bReport, &QPushButton::clicked, this, &GUI::ReportMenu);
		ButtonsLayout->addWidget(bReport);

		auto bUndo = new QPushButton("Undo");
		QObject::connect(bUndo, &QPushButton::clicked, this, &GUI::UndoMenu);
		ButtonsLayout->addWidget(bUndo);

		LeftPanelLayout->addWidget(ActivityPanel);
		ActivityLayout->addWidget(ButtonsPanel);
		RightPanelLayout->addWidget(SelectedPanel);

		setLayout(AppLayout);
		adjustSize();
		ActivityTable->Reload(s.GetAll());
		SelectedTable->Reload(s.GetSelected());
		UpdateButtons();

		RightPanel->setMaximumWidth(450);
		setWindowState(Qt::WindowMaximized);
	}
	void ModifyActivity(int pos, const std::string& ti, const std::string& d, const std::string& ty, int length) {
		try {
			s.Modify(pos, ti, d, ty, length);
			UpdateButtons();
		}
		catch (const AppException& e) {
			std::stringstream ss;
			ss << e;
			QMessageBox::warning(this, "Error", QString::fromStdString((std::stringstream() << e).str()));
			ActivityTable->Reload(s.GetAll());
		}
	}
	void RemoveActivity(int pos) {
		s.Remove(pos);
		ActivityTable->Reload(s.GetAll());
		UpdateButtons();
	}
	void AddActivitySelected(const std::string& t) {
		s.AddSelected(t);
		SelectedTable->Reload(s.GetSelected());
	}
	void AddMenu() {
		q = new QWidget();
		q->setWindowTitle("Add menu");
		auto l = new QFormLayout;
		title = new QLineEdit;
		l->addRow(new QLabel("Title: "), title);
		desc = new QLineEdit;
		l->addRow(new QLabel("Description: "), desc);
		type = new QLineEdit;
		l->addRow(new QLabel("Type: "), type);
		len = new QLineEdit;
		l->addRow(new QLabel("Length: "), len);
		auto button = new QPushButton("Add activity");
		button->setAutoDefault(true);
		l->addWidget(button);
		q->setLayout(l);
		q->adjustSize();
		q->show();
		QObject::connect(button, &QPushButton::pressed, [&] {
			try {
				s.Add(title->text().toStdString(), desc->text().toStdString(), type->text().toStdString(), len->text().toInt());
				title->clear(), desc->clear(), type->clear(), len->clear();
				ActivityTable->Reload(s.GetAll());
				UpdateButtons();
			}
			catch (const AppException& e) {
				std::stringstream ss;
				ss << e;
				QMessageBox::warning(q, "Error", QString::fromStdString((std::stringstream() << e).str()));
			}
			});
	}
	void UndoMenu() {
		try {
			s.Undo();
			ActivityTable->Reload(s.GetAll());
			UpdateButtons();
		}
		catch (const AppException& e) {
			std::stringstream ss;
			ss << e;
			QMessageBox::warning(this, "Error", QString::fromStdString((std::stringstream() << e).str()));
		}
	}
	void PopulateMenu() {
		q = new QWidget;
		q->setWindowTitle("Populate menu");
		auto l = new QVBoxLayout;
		l->addWidget(new QLabel("Enter the number of items: "));
		file = new QLineEdit;
		l->addWidget(file);
		auto button = new QPushButton("Populate");
		button->setAutoDefault(true);
		l->addWidget(button);
		q->setLayout(l);
		q->adjustSize();
		q->show();
		QObject::connect(button, &QPushButton::clicked, [&] {
			try {
				s.PopulateSelected(file->text().toInt());
				SelectedTable->Reload(s.GetSelected());
				q->close();
			}
			catch (const AppException& e) {
				std::stringstream ss;
				ss << e;
				QMessageBox::warning(q, "Error", QString::fromStdString((std::stringstream() << e).str()));
			}
			});
	}
	void ExportMenu() {
		q = new QWidget;
		q->setWindowTitle("Export menu");
		auto l = new QVBoxLayout;
		l->addWidget(new QLabel("Enter the name of the file: "));
		file = new QLineEdit;
		l->addWidget(file);
		auto button = new QPushButton("Export");
		button->setAutoDefault(true);
		l->addWidget(button);
		q->setLayout(l);
		q->adjustSize();
		q->show();
		QObject::connect(button, &QPushButton::clicked, [&] {
			try {
				s.SaveSelected(file->text().toStdString());
				q->close();
				QMessageBox::information(q, "Information", QString::fromStdString("Saved successfully!"));

			}
			catch (const AppException& e) {
				std::stringstream ss;
				ss << e;
				QMessageBox::warning(q, "Error", QString::fromStdString((std::stringstream() << e).str()));
			}
			});
	}

	void OperationMenu() {
		q = new QWidget;
		q->setWindowTitle("Operation menu");
		auto Layout = new QVBoxLayout;
		auto HPanel = new QWidget;
		Layout->addWidget(HPanel);
		auto HLayout = new QHBoxLayout;

		auto FilterBox = new QGroupBox("Filter List");
		auto FilterLayout = new QVBoxLayout();
		FilterBox->setLayout(FilterLayout);

		Filter1 = new QRadioButton("By description");
		FilterLayout->addWidget(Filter1);
		Filter2 = new QRadioButton("By type");
		FilterLayout->addWidget(Filter2);
		filter = new QLineEdit();
		FilterLayout->addWidget(filter);
		auto FilterButton = new QPushButton("Filter");
		FilterLayout->addWidget(FilterButton);
		QObject::connect(FilterButton, &QPushButton::clicked, [&] {
			OperationTable->Reload(s.Filter(filter->text().toStdString(), Filter1->isChecked() ? 0 : 1));
			});
		HLayout->addWidget(FilterBox);

		auto SortBox = new QGroupBox("Sort List");
		auto SortLayout = new QVBoxLayout;
		SortBox->setLayout(SortLayout);
		Sort1 = new QRadioButton("By title");
		SortLayout->addWidget(Sort1);
		Sort2 = new QRadioButton("By description");
		SortLayout->addWidget(Sort2);
		Sort3 = new QRadioButton("By type + length");
		SortLayout->addWidget(Sort3);
		auto SortButton = new QPushButton("Sort");
		SortLayout->addWidget(SortButton);
		QObject::connect(SortButton, &QPushButton::clicked, [&] {
			OperationTable->Reload(s.Sort(Sort1->isChecked() ? 0 : Sort2->isChecked() ? 1 : 2));
			});
		HLayout->addWidget(SortBox);

		auto SearchBox = new QGroupBox("Search List");
		auto SearchLayout = new QVBoxLayout;
		SearchBox->setLayout(SearchLayout);
		search = new QLineEdit();
		SearchLayout->addWidget(search);
		auto SearchButton = new QPushButton("Search");
		QObject::connect(SearchButton, &QPushButton::clicked, [&] {
			OperationTable->Reload(s.Search(search->text().toStdString()));
			});
		SearchLayout->addWidget(SearchButton);
		HLayout->addWidget(SearchBox);

		auto Reset = new QPushButton("Reset");
		HLayout->addWidget(Reset);
		QObject::connect(Reset, &QPushButton::clicked, [&] {
			OperationTable->Reload(s.GetAll());
			});

		HPanel->setLayout(HLayout);

		OperationTable = new ::ActivityList();
		Layout->addWidget(OperationTable);

		q->setLayout(Layout);
		q->setMinimumWidth(300);
		OperationTable->Reload(s.GetAll());
		q->show();
	}

	void ReportMenu() {
		auto t = new QTableWidget(0, 2);
		t->setWindowTitle("Report");
		QStringList Header;
		Header << "Activity title" << "Number";
		t->setHorizontalHeaderLabels(Header);
		for (auto& [x, y] : s.Report()) {
			int r = t->rowCount();
			t->insertRow(r);
			t->setItem(r, 0, new QTableWidgetItem(QString::fromStdString(x)));
			t->setItem(r, 1, new QTableWidgetItem(QString::number(y)));
		}
		t->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		t->setEditTriggers(QAbstractItemView::NoEditTriggers);
		t->show();
	}

	void ClearLayout(QLayout* layout) {
		if (layout == NULL)
			return;
		QLayoutItem* item;
		while ((item = layout->takeAt(0))) {
			if (item->layout()) {
				ClearLayout(item->layout());
				delete item->layout();
			}
			if (item->widget())
				delete item->widget();
			delete item;
		}
	}

	void UpdateButtons() {
		ClearLayout(DynLayout);
		currentReport = s.Report();
		for (const auto& [x, y] : currentReport) {
			auto b = new QPushButton(QString::fromStdString(x));
			QObject::connect(b, &QPushButton::clicked, [&] {
				QMessageBox::information(this, QString::fromStdString(x), "Number of activities with title " + QString::fromStdString(x) + ": " + QString::number(y));
				});
			DynLayout->addWidget(b);
		}
	}
public:
	GUI(Service& _s);

	~GUI() {}
};