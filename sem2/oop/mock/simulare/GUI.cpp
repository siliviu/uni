#include "gui.h"

void GUI::Reload() {
	l->clear();
	for (auto x : s.GetAll()) {
		auto it = new QListWidgetItem(QString::fromStdString(x.name + " " + std::to_string(x.stock)));
		if (showColour)
			it->setBackground(
				x.colour == "albastru" ? Qt::blue :
				x.colour == "rosu" ? Qt::red :
				x.colour == "verde" ? Qt::green :
				Qt::magenta);
		l->addItem(it);
	}
}
