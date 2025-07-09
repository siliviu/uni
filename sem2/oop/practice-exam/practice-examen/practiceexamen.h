#pragma once

#include "ui_practiceexamen.h"
#include <qtableview.h>
#include <qboxlayout.h>
#include <qpushbutton.h>
#include <qlineedit>
#include <qmessagebox.h>
#include <qitemselectionmodel.h>
#include <qpainter.h>
#include <qwidget.h>
#include <qlistview.h>
#include <QMouseEvent>

class QTableModel : public QAbstractTableModel {
	Q_OBJECT
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return 10;
	}
	int columnCount(const QModelIndex& parent = QModelIndex()) const override {
		return 4;
	}
	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::DisplayRole)
			return QString::fromStdString(std::to_string(index.row()) + " " + std::to_string(index.column()) + " " + std::to_string(time(0)));
		else if (role == Qt::BackgroundRole)
			if ((index.row() + index.column()) % 2)
				return QBrush(Qt::yellow);
		return QVariant();
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("first");
			case 1:
				return QString("second");
			case 2:
				return QString("third");
			case 3:
				return QString("fourth");
			}
		}
		return QVariant();
	}

};


class QListModel : public QAbstractListModel {
	Q_OBJECT
public:
	int rowCount(const QModelIndex& parent = QModelIndex()) const override {
		return 10;
	}
	QVariant data(const QModelIndex& index, int role) const override {
		if (role == Qt::DisplayRole)
			return QString::fromStdString(std::to_string(index.row()));
		else if (role == Qt::BackgroundRole)
			if ((index.row() + index.column()) % 2)
				return QBrush(Qt::yellow);
		return QVariant();
	}
	QVariant headerData(int section, Qt::Orientation orientation, int role) const {
		if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
			switch (section) {
			case 0:
				return QString("first");
			}
		}
		return QVariant();
	}

};

class practiceexamen : public QWidget
{
	Q_OBJECT
private:
	QTableView* qv;
	QTableModel* qm;
	QLineEdit* le;
	QItemSelectionModel* qs;
public:
	~practiceexamen();
	practiceexamen() {
		auto l = new QHBoxLayout();
		qv = new QTableView();
		qm = new QTableModel();
		qv->setSelectionBehavior(QAbstractItemView::SelectRows);
		qv->setSelectionMode(QAbstractItemView::SingleSelection);
		qv->setModel(qm);
		l->addWidget(qv);
		qs = qv->selectionModel();
		connect(qs, &QItemSelectionModel::selectionChanged, [&]() {
			le->setText(QString::number(qs->selectedRows()[0].row() + 1));
			});
		le = new QLineEdit();
		connect(le, &QLineEdit::textChanged, [&]() {
			update();
			});
		l->addWidget(le);
		auto b = new QPushButton("Press");
		l->addWidget(b);
		connect(b, &QPushButton::clicked, [&] {
			qm->layoutChanged();
			});
		setLayout(l);
	}
	void mousePressEvent(QMouseEvent* qq) override {
		auto p = qq->pos();
		if (900 <= p.x() && p.x() <= 900 + (le->text().toInt() - 1) * 50 + 50 && 150 <= p.y() && p.y() <= 150 + 50)
			le->setText(QString::number(le->text().toInt() - 1));
	}

	void paintEvent(QPaintEvent* ev) override {
		QPainter p{ this };
		p.setBrush(Qt::red);
		p.setPen(Qt::black);
		for (int i = 0; i < le->text().toInt(); ++i)
			p.drawEllipse(900 + i * 50, 150, 50, 50);
		for (int i = 0; i < le->text().toInt(); ++i)
			p.drawRect(900 + i * 25, 225, 25, 50);
		p.drawRect(900, 300, 25 * le->text().toInt(), 50);
		int r = 20 + 5 * le->text().toInt();
		p.drawEllipse(900 - r / 2, 400 - r / 2, r, r);
	}
private:
	Ui::practiceexamenClass ui;
};
