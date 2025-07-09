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

void MainActivityView::Update() {
	emit model()->layoutChanged();
}

MainActivityView::MainActivityView(GUI* _g) : g(_g) {
	setEditTriggers(QAbstractItemView::DoubleClicked);
	setSelectionBehavior(QAbstractItemView::SelectRows);
	setContextMenuPolicy(Qt::CustomContextMenu);
	QObject::connect(this, &QTableView::customContextMenuRequested, [&](QPoint pos) {
		int selected = indexAt(pos).row();
		if (selected < 0 || selected >= model()->rowCount())
			return;
		QMenu* menu = new QMenu(this);
		QObject::connect(menu, &QMenu::triggered, [&](QAction* q) {
			int count = 0;
			for (const auto& row : selectionModel()->selectedRows()) {
				if (q->text() == "Remove activity")
					g->RemoveActivity(row.row() - count);
				else
					g->AddActivitySelected(model()->data(model()->index(row.row(), 0)).toString().toStdString());
				++count;
			}
			});
		menu->addAction(new QAction("Remove activity", menu));
		menu->addAction(new QAction("Add title to selected", menu));
		menu->popup(viewport()->mapToGlobal(pos));
		});
}

MainActivityModel::MainActivityModel(Service& _s) : s(_s) {
}

Qt::ItemFlags MainActivityModel::flags(const QModelIndex& index) const
{
	return Qt::ItemIsEditable | QAbstractTableModel::flags(index);
}

int MainActivityModel::rowCount(const QModelIndex&) const
{
	return (int)s.GetAll().size();
}

int MainActivityModel::columnCount(const QModelIndex&) const
{
	return 4;
}

QVariant MainActivityModel::data(const QModelIndex& index, int role) const
{
	if (role == Qt::DisplayRole) {
		auto e = s.GetAll()[index.row()];
		int col = index.column();
		return QString::fromStdString(
			col == 0 ? e.GetDescription() :
			col == 1 ? e.GetTitle() :
			col == 2 ? e.GetType() :
			std::to_string(e.GetLength())
		);
	}

	return QVariant();
}

bool MainActivityModel::setData(const QModelIndex& index, const QVariant& value, int role) {
	if (role == Qt::EditRole) {
		if (!checkIndex(index))
			return false;
		int row = index.row(), col = index.column();
		auto e = s.GetAll()[row];
		try {
			s.Modify(row,
				col == 0 ? value.toString().toStdString() : e.GetTitle(),
				col == 1 ? value.toString().toStdString() : e.GetDescription(),
				col == 2 ? value.toString().toStdString() : e.GetType(),
				col == 3 ? value.toString().toInt() : e.GetLength());
		}
		catch (const AppException& e) {
			std::stringstream ss;
			ss << e;
			QMessageBox::warning(0, "Error", QString::fromStdString((std::stringstream() << e).str()));
			return false;
		}
		return true;
	}
	return false;
}