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
#include <windowsx.h> //GET_X_LPARAM��GET_Y_LPARAM
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

//��ʦ��������ܷ��� ������ܷ���ѧ����������
const ULONG_PTR tINVITE = WM_USER + 5935;
//��ʦ��������ܷ��� ��������ź�
const ULONG_PTR tEND = WM_USER + 5936;


//��������ʦ�˷��� ѧ�������ź�
const ULONG_PTR  mt_sLEAVE = WM_USER + 5937;
//��������ʦ�˷��� ѧ�������ź�
const ULONG_PTR  mt_sONLINE = WM_USER + 5942;
//�������ѧ������ ��ʦ�뿪�ź�
const ULONG_PTR ms_tLEAVE = WM_USER + 5938;
//�������ѧ���˷��� �µ�ѧ����������ź�
const ULONG_PTR ms_sINVITED = WM_USER + 5941;

//ѧ����������ܷ��� ѧ�������ź�
const ULONG sENTER = WM_USER + 5939;
//ѧ����������ܷ��� ѧ���뿪�ź�
const ULONG sLEAVE = WM_USER + 5940;


char* QString_2char(QString qs);
//�洢�û����ݵ�����
//������ǰ�û��� ���ھ�� ���� ���� ����״̬����һ���û��Ľڵ�
//��������ҳ�����Ҫ��β��ʼ�壬ȴҪ��ͷ��ʼ����������һ��˫������

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
	//Ϊ�˸��õ��б������struct��������д==�������������struct��seat���ʱ�������������.
	bool operator==(const Camares b) const {
		return this->seat == b.seat;
	}
};
struct Inivite {
	char* name = NULL;
	char* seat = NULL;
	char* image = NULL;
	QWidget *label = nullptr;
	//Ϊ�˸��õ��б������struct��������д==�������������struct��seat���ʱ�������������.
	bool operator==(const Camares b) const {
		return this->seat == b.seat;
	}


};






class LBD_VideoMeeting_Meeting : public QMainWindow
{
    Q_OBJECT

public:
    LBD_VideoMeeting_Meeting(QWidget *parent = Q_NULLPTR);
	//��ʦ�����
	//����:
	//hwnd:����ܵĴ��ھ��
	//sip,port��������ip�Ͷ˿�
	//ClassName���༶����
	//InvitedUsers����ѡ�����û�
	//userinfo ������ѧ��

	void Start(char* hwndName, char* sip, int port, char* ClassName, char* InvitedUsers, char* userinfo);

	//ѧ�������
	//����
	//hwnd:����ܵĴ��ھ��
	//sip,port��������ip�Ͷ˿�
	//currentSeat:��ǰѧ����λ
	//ClassName���༶����
	//InvitedUsers����ѡ�����û�
	//userinfo ������ѧ��
	void Start(char* hwndName, char *sip, int port, char *currentSeat, char* ClassName, char* InvitedUsers, char* userinfo);
private slots:
	void on_btn_invite_clicked(bool checked);
	//��������listwidget���͵����룬��ÿһλ�û����뵽������ȥ 
	void ReceiveInvite(QList<UserInfo> *Invited);
	//��listwidget�нӵ��µĹ�ѡ����󣬲鿴��ǰ�Ƿ���Խ������û�������
	bool getChecked();
	//��listwidget�нӵ��µ�ȡ������󣬼�鵱ǰ�Ƿ���Խ����û���ȡ��ѡ��
	bool getCancel();
	//��ʱ��
	void TimeLabelUpdate();
	//���밴ť
	void on_btn_InviteConfirm_clicked();
	//�����Խ���ť
	void on_btn_close_clicked();
	//�����Խ����Ͻ�
	void on_btn_close_2_clicked();
	//���������ź�
	void QUITSIGNAL();

signals:
	//���û����ݴ���֮��UserInfoָ�뷢�͸�ListWidget
	//����list����������ǰѧ������Ϣ�࣬��ǰѧ����������ǰ����������˽ṹ��
	void UserReady(QList<UserInfo> *users,char* ClassName,QList<Camares> *list);
signals:
	void CancelChecked();
private:


	//��������ܴ�������s
	QString mainFrameHWND;
	QTimer *timer = new QTimer();
	QTime counter;
	int Selected = 0;
	void debug(QString str);
	void debug(char* str);
    Ui::LBD_VideoMeeting_MeetingClass ui;
	//�����÷�������
	char* sroom = "LBD_VideoMeeting_Meeting";
	
	char* clsName;//�����༶���ƣ���ListWidget���õ�
	const char* theRoom = "LBD_VideoMeeting_Meeting";
	QList<UserInfo> *userList = new QList<UserInfo>;

	//���߷��������ڽ�QString����ת��Ϊchar*����
	char* QString2char(QString qs);

	QRect TotalFrame;

	//�����û����ݵĳ��ȣ�����initListWidget������ǰ�༶������
	int UsersLength = 0;

	//��ʼ��meadiasoupserver����
	void initConnection(char* sip, int port);
	//��ʼ������ͷ���
	void initCamare();
	//����ˢ�£�ͨ��Actived�����Ĵ��ھ�������������
	void FreshCams();
	//���������޸�Geometrys�Ű����
	void InitGeometry(int i);
	//����Invite��������ʼ��һЩ����ؼ�
	void InitItems(int i);
	//��ʦ1��ѧ��0
	int TypeUser = 0;



	//��ʼ����
	void StartMeeting(char* TeaName, char* TeaSeat);
	//ѧ���������
	void StuEnterMeeting(char* StuName, char* StuSeat,char* pic);
	void StuEnterMeeting(QString inform);
	//��ʼ��ʱѧ��������飬ֻ����һ��QList
	void StuEnterMeeting(QList<UserInfo> *invited);
	//ѧ���뿪����
	void StuLeaveMeeting(char* StuSeat);
	//��ʦ���ö������Բ��鵽������ȥ����
	Camares Teacher;
	//һ���������ص�ǰѧ���Ľ��
	Camares CurrentStudent;
	//һ������ר�Ÿ�����Ŀ���ʵҲû��Ҫר�Ž�һ�������Ǻÿ�
	Inivite Cam_Invite;
	//����һ������ı�ͷ��������������û�
	QList<Camares> *Actived =new QList<Camares>;
	//���������δ�����û�
	QList<Camares> *unActived = new QList<Camares>;



	//��ʼ����������
	void initNode();
	//���Actived�������Ƿ�Ϸ�
	bool checkActivedLength();
	//����û��Ƿ�����Actived�ڣ�����Ӧ��ֻ�����λ�ž���
	bool isUserActived(char* StuSeat);
	//����һ��ѧ������Ϣ��Ȼ���unActived���ó�һ���ڵ��hwnd��ѧ����Ϣ��ϣ�Ȼ���ٽ��ýڵ����Actived
	void InsertActived(char* StuName, char* StuSeat,char* pic);
	//����һ��ѧ������λ��Ϣ��Ȼ���Actived�������ýڵ㣬����ѧ������Ĩȥ�����뵽unActived��ȥ
	void DeleteActived(char* StuSeat);
	//�˷���������Ĳ��������ɴ����û���������λ��Ϣ��userinfo�ṹ��
	QList<UserInfo> * AnalyseInsert(char* insert);
	//�������һ��ѧ����λ�б�
	QList<QString> *AnalyseSeat(char* seat);

	void DeleteUserNode(QString seat);
	void InserUserNode(QString Insert);
	
	//���·����й�StuList
	//��ListWidget�в���һ��UserInfo���
	void AddList(UserInfo Students);
	//��ʼ��listwidget��Ҳ��������ˢ������ListWidget
	void initListWidget();
	//����userList��Activated���Զ������ε��ظ����userList���й�ѡ
	void CheckList();
	//����listWidget����鵱ǰlistWidget����δ���뵱ǰ��Ƶ������û�ѹ��Actived
	void InviteCheck();
	//�����û��뿪�����û������ʱ��ˢ��list
	void freshList();


	// ��Ӧwindows��Ϣ
	bool nativeEvent(const QByteArray &eventType, void *message, long *result);
	//����Windows��Ϣ��ָ������
	void onSendMessage(QString strMessage, QString Recivepath, ULONG_PTR MsgTYPE);
	bool eventFilter(QObject *obj, QEvent *event);
public:
	void region(const QPoint &currentGlobalPoint);  //����λ��,�ı���


	//����Windows��Ϣ
	//��ʦ���ź�
	//���ͻ��鿪ʼ����
	void InviteMessage();
	//���ض�λ�õ�ѧ������ѧ��������
	void InviteStu(QString seat);
	//����ѧ�������ź�
	void sLeave(QString seat);
	//�����������
	void t_END();

	//ѧ�����ź�
	//ѧ�����뿪����
	void s_LEAVE();
	//ѧ���ӵ���ʦ�Ľ���������źţ��Զ��رճ��򲢶Ͽ�����
	void mtLEAVE();

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
