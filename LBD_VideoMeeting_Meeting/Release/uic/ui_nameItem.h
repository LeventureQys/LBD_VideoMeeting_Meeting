/********************************************************************************
** Form generated from reading UI file 'nameItem.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NAMEITEM_H
#define UI_NAMEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_nameItem
{
public:
    QWidget *widget;
    QLabel *lab_mic;
    QLabel *lab_name;

    void setupUi(QWidget *nameItem)
    {
        if (nameItem->objectName().isEmpty())
            nameItem->setObjectName(QStringLiteral("nameItem"));
        nameItem->resize(94, 32);
        widget = new QWidget(nameItem);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 94, 32));
        widget->setStyleSheet(QStringLiteral("background-color: rgba(0, 0, 0,0.2);"));
        lab_mic = new QLabel(widget);
        lab_mic->setObjectName(QStringLiteral("lab_mic"));
        lab_mic->setGeometry(QRect(15, 7, 14, 18));
        lab_mic->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/mic_White.png);"));
        lab_name = new QLabel(widget);
        lab_name->setObjectName(QStringLiteral("lab_name"));
        lab_name->setGeometry(QRect(32, 10, 54, 12));

        retranslateUi(nameItem);

        QMetaObject::connectSlotsByName(nameItem);
    } // setupUi

    void retranslateUi(QWidget *nameItem)
    {
        nameItem->setWindowTitle(QApplication::translate("nameItem", "nameItem", nullptr));
        lab_mic->setText(QString());
        lab_name->setText(QApplication::translate("nameItem", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class nameItem: public Ui_nameItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NAMEITEM_H
