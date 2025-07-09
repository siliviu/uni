#include "gui.h"

GUI::GUI(Service& _s) : s(_s) {
	Initialise();
}

ActivityList::ActivityList(Service& _s) : s(_s) {}
void ActivityList::AddRow(const Activity& a) {
	addItem(new QListWidgetItem(QString::fromStdString(a.GetTitle())));

}
void ActivityList::Reload(const std::vector<Activity>& v) {
	clear();
	for (const auto& x : v)
		AddRow(x);
}
void ActivityList::Update() {
	Reload(s.GetSelected());
}

ActivityTable::ActivityTable(Service& _s) : QTableWidget(0, 4), s(_s) {
	QStringList Header;
	Header << "Title" << "Description" << "Type" << "Length";
	setHorizontalHeaderLabels(Header);
	horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	setEditTriggers(QAbstractItemView::NoEditTriggers);

};
void ActivityTable::AddRow(const Activity& a) {
	int r = rowCount();
	insertRow(r);
	setItem(r, 0, new QTableWidgetItem(QString::fromStdString(a.GetTitle())));
	setItem(r, 1, new QTableWidgetItem(QString::fromStdString(a.GetDescription())));
	setItem(r, 2, new QTableWidgetItem(QString::fromStdString(a.GetType())));
	setItem(r, 3, new QTableWidgetItem(QString::number(a.GetLength())));
}
void ActivityTable::Reload(const std::vector<Activity>& v) {
	setRowCount(0);
	for (const auto& x : v)
		AddRow(x);
}
void ActivityTable::Update() {
	Reload(s.GetAll());
}

MainActivityTable::MainActivityTable(GUI* _g) : g(_g), ActivityTable(_g->s) {
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	QTableWidget::setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(this, &QTableWidget::customContextMenuRequested, [&](QPoint pos) {
		int selected = indexAt(pos).row();
		if (selected < 0 || selected >= rowCount())
			return;
		QMenu* menu = new QMenu(this);
		QObject::connect(menu, &QMenu::triggered, [&](QAction* q) {
			int count = 0;
			for (const auto& row : selectionModel()->selectedRows()) {
				if (q->text() == "Remove activity")
					g->RemoveActivity(row.row() - count);
				else
					g->AddActivitySelected(item(row.row(), 0)->text().toStdString());
				++count;
			}
			});
		menu->addAction(new QAction("Remove activity", menu));
		menu->addAction(new QAction("Add title to selected", menu));
		menu->popup(viewport()->mapToGlobal(pos));
		});
}

void MainActivityTable::AddRow(const Activity& a) {
	QObject::disconnect(c);
	ActivityTable::AddRow(a);
	c = QObject::connect(this, &QTableWidget::itemChanged, g, [&](QTableWidgetItem* i) {
		g->ModifyActivity(i->row(), item(i->row(), 0)->text().toStdString(), item(i->row(), 1)->text().toStdString(), item(i->row(), 2)->text().toStdString(), item(i->row(), 3)->text().toInt());
		});
}

DynamicButtons::DynamicButtons(Service& _s) : s(_s) {}

void DynamicButtons::ClearLayout(QLayout* layout) {
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

void DynamicButtons::Update() {
	ClearLayout(this);
	currentReport = s.Report();
	for (const auto& [x, y] : currentReport) {
		auto b = new QPushButton(QString::fromStdString(x));
		QObject::connect(b, &QPushButton::clicked, [&] {
			QMessageBox::information(0, QString::fromStdString(x), "Number of activities with title " + QString::fromStdString(x) + ": " + QString::number(y));
			});
		addWidget(b);
	}
}