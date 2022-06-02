#pragma once

#include <QtWidgets/QMainWindow>
#include "windows.h"
#include "ui_LBD_VideoMeeting_Meeting.h"
#include "qevent.h"
#include "qrect.h"
#include "qtimer.h"
#include <QTime>
#include"qdebug.h"
#include "qlabel.h"
#include "qthread.h"
#include "meeting.h"
#include <Windows.h>
#include <windowsx.h> //GET_X_LPARAM和GET_Y_LPARAM
#include "qmessagebox.h"
#pragma comment(lib,"user32.lib")
#include <qt_windows.h>
#include <string>
#include "qregexp.h"
#include"qlistwidget.h"
#include "qexception.h"
#include "qtoolbutton.h"
#include "qgridlayout.h"
#include "items.h"
#include "qscrollbar.h"
#include "Camitem.h"

//
//#define PADDING 2
//enum Direction { UP = 0, DOWN = 1, LEFT, RIGHT, LEFTTOP, LEFTBOTTOM, RIGHTBOTTOM, RIGHTTOP, NONE };

//教师端向主框架发送 向主框架发送学生邀请申请
const ULONG_PTR tINVITE = WM_USER + 5935;
//教师端向主框架发送 会议结束信号
const ULONG_PTR tEND = WM_USER + 5936;


//主框架向教师端发送 学生掉线信号
const ULONG_PTR  mt_sLEAVE = WM_USER + 5937;
//主框架向教师端发送 学生上线信号
const ULONG_PTR  mt_sONLINE = WM_USER + 5942;
//主框架向学生发送 教师离开信号
const ULONG_PTR ms_tLEAVE = WM_USER + 5938;
//主框架向学生端发送 新的学生进入会议信号
const ULONG_PTR ms_sINVITED = WM_USER + 5941;

//学生端向主框架发送 学生进入信号
const ULONG sENTER = WM_USER + 5939;
//学生端向主框架发送 学生离开信号
const ULONG sLEAVE = WM_USER + 5940;


char* QString_2char(QString qs);
//存储用户数据的链表
//包括当前用户的 窗口句柄 姓名 座次 激活状态，下一个用户的节点
//这个链表我常常需要从尾开始插，却要从头开始读，所以是一个双向链表

struct  UserInfo
{
	char* name = NULL;
	char* seat;
	char* image = NULL;
	bool isSelected = false;
};


struct Camares {
	char* name = NULL;
	char* seat = NULL;
	char* image = NULL;
	Camitem *label = nullptr;
	//为了更好的判别，在这个struct中我们重写==运算符，当两个struct的seat相等时，我们视作相等.
	bool operator==(const Camares b) const {
		return this->seat == b.seat;
	}
};
struct Inivite {
	char* name = NULL;
	char* seat = NULL;
	char* image = NULL;
	QWidget *label = nullptr;
	//为了更好的判别，在这个struct中我们重写==运算符，当两个struct的seat相等时，我们视作相等.
	bool operator==(const Camares b) const {
		return this->seat == b.seat;
	}


};






class LBD_VideoMeeting_Meeting : public QMainWindow
{
    Q_OBJECT

public:
    LBD_VideoMeeting_Meeting(QWidget *parent = Q_NULLPTR);
	//教师端入口
	//参数:
	//hwnd:主框架的窗口句柄
	//sip,port：服务器ip和端口
	//ClassName：班级名称
	//InvitedUsers：被选定的用户
	//userinfo ：所有学生

	void Start(char* hwndName, char* sip, int port, char* ClassName, char* InvitedUsers, char* userinfo);

	//学生端入口
	//参数
	//hwnd:主框架的窗口句柄
	//sip,port：服务器ip和端口
	//currentSeat:当前学生座位
	//ClassName：班级名称
	//InvitedUsers：被选定的用户
	//userinfo ：所有学生
	void Start(char* hwndName, char *sip, int port, char *currentSeat, char* ClassName, char* InvitedUsers, char* userinfo);
private slots:
	void on_btn_invite_clicked(bool checked);
	//接收来自listwidget发送的邀请，让每一位用户进入到会议中去 
	void ReceiveInvite(QList<UserInfo> *Invited);
	//从listwidget中接到新的勾选请求后，查看当前是否可以进行新用户的邀请
	bool getChecked();
	//从listwidget中接到新的取消请求后，检查当前是否可以进行用户的取消选择
	bool getCancel();
	//计时器
	void TimeLabelUpdate();
	//邀请按钮
	void on_btn_InviteConfirm_clicked();
	//结束对讲按钮
	void on_btn_close_clicked();
	//结束对讲右上角
	void on_btn_close_2_clicked();
	//结束会议信号
	void QUITSIGNAL();

signals:
	//当用户数据传入之后将UserInfo指针发送给ListWidget
	//传给list三个数，当前学生的信息类，当前学生数量，当前正在聊天的人结构体
	void UserReady(QList<UserInfo> *users,char* ClassName,QList<Camares> *list);
signals:
	void CancelChecked();
private:


	//声明主框架窗口名称s
	QString mainFrameHWND;
	QTimer *timer = new QTimer();
	QTime counter;
	int Selected = 0;
	void debug(QString str);
	void debug(char* str);
    Ui::LBD_VideoMeeting_MeetingClass ui;
	//声明该房间名称
	char* sroom = "LBD_VideoMeeting_Meeting";
	
	char* clsName;//声明班级名称，在ListWidget中用到
	const char* theRoom = "LBD_VideoMeeting_Meeting";
	QList<UserInfo> *userList = new QList<UserInfo>;

	//工具方法，用于将QString类型转化为char*类型
	char* QString2char(QString qs);

	QRect TotalFrame;

	//输入用户数据的长度，用于initListWidget，即当前班级总人数
	int UsersLength = 0;

	//初始化meadiasoupserver连接
	void initConnection(char* sip, int port);
	//初始化摄像头情况
	void initCamare();
	//窗口刷新，通过Actived给定的窗口句柄进行排列组合
	void FreshCams();
	//根据人数修改Geometrys排版策略
	void InitGeometry(int i);
	//根据Invite的数量初始化一些窗体控件
	void InitItems(int i);
	//教师1，学生0
	int TypeUser = 0;



	//开始会议
	void StartMeeting(char* TeaName, char* TeaSeat);
	//学生加入会议
	void StuEnterMeeting(char* StuName, char* StuSeat,char* pic);
	void StuEnterMeeting(QString inform);
	//初始化时学生加入会议，只输入一个QList
	void StuEnterMeeting(QList<UserInfo> *invited);
	//学生离开会议
	void StuLeaveMeeting(char* StuSeat);
	//教师不用动，所以不归到链表中去运算
	Camares Teacher;
	//一个用来承载当前学生的结点
	Camares CurrentStudent;
	//一个用来专门搞邀请的框，其实也没必要专门建一个，但是好看
	Inivite Cam_Invite;
	//创建一个链表的表头，此链表代表激活用户
	QList<Camares> *Actived =new QList<Camares>;
	//此链表代表未激活用户
	QList<Camares> *unActived = new QList<Camares>;



	//初始化两个链表
	void initNode();
	//检查Actived链表长度是否合法
	bool checkActivedLength();
	//检查用户是否以在Actived内，这里应该只检查座位号就行
	bool isUserActived(char* StuSeat);
	//输入一个学生的信息，然后从unActived中拿出一个节点的hwnd和学生信息组合，然后再将该节点插入Actived
	void InsertActived(char* StuName, char* StuSeat,char* pic);
	//输入一个学生的座位信息，然后从Actived中锁定该节点，将其学生数据抹去并插入到unActived中去
	void DeleteActived(char* StuSeat);
	//此方法将输入的参数解析成带有用户姓名和座位信息的userinfo结构体
	QList<UserInfo> * AnalyseInsert(char* insert);
	//解析获得一个学生座位列表
	QList<QString> *AnalyseSeat(char* seat);

	void DeleteUserNode(QString seat);
	void InserUserNode(QString Insert);
	
	//以下方法有关StuList
	//向ListWidget中插入一个UserInfo结点
	void AddList(UserInfo Students);
	//初始化listwidget，也可以用于刷新整个ListWidget
	void initListWidget();
	//遍历userList和Activated，对二者座次的重复项的userList进行勾选
	void CheckList();
	//遍历listWidget，检查当前listWidget，将未进入当前视频会议的用户压入Actived
	void InviteCheck();
	//当有用户离开或有用户加入的时候，刷新list
	void freshList();


	// 响应windows消息
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//发送Windows消息给指定窗口
	void onSendMessage(QString strMessage, QString Recivepath, ULONG_PTR MsgTYPE);
	bool eventFilter(QObject *obj, QEvent *event);
public:
	void region(const QPoint &currentGlobalPoint);  //鼠标的位置,改变光标


	//发送Windows消息
	//教师端信号
	//发送会议开始请求
	void InviteMessage();
	//向特定位置的学生发送学生端邀请
	void InviteStu(QString seat);
	//处理学生掉线信号
	void sLeave(QString seat);
	//会议结束请求
	void t_END();

	//学生端信号
	//学生端离开会议
	void s_LEAVE();
	//学生接到教师的结束会议的信号，自动关闭程序并断开连接
	void mtLEAVE();

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
