/********************************************************************************
** Form generated from reading UI file 'listItem.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LISTITEM_H
#define UI_LISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_listitem
{
public:
    QWidget *widget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton;

    void setupUi(QWidget *listitem)
    {
        if (listitem->objectName().isEmpty())
            listitem->setObjectName(QStringLiteral("listitem"));
        listitem->resize(220, 32);
        listitem->setMinimumSize(QSize(220, 0));
        listitem->setMaximumSize(QSize(220, 16777215));
        widget = new QWidget(listitem);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 0, 220, 32));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(220, 32));
        widget->setMaximumSize(QSize(220, 16777215));
        widget->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(7, 8, 18, 18));
        label->setStyleSheet(QStringLiteral("min-width: 16px; min-height: 16px;max-width:16px; max-height: 16px;border-radius: 8px;  border:1px solid black;"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(31, 7, 48, 16));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(200, 10, 16, 16));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);
        pushButton->setMinimumSize(QSize(16, 16));
        pushButton->setMaximumSize(QSize(16, 16));
        pushButton->setStyleSheet(QLatin1String("QPushButton:!checked:!hover{\n"
"border-image: url(:/new/prefix1/checked_default.png);\n"
"}\n"
"\n"
"QPushButton:!checked:hover{\n"
"border-image: url(:/new/prefix1/checked_hover.png);\n"
"}\n"
"\n"
"QPushButton:checked{\n"
"border-image: url(:/new/prefix1/checked_confirm.png);\n"
"}"));
        pushButton->setCheckable(true);
        pushButton->setChecked(false);

        retranslateUi(listitem);

        QMetaObject::connectSlotsByName(listitem);
    } // setupUi

    void retranslateUi(QWidget *listitem)
    {
        listitem->setWindowTitle(QApplication::translate("listitem", "Form", nullptr));
        label->setText(QString());
        label_2->setText(QApplication::translate("listitem", "username", nullptr));
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class listitem: public Ui_listitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LISTITEM_H
