/********************************************************************************
** Form generated from reading UI file 'Practice.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRACTICE_H
#define UI_PRACTICE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PracticeClass
{
public:

    void setupUi(QWidget *PracticeClass)
    {
        if (PracticeClass->objectName().isEmpty())
            PracticeClass->setObjectName("PracticeClass");
        PracticeClass->resize(600, 400);

        retranslateUi(PracticeClass);

        QMetaObject::connectSlotsByName(PracticeClass);
    } // setupUi

    void retranslateUi(QWidget *PracticeClass)
    {
        PracticeClass->setWindowTitle(QCoreApplication::translate("PracticeClass", "Practice", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PracticeClass: public Ui_PracticeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRACTICE_H
