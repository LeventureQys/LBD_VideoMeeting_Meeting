/********************************************************************************
** Form generated from reading UI file 'Quit.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QUIT_H
#define UI_QUIT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Quit
{
public:
    QWidget *widget;
    QLabel *label;
    QPushButton *btn_Close;
    QPushButton *btn_Cancel;
    QPushButton *btn_Close_2;

    void setupUi(QWidget *Quit)
    {
        if (Quit->objectName().isEmpty())
            Quit->setObjectName(QStringLiteral("Quit"));
        Quit->resize(400, 180);
        Quit->setStyleSheet(QLatin1String("QWidget[objectName=Quit]{\n"
"background-color: rgb(255, 255, 255);\n"
"}"));
        widget = new QWidget(Quit);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(101, 54, 38, 34));
        widget->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/Question_Big.png);"));
        label = new QLabel(Quit);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(147, 62, 153, 19));
        label->setStyleSheet(QString::fromUtf8("font: 18px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        btn_Close = new QPushButton(Quit);
        btn_Close->setObjectName(QStringLiteral("btn_Close"));
        btn_Close->setGeometry(QRect(86, 125, 108, 30));
        btn_Close->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"border-image: url(:/new/prefix1/btn_bg_default.png);\n"
"padding-bottom:8px;\n"
"	font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"	color: rgb(255, 255, 255);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border-image: url(:/new/prefix1/btn_bg_hover.png);\n"
"padding-bottom:8px;\n"
"	font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"	color: rgb(255, 255, 255);\n"
"}"));
        btn_Cancel = new QPushButton(Quit);
        btn_Cancel->setObjectName(QStringLiteral("btn_Cancel"));
        btn_Cancel->setGeometry(QRect(206, 125, 108, 30));
        btn_Cancel->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"border-image: url(:/new/prefix1/hollowBtn_default.png);\n"
"padding-bottom:7px;\n"
"	font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"	color: rgb(0, 153, 255);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border-image: url(:/new/prefix1/hollowBtn_hover.png);\n"
"padding-bottom:7px;\n"
"	font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"	color: rgb(0, 153, 255);\n"
"}"));
        btn_Close_2 = new QPushButton(Quit);
        btn_Close_2->setObjectName(QStringLiteral("btn_Close_2"));
        btn_Close_2->setGeometry(QRect(368, 16, 16, 16));
        btn_Close_2->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
"border-image: url(:/new/prefix1/InvitationClose_hover.png);\n"
"}\n"
"QPushButton:hover{\n"
"border-image: url(:/new/prefix1/Invitation_hover.png);\n"
"}"));

        retranslateUi(Quit);

        QMetaObject::connectSlotsByName(Quit);
    } // setupUi

    void retranslateUi(QWidget *Quit)
    {
        Quit->setWindowTitle(QApplication::translate("Quit", "Form", nullptr));
        label->setText(QApplication::translate("Quit", "\346\230\257\345\220\246\347\273\223\346\235\237\345\270\210\347\224\237\345\257\271\350\256\262", nullptr));
        btn_Close->setText(QApplication::translate("Quit", "\347\241\256\345\256\232", nullptr));
        btn_Cancel->setText(QApplication::translate("Quit", "\345\217\226\346\266\210", nullptr));
        btn_Close_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Quit: public Ui_Quit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QUIT_H
