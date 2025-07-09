#include "practiceexamen.h"
#include <QtWidgets/QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
    std::cout << "HAHA";
    QApplication a(argc, argv);
    practiceexamen w;
    w.show();
    return a.exec();
}