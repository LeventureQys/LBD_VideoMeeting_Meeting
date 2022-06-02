/********************************************************************************
** Form generated from reading UI file 'List.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LIST_H
#define UI_LIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_StuList
{
public:
    QLineEdit *txt_Search;
    QLabel *lab_className;
    QListWidget *listWidget;
    QPushButton *btn_Invite;
    QLabel *lab_num;
    QPushButton *btn_search;

    void setupUi(QWidget *StuList)
    {
        if (StuList->objectName().isEmpty())
            StuList->setObjectName(QStringLiteral("StuList"));
        StuList->resize(308, 465);
        StuList->setStyleSheet(QString::fromUtf8("QWidget[objectName=\"StuList\"]{\n"
"background-image:url(./images/StuList_BG.png)\n"
"\n"
"}\n"
"QLineEdit{\n"
"color: rgb(153, 153, 153);\n"
"	font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"border-image:url(./images/line_Edit.png)\n"
"}\n"
"\n"
"QPushButton[objectName=\"btn_search\"]{\n"
"border-image:url(./images/Search_default.png)\n"
"}\n"
"\n"
"QListWidget{\n"
"border:0\n"
"}\n"
""));
        txt_Search = new QLineEdit(StuList);
        txt_Search->setObjectName(QStringLiteral("txt_Search"));
        txt_Search->setGeometry(QRect(40, 60, 231, 33));
        txt_Search->setStyleSheet(QStringLiteral(""));
        lab_className = new QLabel(StuList);
        lab_className->setObjectName(QStringLiteral("lab_className"));
        lab_className->setGeometry(QRect(40, 40, 41, 16));
        lab_className->setStyleSheet(QString::fromUtf8("QLabel[objectName = \"lab_className\"]{\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        listWidget = new QListWidget(StuList);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(40, 100, 231, 301));
        listWidget->setStyleSheet(QStringLiteral(""));
        btn_Invite = new QPushButton(StuList);
        btn_Invite->setObjectName(QStringLiteral("btn_Invite"));
        btn_Invite->setGeometry(QRect(120, 410, 80, 30));
        btn_Invite->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"border-image:url(./images/InviteBtn_default.png);\n"
"background-image: linear-gradient(-90deg, \n"
"		#1ad5ff 0%, \n"
"		#14b5f6 45%, \n"
"		#0e94ec 100%);\n"
"border-radius: 15px;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);\n"
"border-image:url(./images/InviteBtn_hover.png);\n"
"background-image: linear-gradient(-90deg, \n"
"		#1ad5ff 0%, \n"
"		#14b5f6 45%, \n"
"		#0e94ec 100%);\n"
"border-radius: 15px;\n"
"}"));
        lab_num = new QLabel(StuList);
        lab_num->setObjectName(QStringLiteral("lab_num"));
        lab_num->setGeometry(QRect(90, 40, 101, 16));
        lab_num->setStyleSheet(QString::fromUtf8("color: rgb(153, 153, 153);\n"
"font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_search = new QPushButton(StuList);
        btn_search->setObjectName(QStringLiteral("btn_search"));
        btn_search->setGeometry(QRect(250, 70, 16, 16));
        btn_search->setStyleSheet(QLatin1String("QPushButton{\n"
"image:url(./images/Search_default.png)\n"
"}"));

        retranslateUi(StuList);

        QMetaObject::connectSlotsByName(StuList);
    } // setupUi

    void retranslateUi(QWidget *StuList)
    {
        StuList->setWindowTitle(QApplication::translate("StuList", "Form", nullptr));
        txt_Search->setText(QApplication::translate("StuList", "\350\276\223\345\205\245\345\255\246\347\224\237\345\247\223\345\220\215\350\277\233\350\241\214\346\220\234\347\264\242...", nullptr));
        lab_className->setText(QApplication::translate("StuList", "x\345\271\264x\347\217\255", nullptr));
        btn_Invite->setText(QApplication::translate("StuList", "\347\241\256\350\256\244", nullptr));
        lab_num->setText(QApplication::translate("StuList", "(\346\234\200\345\244\232\345\217\257\351\202\200\350\257\267x/8\344\272\272)", nullptr));
        btn_search->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class StuList: public Ui_StuList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LIST_H
