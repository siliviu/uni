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
#include <qpainter.h>
#include <qtableview.h>
#include "util.h"

class ActivityTable : public QTableWidget, public Observer {
	Service& s;
public:
	ActivityTable(Service& _s);
	void Reload(const std::vector<Activity>& v);
protected:
	virtual void AddRow(const Activity& a);
	void Update() override;
};

class ActivityList : public QListWidget, public Observer {
	Service& s;
public:
	ActivityList(Service& _s);
	void Reload(const std::vector<Activity>& v);
protected:
	void Update() override;
	void AddRow(const Activity& a);
};

class GUI;

class DynamicButtons : public QVBoxLayout, public Observer {
public:
	DynamicButtons(Service& _s);
private:
	Service& s;
	std::vector<DTO> currentReport;
	void ClearLayout(QLayout* layout);
protected:
	void Update() override;
};

class MainActivityView : public QTableView, public Observer {
private:
	GUI* g;
public:
	MainActivityView(GUI* _g);
protected:
	void Update() override;
};

class MainActivityModel : public QAbstractTableModel {
	Q_OBJECT
private:
	Service& s;
public:
	MainActivityModel(Service& _s);

	int rowCount(const QModelIndex& parent = QModelIndex()) const override;
	int columnCount(const QModelIndex& parent = QModelIndex()) const override;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
	bool setData(const QModelIndex& index, const QVariant& value, int role) override;
	Qt::ItemFlags flags(const QModelIndex& index) const override;
};

class GUI : public QWidget {
	friend class MainActivityTable;
	friend class MainActivityView;
private:
	Service& s;
	MainActivityModel* ActivityModel;
	MainActivityView* ActivityView;
	ActivityTable* ActivityTable, * OperationTable;
	ActivityList* SelectedTable;
	QWidget* q;
	QLineEdit* title, * desc, * type, * len, * file, * search, * filter;
	QRadioButton* Sort1, * Sort2, * Sort3, * Filter1, * Filter2;
	DynamicButtons* DynLayout;

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

		ActivityView = new MainActivityView(this);
		ActivityModel = new MainActivityModel(s);
		ActivityView->setModel(ActivityModel);
		s.AddObserver(ActivityView);

		ActivityLayout->addWidget(ActivityView);


		//Selected Panel
		auto SelectedPanel = new QGroupBox("Current Activity List");
		auto SelectedLayout = new QVBoxLayout;
		SelectedPanel->setLayout(SelectedLayout);

		SelectedTable = new ::ActivityList(s);
		s.AddObserver(SelectedTable);
		SelectedLayout->addWidget(SelectedTable);

		auto PanelButtons = new QWidget(SelectedPanel);
		auto PanelButtonLayout = new QHBoxLayout;
		PanelButtons->setLayout(PanelButtonLayout);

		auto ClearButton = new QPushButton("Clear", PanelButtons);
		QObject::connect(ClearButton, &QPushButton::clicked, [&] {s.ClearSelected(); });
		PanelButtonLayout->addWidget(ClearButton);

		auto PopulateButton = new QPushButton("Populate", PanelButtons);
		QObject::connect(PopulateButton, &QPushButton::clicked, this, &GUI::PopulateMenu);
		PanelButtonLayout->addWidget(PopulateButton);

		auto ExportButton = new QPushButton("Export", PanelButtons);
		QObject::connect(ExportButton, &QPushButton::clicked, this, &GUI::ExportMenu);
		PanelButtonLayout->addWidget(ExportButton);

		auto CRUDButton = new QPushButton("CRUD GUI", PanelButtons);
		QObject::connect(CRUDButton, &QPushButton::clicked, this, &GUI::CRUDMenu);
		PanelButtonLayout->addWidget(CRUDButton);

		auto ReadOnlyButton = new QPushButton("Read-Only GUI", PanelButtons);
		QObject::connect(ReadOnlyButton, &QPushButton::clicked, this, &GUI::ReadOnlyMenu);
		PanelButtonLayout->addWidget(ReadOnlyButton);

		SelectedLayout->addWidget(PanelButtons);

		// Dynamic Buttons
		auto DynButtons = new QGroupBox("Activity Titles");
		DynLayout = new DynamicButtons(s);
		s.AddObserver(DynLayout);
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

		RightPanel->setMaximumWidth(450);
		setWindowState(Qt::WindowMaximized);
		s.Notify();
	}
	void RemoveActivity(int pos) {
		s.Remove(pos);
	}

	void AddActivitySelected(const std::string& t) {
		s.AddSelected(t);
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
			s.Notify();
			});

		HPanel->setLayout(HLayout);

		OperationTable = new ::ActivityTable(s);
		s.AddObserver(OperationTable);
		Layout->addWidget(OperationTable);

		q->setLayout(Layout);
		q->setMinimumWidth(300);
		s.Notify();
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


	void CRUDMenu() {
		q = new QWidget;
		q->setWindowTitle("CRUD menu");

		auto SelectedLayout = new QVBoxLayout;
		q->setLayout(SelectedLayout);

		auto NewSelectedTable = new ::ActivityList(s);
		s.AddObserver(NewSelectedTable);
		SelectedLayout->addWidget(NewSelectedTable);

		auto PanelButtons = new QWidget(q);
		auto PanelButtonLayout = new QHBoxLayout;
		PanelButtons->setLayout(PanelButtonLayout);

		auto PopulateButton = new QPushButton("Populate", PanelButtons);
		QObject::connect(PopulateButton, &QPushButton::clicked, this, &GUI::PopulateMenu);
		PanelButtonLayout->addWidget(PopulateButton);

		auto ClearButton = new QPushButton("Clear", PanelButtons);
		QObject::connect(ClearButton, &QPushButton::clicked, [&] {s.ClearSelected(); });
		PanelButtonLayout->addWidget(ClearButton);

		SelectedLayout->addWidget(PanelButtons);

		q->setMinimumWidth(300);
		s.Notify();
		q->show();
	}

	void ReadOnlyMenu() {
		class Window : public QWidget, public Observer {
			Service& s;
		public:
			Window(Service& _s) :s(_s) {}
		protected:
			void Update() override {
				repaint();
			}
			void paintEvent(QPaintEvent* ev) override {
				ev;
				QPainter p(this);
				for (auto _ : s.GetSelected())
					p.drawImage(rand() % (width() - 150), rand() % (height() - 150), QImage("pentagram.png"));
			}
		};

		auto qq = new Window(s);
		s.AddObserver(qq);
		qq->setWindowTitle("Read-Only menu");


		qq->setMinimumWidth(300);
		s.Notify();
		qq->show();
	}

public:
	GUI(Service& _s);

	~GUI() {}
};