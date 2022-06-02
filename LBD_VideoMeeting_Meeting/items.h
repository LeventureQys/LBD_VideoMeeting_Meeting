#pragma once
#include "ui_listItem.h"
#include "ui_nameItem.h"
#include "ui_Quit.h"
class TnameItem :public QWidget {
	Q_OBJECT

public:
	TnameItem(QWidget *parent = Q_NULLPTR);

private:
	Ui::nameItem ui;
	QString name;
};
class nameItem :public QWidget {
	Q_OBJECT

public:
	nameItem(QWidget *parent = Q_NULLPTR);
	void setName(QString strMsg);
private:
	Ui::nameItem ui;
	QString name;
};
#define PADDING 2
enum Direction { UP = 0, DOWN = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };
class listitem : public QWidget {
	Q_OBJECT
public:
	listitem(QWidget *parent = Q_NULLPTR);
	void setPic(QString picpath);
	void setName(QString stuname);
	//设置按钮为被按下状态
	bool setChecked();
	void cancelChecked();
	QString name;
	QString PicPath;
	QString seat;
	bool CheckState = false;
	bool isChecked();
signals:
	void newCheck();
	//勾选消息发送
signals:
	void cancelCheck();
	//取消选择消息发送
private:
	Ui::listitem ui;




	private slots:
	void on_pushButton_clicked(bool checked);
	//如果被取消选择的用户还在Activeed内，则无法取消勾选
	void notCancel();
};

class Quit : public QWidget {
	Q_OBJECT

public:
	Quit(QWidget *parent = Q_NULLPTR);

private:
	Ui::Quit ui;

	private slots:

	void on_btn_Close_clicked();
	void on_btn_Close_2_clicked();
	void on_btn_Cancel_clicked();
signals:
	void QUITMEETING();

public:
	void region(const QPoint &currentGlobalPoint);  //鼠标的位置,改变光标
protected:
	//鼠标按下移动及释放事件
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QPoint m_movePoint;  //鼠标的位置
	bool isLeftPressDown;  // 判断左键是否按下
	Direction dir;        // 窗口大小改变时，记录改变方向
};

