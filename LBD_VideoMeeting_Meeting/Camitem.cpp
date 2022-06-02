#include "Camitem.h"

Camitem::Camitem(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//this->installEventFilter();
}

Camitem::~Camitem()
{
}

void Camitem::SetPic(QString picname)
{
	QString picpath = QString("%1").arg(picname);
	QPixmap temp = QPixmap(picpath);
	qDebug() << picpath;
	qDebug() << temp.isNull();
	QString tempsheet = ui.Pic_s2->styleSheet();
	tempsheet = tempsheet + QString("border-image: url(%1);").arg(picname);
	ui.Pic_s2->setStyleSheet(tempsheet);

}

void Camitem::SetName(QString name)
{
	ui.name_s2->setText(name);
}
