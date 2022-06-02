/********************************************************************************
** Form generated from reading UI file 'Camitem.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAMITEM_H
#define UI_CAMITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Camitem
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer_3;
    QLabel *Pic_s2;
    QSpacerItem *verticalSpacer_24;
    QLabel *name_s2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;

    void setupUi(QWidget *Camitem)
    {
        if (Camitem->objectName().isEmpty())
            Camitem->setObjectName(QStringLiteral("Camitem"));
        Camitem->resize(532, 274);
        Camitem->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(Camitem);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(Camitem);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setStyleSheet(QLatin1String("QWidget[objectName=widget]{background-color: rgb(51, 51, 51);border:1px solid white\n"
"\n"
"}"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer_3 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_3, 4, 1, 1, 1);

        Pic_s2 = new QLabel(widget);
        Pic_s2->setObjectName(QStringLiteral("Pic_s2"));
        Pic_s2->setMinimumSize(QSize(82, 82));
        Pic_s2->setMaximumSize(QSize(82, 82));
        Pic_s2->setStyleSheet(QLatin1String("min-width: 80px; min-height: 80px;max-width:80px; max-height: 80px;border-radius: 40px; border:1px solid white; \n"
""));
        Pic_s2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(Pic_s2, 1, 1, 2, 1);

        verticalSpacer_24 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer_24, 0, 1, 1, 1);

        name_s2 = new QLabel(widget);
        name_s2->setObjectName(QStringLiteral("name_s2"));
        name_s2->setStyleSheet(QString::fromUtf8("font: 16px \"\345\276\256\350\275\257\351\233\205\351\273\221\";\n"
"color: rgb(255, 255, 255);"));
        name_s2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(name_s2, 3, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(137, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 2, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(138, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 0, 1, 1);


        gridLayout_2->addWidget(widget, 0, 0, 1, 1);


        retranslateUi(Camitem);

        QMetaObject::connectSlotsByName(Camitem);
    } // setupUi

    void retranslateUi(QWidget *Camitem)
    {
        Camitem->setWindowTitle(QApplication::translate("Camitem", "Form", nullptr));
        Pic_s2->setText(QString());
        name_s2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Camitem: public Ui_Camitem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAMITEM_H
