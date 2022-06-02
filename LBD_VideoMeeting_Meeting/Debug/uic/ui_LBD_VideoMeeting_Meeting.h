/********************************************************************************
** Form generated from reading UI file 'LBD_VideoMeeting_Meeting.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LBD_VIDEOMEETING_MEETING_H
#define UI_LBD_VIDEOMEETING_MEETING_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "Camitem.h"

QT_BEGIN_NAMESPACE

class Ui_LBD_VideoMeeting_MeetingClass
{
public:
    QWidget *centralWidget;
    QPushButton *btn_cam;
    QLabel *lab_bg;
    QLabel *lab_toolbar;
    QLabel *lab_Invite;
    QPushButton *btn_mic;
    QPushButton *btn_invite;
    QPushButton *btn_close;
    QLabel *lab_cam;
    QLabel *lab_mic;
    QLabel *lab_invite;
    QLabel *lab_end;
    QWidget *StuList;
    QLabel *lab_className;
    QLabel *lab_num;
    QLineEdit *txt_Search;
    QPushButton *btn_search;
    QListWidget *listWidget;
    QPushButton *btn_InviteConfirm;
    QWidget *mengban;
    QLabel *label;
    QLabel *lab_timer;
    Camitem *Cam_Stu1;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QWidget *Cam_Invite;
    QPushButton *nameitem1;
    QPushButton *nameitem2;
    QPushButton *nameitem3;
    QPushButton *nameitem4;
    QPushButton *nameitem5;
    QPushButton *nameitem6;
    QPushButton *nameitem8;
    QPushButton *nameitem7;
    QWidget *nameitem0;
    QPushButton *pushButton;
    QWidget *widget;
    QLabel *label_2;
    QWidget *nameitem_me;
    QWidget *widget_2;
    QLabel *label_3;
    QWidget *wid_close;
    Camitem *Cam_Stu2;
    QGridLayout *gridLayout_2;
    QLabel *label_5;
    Camitem *Cam_Stu3;
    QGridLayout *gridLayout_4;
    QLabel *label_6;
    Camitem *Cam_Stu4;
    QGridLayout *gridLayout_5;
    QLabel *label_7;
    Camitem *Cam_Stu5;
    QGridLayout *gridLayout_6;
    QLabel *label_10;
    Camitem *Cam_Stu6;
    QGridLayout *gridLayout_7;
    QLabel *label_11;
    Camitem *Cam_Stu7;
    QGridLayout *gridLayout_8;
    QLabel *label_8;
    Camitem *Cam_Stu8;
    QGridLayout *gridLayout_9;
    QLabel *label_9;
    Camitem *Cam_Teacher;
    QGridLayout *gridLayout_11;
    QLabel *label_12;

    void setupUi(QMainWindow *LBD_VideoMeeting_MeetingClass)
    {
        if (LBD_VideoMeeting_MeetingClass->objectName().isEmpty())
            LBD_VideoMeeting_MeetingClass->setObjectName(QStringLiteral("LBD_VideoMeeting_MeetingClass"));
        LBD_VideoMeeting_MeetingClass->resize(940, 620);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LBD_VideoMeeting_MeetingClass->sizePolicy().hasHeightForWidth());
        LBD_VideoMeeting_MeetingClass->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(LBD_VideoMeeting_MeetingClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        btn_cam = new QPushButton(centralWidget);
        btn_cam->setObjectName(QStringLiteral("btn_cam"));
        btn_cam->setGeometry(QRect(309, 554, 64, 34));
        btn_cam->setStyleSheet(QLatin1String("QPushButton:!checked:!hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image: url(:/new/prefix1/CamareOn_default.png);\n"
"}\n"
"\n"
"QPushButton:!checked:hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/CamareOn_hover.png);\n"
"}\n"
"\n"
"QPushButton:checked:!hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(./images/CamareOff_default.png)\n"
"}\n"
"\n"
"QPushButton:checked:hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/CamareOff_hover.png)\n"
"}"));
        btn_cam->setCheckable(true);
        btn_cam->setChecked(false);
        lab_bg = new QLabel(centralWidget);
        lab_bg->setObjectName(QStringLiteral("lab_bg"));
        lab_bg->setGeometry(QRect(0, 0, 940, 540));
        lab_bg->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        lab_toolbar = new QLabel(centralWidget);
        lab_toolbar->setObjectName(QStringLiteral("lab_toolbar"));
        lab_toolbar->setGeometry(QRect(0, 540, 940, 80));
        lab_toolbar->setStyleSheet(QStringLiteral("background-color:rgb(255, 255, 255)"));
        lab_Invite = new QLabel(centralWidget);
        lab_Invite->setObjectName(QStringLiteral("lab_Invite"));
        lab_Invite->setGeometry(QRect(670, 380, 121, 81));
        btn_mic = new QPushButton(centralWidget);
        btn_mic->setObjectName(QStringLiteral("btn_mic"));
        btn_mic->setGeometry(QRect(395, 554, 64, 34));
        btn_mic->setStyleSheet(QLatin1String("QPushButton:!checked:!hover{\n"
"\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/MicOn_default.png);}\n"
"\n"
"QPushButton:!checked:hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/MicOn_hover.png);\n"
"}\n"
"\n"
"QPushButton:checked:!hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/MicOff_default.png)\n"
"}\n"
"\n"
"QPushButton:checked:hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/MicOff_hover.png)\n"
"}\n"
""));
        btn_mic->setCheckable(true);
        btn_invite = new QPushButton(centralWidget);
        btn_invite->setObjectName(QStringLiteral("btn_invite"));
        btn_invite->setGeometry(QRect(481, 554, 64, 34));
        btn_invite->setStyleSheet(QLatin1String("QPushButton:!checked{\n"
"\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/Invite_default.png)\n"
"}\n"
"\n"
"QPushButton:checked{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"image:url(:/new/prefix1/Invite_hover.png);\n"
"\n"
"}\n"
""));
        btn_invite->setCheckable(true);
        btn_invite->setChecked(false);
        btn_close = new QPushButton(centralWidget);
        btn_close->setObjectName(QStringLiteral("btn_close"));
        btn_close->setGeometry(QRect(567, 554, 64, 34));
        btn_close->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
"\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"border-image:url(:/new/prefix1/End_default.png)\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border:2px groove gray;border-radius:10px;padding:2px 4px;\n"
"background-color: rgb(238, 238, 238);\n"
"border-image:url(:/new/prefix1/End_hover.png);\n"
"\n"
"}\n"
""));
        lab_cam = new QLabel(centralWidget);
        lab_cam->setObjectName(QStringLiteral("lab_cam"));
        lab_cam->setGeometry(QRect(311, 595, 60, 11));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(9);
        lab_cam->setFont(font);
        lab_cam->setStyleSheet(QStringLiteral("color: rgb(153, 153, 153);"));
        lab_mic = new QLabel(centralWidget);
        lab_mic->setObjectName(QStringLiteral("lab_mic"));
        lab_mic->setGeometry(QRect(403, 595, 60, 11));
        lab_mic->setFont(font);
        lab_mic->setStyleSheet(QStringLiteral("color: rgb(153, 153, 153);"));
        lab_invite = new QLabel(centralWidget);
        lab_invite->setObjectName(QStringLiteral("lab_invite"));
        lab_invite->setGeometry(QRect(501, 595, 60, 11));
        lab_invite->setFont(font);
        lab_invite->setStyleSheet(QStringLiteral("color: rgb(153, 153, 153);"));
        lab_end = new QLabel(centralWidget);
        lab_end->setObjectName(QStringLiteral("lab_end"));
        lab_end->setGeometry(QRect(575, 595, 60, 11));
        lab_end->setFont(font);
        lab_end->setStyleSheet(QStringLiteral("color: rgb(153, 153, 153);"));
        StuList = new QWidget(centralWidget);
        StuList->setObjectName(QStringLiteral("StuList"));
        StuList->setGeometry(QRect(360, 70, 301, 461));
        StuList->setStyleSheet(QLatin1String("QWidget[objectName=\"StuList\"]{\n"
"background-image:url(:/new/prefix1/StuList_BG.png)\n"
"}\n"
"\n"
"QPushButton[objectName=\"btn_search\"]{\n"
"border-image:url(:/new/prefix1/Search_default.png)\n"
"}\n"
"\n"
"QListWidget{\n"
"border:0\n"
"}\n"
""));
        lab_className = new QLabel(StuList);
        lab_className->setObjectName(QStringLiteral("lab_className"));
        lab_className->setGeometry(QRect(40, 40, 41, 16));
        lab_className->setStyleSheet(QString::fromUtf8("QLabel[objectName = \"lab_className\"]{\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}"));
        lab_num = new QLabel(StuList);
        lab_num->setObjectName(QStringLiteral("lab_num"));
        lab_num->setGeometry(QRect(90, 40, 101, 16));
        lab_num->setStyleSheet(QString::fromUtf8("color: rgb(153, 153, 153);\n"
"font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        txt_Search = new QLineEdit(StuList);
        txt_Search->setObjectName(QStringLiteral("txt_Search"));
        txt_Search->setGeometry(QRect(40, 60, 231, 33));
        txt_Search->setStyleSheet(QString::fromUtf8("QLineEdit:!hover{\n"
"border-image:url(:/new/prefix1/line_Edit.png);\n"
"color: rgb(102, 102, 102);\n"
"font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"}\n"
"\n"
"QLineEdit:hover{\n"
"border-image:url(:/new/prefix1/line_Edit_hover.png);\n"
"color: rgb(102, 102, 102);\n"
"font: 12px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"\n"
"}"));
        btn_search = new QPushButton(StuList);
        btn_search->setObjectName(QStringLiteral("btn_search"));
        btn_search->setGeometry(QRect(250, 70, 16, 16));
        btn_search->setStyleSheet(QLatin1String("QPushButton:!hover{\n"
"border-image: url(:/new/prefix1/Search_default.png);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"border-image: url(:/new/prefix1/Search_hover.png);\n"
"}"));
        listWidget = new QListWidget(StuList);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(40, 100, 231, 301));
        listWidget->setStyleSheet(QLatin1String("QListWidget::Item{background:rgba(0,0,0,0%);margin:0px,0px,0px,0px;padding-left:0px;}\"\n"
"\n"
"QScrollBar{width:5px;}"));
        btn_InviteConfirm = new QPushButton(StuList);
        btn_InviteConfirm->setObjectName(QStringLiteral("btn_InviteConfirm"));
        btn_InviteConfirm->setGeometry(QRect(120, 410, 80, 30));
        btn_InviteConfirm->setStyleSheet(QString::fromUtf8("QPushButton:!hover{\n"
"	font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"	color: rgb(255, 255, 255);\n"
"border-image:url(:/new/prefix1/InviteBtn_default.png);\n"
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
"border-image:url(:/new/prefix1/InviteBtn_hover.png);\n"
"background-image: linear-gradient(-90deg, \n"
"		#1ad5ff 0%, \n"
"		#14b5f6 45%, \n"
"		#0e94ec 100%);\n"
"border-radius: 15px;\n"
"}"));
        mengban = new QWidget(centralWidget);
        mengban->setObjectName(QStringLiteral("mengban"));
        mengban->setGeometry(QRect(0, 0, 940, 120));
        mengban->setStyleSheet(QLatin1String("QWidget[objectName = \"mengban\"]{\n"
"border-image:url(:/new/prefix1/mengban.png)\n"
"rgb(255, 255, 255)\n"
"}\n"
"\n"
"QPushButton:!hover\n"
"{\n"
"background-color: rgb(255, 255, 255,0);\n"
"image:url(:/new/prefix1/close_default.png);\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"background-color: rgb(255, 255, 255,0);\n"
"image:url(:/new/prefix1/close_hover.png);\n"
"}"));
        label = new QLabel(mengban);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(41, 20, 91, 16));
        label->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lab_timer = new QLabel(mengban);
        lab_timer->setObjectName(QStringLiteral("lab_timer"));
        lab_timer->setGeometry(QRect(443, 21, 81, 16));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        lab_timer->setFont(font1);
        lab_timer->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);\n"
"font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        Cam_Stu1 = new Camitem(centralWidget);
        Cam_Stu1->setObjectName(QStringLiteral("Cam_Stu1"));
        Cam_Stu1->setGeometry(QRect(20, 140, 151, 131));
        Cam_Stu1->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu1]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}\n"
""));
        gridLayout = new QGridLayout(Cam_Stu1);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_4 = new QLabel(Cam_Stu1);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        Cam_Invite = new QWidget(centralWidget);
        Cam_Invite->setObjectName(QStringLiteral("Cam_Invite"));
        Cam_Invite->setGeometry(QRect(700, 390, 241, 131));
        Cam_Invite->setStyleSheet(QLatin1String("QWidget:!hover{background-color: rgb(51, 51, 51);image: url(:/new/prefix1/Add_default.png);border:1px solid white;}\n"
"QWidget:hover{background-color: rgb(51, 51, 51);image: url(:/new/prefix1/Add_hover.png);border:1px solid white;}\n"
""));
        nameitem1 = new QPushButton(centralWidget);
        nameitem1->setObjectName(QStringLiteral("nameitem1"));
        nameitem1->setGeometry(QRect(90, 570, 75, 23));
        nameitem1->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);\n"
"\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/new/prefix1/mic_White.png"), QSize(), QIcon::Normal, QIcon::Off);
        nameitem1->setIcon(icon);
        nameitem1->setCheckable(false);
        nameitem1->setChecked(false);
        nameitem2 = new QPushButton(centralWidget);
        nameitem2->setObjectName(QStringLiteral("nameitem2"));
        nameitem2->setGeometry(QRect(90, 590, 75, 23));
        nameitem2->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);\n"
"icon-position:left;\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        nameitem2->setIcon(icon);
        nameitem3 = new QPushButton(centralWidget);
        nameitem3->setObjectName(QStringLiteral("nameitem3"));
        nameitem3->setGeometry(QRect(10, 550, 75, 23));
        nameitem3->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);\n"
"\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        nameitem3->setIcon(icon);
        nameitem4 = new QPushButton(centralWidget);
        nameitem4->setObjectName(QStringLiteral("nameitem4"));
        nameitem4->setGeometry(QRect(10, 590, 75, 23));
        nameitem4->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";image-position:left;text-align:center;padding-left:5px;padding-bottom:2px;color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        nameitem4->setIcon(icon);
        nameitem5 = new QPushButton(centralWidget);
        nameitem5->setObjectName(QStringLiteral("nameitem5"));
        nameitem5->setGeometry(QRect(10, 570, 75, 23));
        nameitem5->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);\n"
"\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        nameitem5->setIcon(icon);
        nameitem6 = new QPushButton(centralWidget);
        nameitem6->setObjectName(QStringLiteral("nameitem6"));
        nameitem6->setGeometry(QRect(160, 570, 75, 23));
        nameitem6->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);\n"
"\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        nameitem6->setIcon(icon);
        nameitem8 = new QPushButton(centralWidget);
        nameitem8->setObjectName(QStringLiteral("nameitem8"));
        nameitem8->setGeometry(QRect(160, 550, 75, 23));
        nameitem8->setStyleSheet(QString::fromUtf8("QPushButton{background-color: rgba(0, 0, 0,0.3);\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;}\n"
""));
        nameitem8->setIcon(icon);
        nameitem8->setCheckable(false);
        nameitem7 = new QPushButton(centralWidget);
        nameitem7->setObjectName(QStringLiteral("nameitem7"));
        nameitem7->setGeometry(QRect(90, 550, 75, 23));
        nameitem7->setStyleSheet(QString::fromUtf8("background-color: rgba(0, 0, 0,0.3);\n"
"\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;"));
        nameitem7->setIcon(icon);
        nameitem0 = new QWidget(centralWidget);
        nameitem0->setObjectName(QStringLiteral("nameitem0"));
        nameitem0->setGeometry(QRect(150, 590, 132, 32));
        nameitem0->setStyleSheet(QString::fromUtf8("QWidget[objectName=nameitem0]{\n"
"background-color: rgba(0, 0, 0,0.3);\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"image-position:left;\n"
"text-align:center;\n"
"padding-left:5px;\n"
"padding-bottom:2px;\n"
"color: rgb(255, 255, 255);\n"
"border-radius: 3px;}\n"
"\n"
"\n"
"\n"
""));
        pushButton = new QPushButton(nameitem0);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 4, 72, 24));
        pushButton->setStyleSheet(QString::fromUtf8("border-image: url(:/new/prefix1/TeacherGreen.png);\n"
"color: rgb(255, 255, 255);\n"
"font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"padding-right:4px;\n"
"background-color: rgba(255, 255, 255,0);\n"
"border-radius: 3px;"));
        widget = new QWidget(nameitem0);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(91, 7, 14, 18));
        widget->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/mic_White.png);"));
        label_2 = new QLabel(nameitem0);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(108, 8, 16, 16));
        label_2->setStyleSheet(QString::fromUtf8("font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));
        nameitem_me = new QWidget(centralWidget);
        nameitem_me->setObjectName(QStringLiteral("nameitem_me"));
        nameitem_me->setGeometry(QRect(240, 550, 50, 32));
        nameitem_me->setStyleSheet(QLatin1String("QWidget[objectName=nameitem_me]{border-radius: 3px;border-image: url(:/new/prefix1/TeacherGreen.png);}\n"
"\n"
""));
        widget_2 = new QWidget(nameitem_me);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        widget_2->setGeometry(QRect(9, 7, 14, 18));
        widget_2->setStyleSheet(QStringLiteral("border-image: url(:/new/prefix1/mic_White.png);"));
        label_3 = new QLabel(nameitem_me);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(26, 7, 16, 16));
        label_3->setStyleSheet(QString::fromUtf8("font: 14px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));
        wid_close = new QWidget(centralWidget);
        wid_close->setObjectName(QStringLiteral("wid_close"));
        wid_close->setGeometry(QRect(890, 170, 16, 16));
        wid_close->setStyleSheet(QLatin1String("QWidget:!hover{\n"
"background-color: rgb(255, 255, 255,0);\n"
"image:url(:/new/prefix1/close_default.png);\n"
"}\n"
"\n"
"QWidget:hover{\n"
"background-color: rgb(255, 255, 255,0);\n"
"image:url(:/new/prefix1/close_hover.png);\n"
"}"));
        Cam_Stu2 = new Camitem(centralWidget);
        Cam_Stu2->setObjectName(QStringLiteral("Cam_Stu2"));
        Cam_Stu2->setGeometry(QRect(180, 130, 181, 151));
        Cam_Stu2->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu2]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_2 = new QGridLayout(Cam_Stu2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_5 = new QLabel(Cam_Stu2);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout_2->addWidget(label_5, 0, 0, 1, 1);

        Cam_Stu3 = new Camitem(centralWidget);
        Cam_Stu3->setObjectName(QStringLiteral("Cam_Stu3"));
        Cam_Stu3->setGeometry(QRect(30, 280, 141, 121));
        Cam_Stu3->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu3]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}\n"
""));
        gridLayout_4 = new QGridLayout(Cam_Stu3);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        label_6 = new QLabel(Cam_Stu3);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_4->addWidget(label_6, 0, 0, 1, 1);

        Cam_Stu4 = new Camitem(centralWidget);
        Cam_Stu4->setObjectName(QStringLiteral("Cam_Stu4"));
        Cam_Stu4->setGeometry(QRect(190, 290, 141, 121));
        Cam_Stu4->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu4]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_5 = new QGridLayout(Cam_Stu4);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        label_7 = new QLabel(Cam_Stu4);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_5->addWidget(label_7, 0, 0, 1, 1);

        Cam_Stu5 = new Camitem(centralWidget);
        Cam_Stu5->setObjectName(QStringLiteral("Cam_Stu5"));
        Cam_Stu5->setGeometry(QRect(660, 130, 141, 121));
        Cam_Stu5->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu5]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_6 = new QGridLayout(Cam_Stu5);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        label_10 = new QLabel(Cam_Stu5);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_6->addWidget(label_10, 0, 0, 1, 1);

        Cam_Stu6 = new Camitem(centralWidget);
        Cam_Stu6->setObjectName(QStringLiteral("Cam_Stu6"));
        Cam_Stu6->setGeometry(QRect(670, 250, 141, 121));
        Cam_Stu6->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu6]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_7 = new QGridLayout(Cam_Stu6);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QStringLiteral("gridLayout_7"));
        label_11 = new QLabel(Cam_Stu6);
        label_11->setObjectName(QStringLiteral("label_11"));

        gridLayout_7->addWidget(label_11, 0, 0, 1, 1);

        Cam_Stu7 = new Camitem(centralWidget);
        Cam_Stu7->setObjectName(QStringLiteral("Cam_Stu7"));
        Cam_Stu7->setGeometry(QRect(10, 400, 141, 121));
        Cam_Stu7->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu7]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_8 = new QGridLayout(Cam_Stu7);
        gridLayout_8->setSpacing(6);
        gridLayout_8->setContentsMargins(11, 11, 11, 11);
        gridLayout_8->setObjectName(QStringLiteral("gridLayout_8"));
        label_8 = new QLabel(Cam_Stu7);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_8->addWidget(label_8, 0, 0, 1, 1);

        Cam_Stu8 = new Camitem(centralWidget);
        Cam_Stu8->setObjectName(QStringLiteral("Cam_Stu8"));
        Cam_Stu8->setGeometry(QRect(190, 410, 141, 121));
        Cam_Stu8->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Stu8]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_9 = new QGridLayout(Cam_Stu8);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QStringLiteral("gridLayout_9"));
        label_9 = new QLabel(Cam_Stu8);
        label_9->setObjectName(QStringLiteral("label_9"));

        gridLayout_9->addWidget(label_9, 0, 0, 1, 1);

        Cam_Teacher = new Camitem(centralWidget);
        Cam_Teacher->setObjectName(QStringLiteral("Cam_Teacher"));
        Cam_Teacher->setGeometry(QRect(810, 260, 141, 121));
        Cam_Teacher->setStyleSheet(QLatin1String("QWidget[objectName=Cam_Teacher]{background-color: rgb(51, 51, 51);border:1px solid white;\n"
"}"));
        gridLayout_11 = new QGridLayout(Cam_Teacher);
        gridLayout_11->setSpacing(6);
        gridLayout_11->setContentsMargins(11, 11, 11, 11);
        gridLayout_11->setObjectName(QStringLiteral("gridLayout_11"));
        label_12 = new QLabel(Cam_Teacher);
        label_12->setObjectName(QStringLiteral("label_12"));

        gridLayout_11->addWidget(label_12, 0, 0, 1, 1);

        LBD_VideoMeeting_MeetingClass->setCentralWidget(centralWidget);
        lab_bg->raise();
        lab_toolbar->raise();
        btn_cam->raise();
        lab_Invite->raise();
        btn_mic->raise();
        btn_invite->raise();
        btn_close->raise();
        lab_cam->raise();
        lab_mic->raise();
        lab_invite->raise();
        lab_end->raise();
        StuList->raise();
        mengban->raise();
        Cam_Stu1->raise();
        Cam_Invite->raise();
        nameitem1->raise();
        nameitem2->raise();
        nameitem3->raise();
        nameitem4->raise();
        nameitem5->raise();
        nameitem6->raise();
        nameitem8->raise();
        nameitem7->raise();
        nameitem0->raise();
        nameitem_me->raise();
        wid_close->raise();
        Cam_Stu2->raise();
        Cam_Stu3->raise();
        Cam_Stu4->raise();
        Cam_Stu5->raise();
        Cam_Stu6->raise();
        Cam_Stu7->raise();
        Cam_Stu8->raise();
        Cam_Teacher->raise();

        retranslateUi(LBD_VideoMeeting_MeetingClass);

        QMetaObject::connectSlotsByName(LBD_VideoMeeting_MeetingClass);
    } // setupUi

    void retranslateUi(QMainWindow *LBD_VideoMeeting_MeetingClass)
    {
        LBD_VideoMeeting_MeetingClass->setWindowTitle(QApplication::translate("LBD_VideoMeeting_MeetingClass", "LBD_VideoMeeting_Meeting", nullptr));
        btn_cam->setText(QString());
        lab_bg->setText(QString());
        lab_toolbar->setText(QString());
        lab_Invite->setText(QString());
        btn_mic->setText(QString());
        btn_invite->setText(QString());
        btn_close->setText(QString());
        lab_cam->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\345\205\263\351\227\255\346\221\204\345\203\217\345\244\264", nullptr));
        lab_mic->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\345\205\263\351\227\255\350\257\235\347\255\222", nullptr));
        lab_invite->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\351\202\200\350\257\267", nullptr));
        lab_end->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\347\273\223\346\235\237\345\257\271\350\256\262", nullptr));
        lab_className->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "x\345\271\264x\347\217\255", nullptr));
        lab_num->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "(\346\234\200\345\244\232\345\217\257\351\202\200\350\257\267x/8\344\272\272)", nullptr));
        txt_Search->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\350\276\223\345\205\245\345\255\246\347\224\237\345\247\223\345\220\215\350\277\233\350\241\214\346\220\234\347\264\242...", nullptr));
        btn_search->setText(QString());
        btn_InviteConfirm->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\347\241\256\350\256\244", nullptr));
        label->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\345\270\210\347\224\237\345\257\271\350\256\262", nullptr));
        lab_timer->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "00:00:00", nullptr));
        label_4->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "1", nullptr));
        nameitem1->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem2->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem3->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem4->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem5->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem6->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem8->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        nameitem7->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\235\216\346\226\207\350\275\251", nullptr));
        pushButton->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\344\270\212\350\257\276\350\200\201\345\270\210", nullptr));
        label_2->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\210\221", nullptr));
        label_3->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "\346\210\221", nullptr));
        label_5->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "2", nullptr));
        label_6->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "3", nullptr));
        label_7->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "4", nullptr));
        label_10->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "5", nullptr));
        label_11->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "6", nullptr));
        label_8->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "7", nullptr));
        label_9->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "8", nullptr));
        label_12->setText(QApplication::translate("LBD_VideoMeeting_MeetingClass", "t", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LBD_VideoMeeting_MeetingClass: public Ui_LBD_VideoMeeting_MeetingClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LBD_VIDEOMEETING_MEETING_H
