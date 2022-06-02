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
	//���ð�ťΪ������״̬
	bool setChecked();
	void cancelChecked();
	QString name;
	QString PicPath;
	QString seat;
	bool CheckState = false;
	bool isChecked();
signals:
	void newCheck();
	//��ѡ��Ϣ����
signals:
	void cancelCheck();
	//ȡ��ѡ����Ϣ����
private:
	Ui::listitem ui;




	private slots:
	void on_pushButton_clicked(bool checked);
	//�����ȡ��ѡ����û�����Activeed�ڣ����޷�ȡ����ѡ
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
	void region(const QPoint &currentGlobalPoint);  //����λ��,�ı���
protected:
	//��갴���ƶ����ͷ��¼�
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

private:
	QPoint m_movePoint;  //����λ��
	bool isLeftPressDown;  // �ж�����Ƿ���
	Direction dir;        // ���ڴ�С�ı�ʱ����¼�ı䷽��
};

