#pragma once

#include <QWidget>
#include "ui_Camitem.h"
#include "qdebug.h"
#include "qpixmap.h"
class Camitem : public QWidget
{
	Q_OBJECT

public:
	Camitem(QWidget *parent = Q_NULLPTR);
	~Camitem();
	void SetPic(QString picpath);
	void SetName(QString name);
 
private:
	Ui::Camitem ui;

	
	
};
