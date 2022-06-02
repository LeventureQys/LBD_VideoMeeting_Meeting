/********************************************************************************
** Form generated from reading UI file 'TnameItem.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TNAMEITEM_H
#define UI_TNAMEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_TnameItem
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;

    void setupUi(QWidget *TnameItem)
    {
        if (TnameItem->objectName().isEmpty())
            TnameItem->setObjectName(QStringLiteral("TnameItem"));
        TnameItem->resize(133, 32);
        TnameItem->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0,0.2);"));
        label = new QLabel(TnameItem);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 4, 72, 24));
        label->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/TeacherIcon.png);\n"
"color: rgb(255, 255, 255);\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
""));
        label->setAlignment(Qt::AlignCenter);
        label_2 = new QLabel(TnameItem);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(91, 7, 14, 18));
        label_2->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/mic_White.png);"));
        label_3 = new QLabel(TnameItem);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(110, 10, 16, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));

        retranslateUi(TnameItem);

        QMetaObject::connectSlotsByName(TnameItem);
    } // setupUi

    void retranslateUi(QWidget *TnameItem)
    {
        TnameItem->setWindowTitle(QApplication::translate("TnameItem", "Form", nullptr));
        label->setText(QApplication::translate("TnameItem", "\344\270\212\350\257\276\350\200\201\345\270\210", nullptr));
        label_2->setText(QString());
        label_3->setText(QApplication::translate("TnameItem", "\346\210\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class TnameItem: public Ui_TnameItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TNAMEITEM_H
