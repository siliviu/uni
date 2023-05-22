#include "gui.h"

GUI::GUI(Service& _s) : s(_s) {
	Initialise();
}

ActivityList::ActivityList() {

}

void ActivityList::AddRow(const Activity& a) {
	addItem(new QListWidgetItem(QString::fromStdString(a.GetTitle())));

}

void ActivityList::Reload(const std::vector<Activity>& v) {
	clear();
	for (const auto& x : v)
		AddRow(x);
}

ActivityTable::ActivityTable() : QTableWidget(0, 4) {
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

MainActivityTable::MainActivityTable(GUI* _g) : g(_g) {
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
