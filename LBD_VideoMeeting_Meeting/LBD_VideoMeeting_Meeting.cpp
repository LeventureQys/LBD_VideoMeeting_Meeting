#include "LBD_VideoMeeting_Meeting.h"

LBD_VideoMeeting_Meeting::LBD_VideoMeeting_Meeting(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//取消标题栏去掉标题栏,去掉工具栏，窗口置顶
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	//设置窗口名称，便于收发message
	
	ui.wid_close->setVisible(false);








	ui.StuList->hide();
	counter.setHMS(0, 0, 0, 0);
	connect(timer, SIGNAL(timeout()), this, SLOT(TimeLabelUpdate()));
	timer->start(1000);

	//ui.mengban->installEventFilter(this);

	ui.centralWidget->installEventFilter(this);

	ui.StuList->raise();

	ui.lab_Invite->installEventFilter(this);

	ui.Cam_Invite->installEventFilter(this);


}

//这个是邀请按钮，点开显示listwidget
void LBD_VideoMeeting_Meeting::on_btn_invite_clicked(bool checked)
{
	if (checked) {
		//ui.StuList->setWindowFlag(Qt::WindowStaysOnTopHint);
		ui.StuList->raise();
		ui.StuList->show();
	}
	else {
		//关闭的时候记得刷新一下，避免缓存到未连接的用户
		initListWidget();
		ui.StuList->hide();
	}

}

void LBD_VideoMeeting_Meeting::ReceiveInvite(QList<UserInfo>* Invited)
{

}

bool LBD_VideoMeeting_Meeting::getChecked()
{
	int numbers = 0;
	for (int i = 0; i < ui.listWidget->count(); i++) {
		listitem *temps = static_cast<listitem*>(ui.listWidget->itemWidget(ui.listWidget->item(i)));
		if (temps->isChecked()) {
			numbers++;
		}
		//如果++后numbers >=8了，也就是用户超限了，弹出提示框，并取消该选项的Checked状态
		if (numbers > 8) {
			//
			// 应弹出提示框
			//
			//抓取消息发送的对象
			listitem *current = qobject_cast<listitem *>(sender());
			current->cancelChecked();

			return false;
		}

		ui.lab_num->setText(QString("(最多可邀请%1/8人)").arg(numbers));
	}

	return true;
	
}

bool LBD_VideoMeeting_Meeting::getCancel()
{
	//获取发送信号的对象
	listitem *current = qobject_cast<listitem *>(sender());
	//检索整个Actived列表，如果当前用户在其中，则不允许取消选定
	for (int i = 0; i < Actived->size(); i++) {
		if (current->seat == QString(Actived->at(i).seat));
		{
			current->setChecked();
		}

	}
	return false;
}

void LBD_VideoMeeting_Meeting::TimeLabelUpdate()
{
	counter = counter.addSecs(1);
	ui.lab_timer->setText(counter.toString());
}

//这个是邀请界面点击确定
void LBD_VideoMeeting_Meeting::on_btn_InviteConfirm_clicked()
{
	//1.遍历listWidget，检查当前listWidget，将未进入当前视频会议的用户压入Actived
	ui.StuList->raise();
	InviteCheck();

	

}

void LBD_VideoMeeting_Meeting::debug(QString str)
{
	qDebug() << str;
}

void LBD_VideoMeeting_Meeting::debug(char * str)
{
	qDebug() << QString(str);
}

void LBD_VideoMeeting_Meeting::initConnection(char* sip, int port) {
	try {
		//完成对MediasoupServer的连接
		SetMediasoupServerAddress(sip, port);
		debug(QString("Connect to sip:%1 , port:%2 successfully").arg(sip).arg(port));
	}
	catch (QException ex) {
		debug("Connect failed");
		qDebug() << ex.what()<<endl;
	}

}

void LBD_VideoMeeting_Meeting::initCamare() {
	try {
		
		//设置摄像头可以铺满窗口
		SetVideoFullStretch(true);
		//设置信号源
		SetSignalSource(true, true, false);
		debug("initCamare success");

		ui.listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{width:10px;background:rgba(0,0,0,0%);margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
			"QScrollBar::handle:vertical{width:10px;background:rgba(0,0,0,25%);border-radius:2px;min-height:20;}"
			"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical{height:10px;width:0px;}");

		ui.lab_num->setText(QString("(最多可邀请0/8人)"));
		

	
		
	}
	catch (QException ex) {
		debug("initCamare failed");
		qDebug() << ex.what()<<endl;
	}

}
//刷新摄像头排序
void LBD_VideoMeeting_Meeting::FreshCams()
{
	//1.对Actived进行排序
	InitGeometry(Actived->size());

	//2.将用户的摄像头贴上去

	//应该调用外部接口

	
	
}

void LBD_VideoMeeting_Meeting::InitGeometry(int i)
{
	try {
		int weight;
		int height;
		//直接排Actived内的label算了，反正Actived已经是排好序的了
		//注意，每次人数不同排版不同，所以每次需要先确定人数，给定排列策略，再进行排版
		//0号永远是教师，1-8才是学生 
		//根据不同的模式进入不同的客户端
		Camares temp;
		QString space = "   ";
		InitItems(i);
		ui.wid_close->setGeometry(906, 18, 16, 16);
		ui.wid_close->raise();
		Cam_Invite.label->setVisible(false);
	
		if (TypeUser == 1) {
			switch (i) {
			case 1:
				//设置教师窗体大小位置和第一个学生的窗体位置，然后将剩下的窗体屏蔽
				weight = 470;
				height = 540;
			 
				Teacher.label->setGeometry(0, 0, weight, height);
				
				Actived->at(0).label->setGeometry(weight, 0, weight, height);

				for (int i = 0; i < 1; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 1; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				
				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));
				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();

				break;
			case 2:
				Teacher.label->setGeometry(0, 0, 470, 540);
				Actived->at(0).label->setGeometry(470, 0, 470, 270);
				Actived->at(1).label->setGeometry(470, 270, 470, 270);
				for (int i = 0; i < 2; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 2; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));
				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();

				break;
			case 3:
				weight = 470;
				height = 270;
				Teacher.label->setGeometry(0, 0, weight, height);
				temp.label = Actived->at(0).label;
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(weight, height, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);

				for (int i = 0; i < 3; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 3; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));
				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);
				ui.nameitem3->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();

				break;
			case 4:
				weight = 313;
				height = 270;
				
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);
				Actived->at(3).label->setGeometry(weight, height, weight, height);
				Cam_Invite.label->setGeometry(2 * weight, height, weight, height);

				Cam_Invite.label->setVisible(true);
				Cam_Invite.label->setStyleSheet("QWidget:!hover{background-color: rgb(51, 51, 51);image: url(:/new/prefix1/Add_default.png);}"
					"QWidget:hover{background-color:rgb(51,51,51); image: url(:/new/prefix1/Add_hover.png);}");
				for (int i = 0; i < 4; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 4; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));


				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);
				ui.nameitem3->setVisible(true);
				ui.nameitem4->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();


				break;
			case 5:
				weight = 313;
				height = 270;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);
				Actived->at(3).label->setGeometry(weight, height, weight, height);
				Actived->at(4).label->setGeometry(2 * weight, height, weight, height);
				for (int i = 0; i < 5; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 5; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);
				ui.nameitem3->setVisible(true);
				ui.nameitem4->setVisible(true);
				ui.nameitem5->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();

				break;
			case 6:
				weight = 235;
				height = 269;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(3 * weight, 0, weight, height);
				Actived->at(3).label->setGeometry(0, height, weight, height);
				Actived->at(4).label->setGeometry(weight, height, weight, height);
				Actived->at(5).label->setGeometry(2 * weight, height, weight, height);
				Cam_Invite.label->setGeometry(3 * weight, height, weight, height);
				Cam_Invite.label->setVisible(true);
				Cam_Invite.label->setStyleSheet("QWidget:!hover{background-color: rgb(51, 51, 51);image: url(:/new/prefix1/Add_default.png);}"
					"QWidget:hover{background-color:rgb(51,51,51); image: url(:/new/prefix1/Add_hover.png);}");
				for (int i = 0; i < 6; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 6; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);

				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem6->setGeometry(Actived->at(5).label->x() + Actived->at(5).label->width()*0.1, Actived->at(5).label->y() + Actived->at(5).label->height()*0.85, 75, 23);
				ui.nameitem6->setText(QString("%1%2").arg(space).arg(Actived->at(5).name));

				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);
				ui.nameitem3->setVisible(true);
				ui.nameitem4->setVisible(true);
				ui.nameitem5->setVisible(true);
				ui.nameitem6->setVisible(true);


				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				ui.nameitem6->raise();
				break;
			case 7:
				weight = 235;
				height = 269;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(3 * weight, 0, weight, height);
				Actived->at(3).label->setGeometry(0, height, weight, height);
				Actived->at(4).label->setGeometry(weight, height, weight, height);
				Actived->at(5).label->setGeometry(2 * weight, height, weight, height);
				Actived->at(6).label->setGeometry(3 * weight, height, weight, height);
				for (int i = 0; i < 7; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 7; i < Actived->size(); i++) {
					Actived->at(i).label->setVisible(false);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem6->setGeometry(Actived->at(5).label->x() + Actived->at(5).label->width()*0.1, Actived->at(5).label->y() + Actived->at(5).label->height()*0.85, 75, 23);
				ui.nameitem6->setText(QString("%1%2").arg(space).arg(Actived->at(5).name));

				ui.nameitem7->setGeometry(Actived->at(6).label->x() + Actived->at(6).label->width()*0.1, Actived->at(6).label->y() + Actived->at(6).label->height()*0.85, 75, 23);
				ui.nameitem7->setText(QString("%1%2").arg(space).arg(Actived->at(6).name));
				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);
				ui.nameitem3->setVisible(true);
				ui.nameitem4->setVisible(true);
				ui.nameitem5->setVisible(true);
				ui.nameitem6->setVisible(true);
				ui.nameitem7->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				ui.nameitem6->raise();
				ui.nameitem7->raise();

				break;
			case 8:
				weight = 313;
				height = 180;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);
				Actived->at(3).label->setGeometry(weight, height, weight, height);
				Actived->at(4).label->setGeometry(2 * weight, height, weight, height);
				Actived->at(5).label->setGeometry(0, 2 * height, weight, height);
				Actived->at(6).label->setGeometry(weight, 2 * height, weight, height);
				Actived->at(7).label->setGeometry(2 * weight, 2 * height, weight, height);
				Cam_Invite.label->setVisible(false);
				ui.nameitem0->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem1->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 75, 23);
				ui.nameitem1->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem6->setGeometry(Actived->at(5).label->x() + Actived->at(5).label->width()*0.1, Actived->at(5).label->y() + Actived->at(5).label->height()*0.85, 75, 23);
				ui.nameitem6->setText(QString("%1%2").arg(space).arg(Actived->at(5).name));

				ui.nameitem7->setGeometry(Actived->at(6).label->x() + Actived->at(6).label->width()*0.1, Actived->at(6).label->y() + Actived->at(6).label->height()*0.85, 75, 23);
				ui.nameitem7->setText(QString("%1%2").arg(space).arg(Actived->at(6).name));

				ui.nameitem8->setGeometry(Actived->at(7).label->x() + Actived->at(7).label->width()*0.1, Actived->at(7).label->y() + Actived->at(7).label->height()*0.85+5, 75, 23);
				ui.nameitem8->setText(QString("%1%2").arg(space).arg(Actived->at(7).name));
				for (int i = 0; i <8; i++) {
					Actived->at(i).label->setVisible(true);
				}
				ui.nameitem0->setVisible(true);
				ui.nameitem1->setVisible(true);
				ui.nameitem2->setVisible(true);
				ui.nameitem3->setVisible(true);
				ui.nameitem4->setVisible(true);
				ui.nameitem5->setVisible(true);
				ui.nameitem6->setVisible(true);
				ui.nameitem7->setVisible(true);
				ui.nameitem8->setVisible(true);

				ui.nameitem0->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				ui.nameitem6->raise();
				ui.nameitem7->raise();
				ui.nameitem8->raise();

				break;

			}
			ui.StuList->raise();
			ui.mengban->raise();
			

		}
		else {
			//如果是学生，屏蔽邀请按钮，有一些按钮得重设位置
			ui.btn_invite->setVisible(false);
			ui.lab_invite->setVisible(false);
			ui.btn_cam->setGeometry(352, 554, 64, 34);
			ui.lab_cam->setGeometry(354, 595, 60, 11);
			ui.btn_mic->setGeometry(438,554,64,34);
			ui.lab_mic->setGeometry(446, 595, 60, 11);
			ui.btn_close->setGeometry(524, 554, 64, 34);
			ui.lab_end->setGeometry(535, 595, 60, 11);
			Cam_Invite.label->setVisible(false);
			ui.nameitem1->setVisible(true);
			ui.nameitem1->setText(QString("%1老师").arg(Teacher.name));

			switch (i) {
			case 1:
				//设置教师窗体大小位置和第一个学生的窗体位置，然后将剩下的窗体屏蔽
				weight = 470;
				height = 540;

				Teacher.label->setGeometry(0, 0, weight, height);

				Actived->at(0).label->setGeometry(weight, 0, weight, height);

				for (int i = 0; i < 1; i++) {
					Actived->at(i).label->setVisible(true);
				}

				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50,32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
			
				break;
			case 2:
				Teacher.label->setGeometry(0, 0, 470, 540);
				Actived->at(0).label->setGeometry(470, 0, 470, 270);
				Actived->at(1).label->setGeometry(470, 270, 470, 270);
				for (int i = 0; i < 2; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				break;
			case 3:
				weight = 470;
				height = 270;
				Teacher.label->setGeometry(0, 0, weight, height);
				temp.label = Actived->at(0).label;
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(weight, height, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);

				for (int i = 0; i < 3; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				break;
			case 4:
				weight = 313;
				height = 270;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);
				Actived->at(3).label->setGeometry(weight, height, weight, height);
				Cam_Invite.label->setGeometry(2 * weight, height, weight, height);

				Cam_Invite.label->setVisible(true);
				Cam_Invite.label->setStyleSheet("QWidget:!hover{background-color: rgb(51, 51, 51);image: url(:/new/prefix1/Add_default.png);}"
					"QWidget:hover{background-color:rgb(51,51,51); image: url(:/new/prefix1/Add_hover.png);}");
				qDebug() << Cam_Invite.label->isVisible();
				for (int i = 0; i < 4; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 4; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				break;
			case 5:
				weight = 313;
				height = 270;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);
				Actived->at(3).label->setGeometry(weight, height, weight, height);
				Actived->at(4).label->setGeometry(2 * weight, height, weight, height);
				for (int i = 0; i < 5; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				break;
			case 6:
				weight = 235;
				height = 269;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(3 * weight, 0, weight, height);
				Actived->at(3).label->setGeometry(0, height, weight, height);
				Actived->at(4).label->setGeometry(weight, height, weight, height);
				Actived->at(5).label->setGeometry(2 * weight, height, weight, height);
				Cam_Invite.label->setGeometry(3 * weight, height, weight, height);
				Cam_Invite.label->setVisible(true);
				Cam_Invite.label->setStyleSheet("QWidget:!hover{background-color: rgb(51, 51, 51);image: url(:/new/prefix1/Add_default.png);}"
					"QWidget:hover{background-color:rgb(51,51,51); image: url(:/new/prefix1/Add_hover.png);}");
				for (int i = 0; i < 6; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);

				}
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem6->setGeometry(Actived->at(5).label->x() + Actived->at(5).label->width()*0.1, Actived->at(5).label->y() + Actived->at(5).label->height()*0.85, 75, 23);
				ui.nameitem6->setText(QString("%1%2").arg(space).arg(Actived->at(5).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				ui.nameitem6->raise();
				break;
			case 7:
				weight = 235;
				height = 269;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(3 * weight, 0, weight, height);
				Actived->at(3).label->setGeometry(0, height, weight, height);
				Actived->at(4).label->setGeometry(weight, height, weight, height);
				Actived->at(5).label->setGeometry(2 * weight, height, weight, height);
				Actived->at(6).label->setGeometry(3 * weight, height, weight, height);
				for (int i = 0; i < 7; i++) {
					Actived->at(i).label->setVisible(true);
				}
				for (int i = 0; i < unActived->size(); i++) {
					unActived->at(i).label->setVisible(false);
				}
				Cam_Invite.label->setVisible(false);
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem6->setGeometry(Actived->at(5).label->x() + Actived->at(5).label->width()*0.1, Actived->at(5).label->y() + Actived->at(5).label->height()*0.85, 75, 23);
				ui.nameitem6->setText(QString("%1%2").arg(space).arg(Actived->at(5).name));

				ui.nameitem7->setGeometry(Actived->at(6).label->x() + Actived->at(6).label->width()*0.1, Actived->at(6).label->y() + Actived->at(6).label->height()*0.85, 75, 23);
				ui.nameitem7->setText(QString("%1%2").arg(space).arg(Actived->at(6).name));
				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				ui.nameitem6->raise();
				ui.nameitem7->raise();
			
				break;
			case 8:
				weight = 313;
				height = 180;
				Teacher.label->setGeometry(0, 0, weight, height);
				Actived->at(0).label->setGeometry(weight, 0, weight, height);
				Actived->at(1).label->setGeometry(2 * weight, 0, weight, height);
				Actived->at(2).label->setGeometry(0, height, weight, height);
				Actived->at(3).label->setGeometry(weight, height, weight, height);
				Actived->at(4).label->setGeometry(2 * weight, height, weight, height);
				Actived->at(5).label->setGeometry(0, 2 * height, weight, height);
				Actived->at(6).label->setGeometry(weight, 2 * height, weight, height);
				Actived->at(7).label->setGeometry(2 * weight, 2 * height, weight, height);
				Cam_Invite.label->setVisible(false);
				ui.nameitem1->setGeometry(Teacher.label->x() + Teacher.label->width()*0.1, Teacher.label->y() + Teacher.label->height()*0.85, 133, 32);
				

				ui.nameitem_me->setGeometry(Actived->at(0).label->x() + Actived->at(0).label->width()*0.1, Actived->at(0).label->y() + Actived->at(0).label->height()*0.85, 50, 32);
				//ui.nameitem_me->setText(QString("%1%2").arg(space).arg(Actived->at(0).name));

				ui.nameitem2->setGeometry(Actived->at(1).label->x() + Actived->at(1).label->width()*0.1, Actived->at(1).label->y() + Actived->at(1).label->height()*0.85, 75, 23);
				ui.nameitem2->setText(QString("%1%2").arg(space).arg(Actived->at(1).name));

				ui.nameitem3->setGeometry(Actived->at(2).label->x() + Actived->at(2).label->width()*0.1, Actived->at(2).label->y() + Actived->at(2).label->height()*0.85, 75, 23);
				ui.nameitem3->setText(QString("%1%2").arg(space).arg(Actived->at(2).name));

				ui.nameitem4->setGeometry(Actived->at(3).label->x() + Actived->at(3).label->width()*0.1, Actived->at(3).label->y() + Actived->at(3).label->height()*0.85, 75, 23);
				ui.nameitem4->setText(QString("%1%2").arg(space).arg(Actived->at(3).name));

				ui.nameitem5->setGeometry(Actived->at(4).label->x() + Actived->at(4).label->width()*0.1, Actived->at(4).label->y() + Actived->at(4).label->height()*0.85, 75, 23);
				ui.nameitem5->setText(QString("%1%2").arg(space).arg(Actived->at(4).name));

				ui.nameitem6->setGeometry(Actived->at(5).label->x() + Actived->at(5).label->width()*0.1, Actived->at(5).label->y() + Actived->at(5).label->height()*0.85, 75, 23);
				ui.nameitem6->setText(QString("%1%2").arg(space).arg(Actived->at(5).name));

				ui.nameitem7->setGeometry(Actived->at(6).label->x() + Actived->at(6).label->width()*0.1, Actived->at(6).label->y() + Actived->at(6).label->height()*0.85, 75, 23);
				ui.nameitem7->setText(QString("%1%2").arg(space).arg(Actived->at(6).name));

				ui.nameitem8->setGeometry(Actived->at(7).label->x() + Actived->at(7).label->width()*0.1, Actived->at(7).label->y() + Actived->at(7).label->height()*0.85, 75, 23);
				ui.nameitem8->setText(QString("%1%2").arg(space).arg(Actived->at(7).name));
				for (int i = 0; i < 8; i++) {
					Actived->at(i).label->setVisible(true);
				}

				ui.nameitem_me->raise();
				ui.nameitem1->raise();
				ui.nameitem2->raise();
				ui.nameitem3->raise();
				ui.nameitem4->raise();
				ui.nameitem5->raise();
				ui.nameitem6->raise();
				ui.nameitem7->raise();
				ui.nameitem8->raise();
				break;
				
			}
			
		}
		



		debug("InitGeometry success");
	}
	catch (QException ex) {
		debug("InitGeometry fail");
		qDebug() << ex.what();
	}
	
}

void LBD_VideoMeeting_Meeting::InitItems(int i)
{
	if(TypeUser ==1){
		ui.nameitem_me->setVisible(false);
		switch (i) {
		case 1:
			ui.nameitem1->setVisible(true);
			ui.nameitem0->setVisible(true);
			ui.nameitem2->setVisible(false);
			ui.nameitem3->setVisible(false);
			ui.nameitem4->setVisible(false);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 2:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(false);
			ui.nameitem4->setVisible(false);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 3:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(false);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 4:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 5:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 6:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(true);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 7:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(true);
			ui.nameitem7->setVisible(true);
			ui.nameitem8->setVisible(false);
			break;
		case 8:
			ui.nameitem0->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(true);
			ui.nameitem7->setVisible(true);
			ui.nameitem8->setVisible(true);
			break;
		}
	}
	else if (TypeUser == 0) {
		ui.nameitem0->setVisible(false);
		switch (i) {
		case 1:
			ui.nameitem1->setVisible(true);
			ui.nameitem_me->setVisible(true);
			ui.nameitem2->setVisible(false);
			ui.nameitem3->setVisible(false);
			ui.nameitem4->setVisible(false);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 2:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(false);
			ui.nameitem4->setVisible(false);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 3:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(false);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 4:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(false);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 5:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(false);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 6:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(true);
			ui.nameitem7->setVisible(false);
			ui.nameitem8->setVisible(false);
			break;
		case 7:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(true);
			ui.nameitem7->setVisible(true);
			ui.nameitem8->setVisible(false);
			break;
		case 8:
			 ui.nameitem_me->setVisible(true);
			ui.nameitem1->setVisible(true);
			ui.nameitem2->setVisible(true);
			ui.nameitem3->setVisible(true);
			ui.nameitem4->setVisible(true);
			ui.nameitem5->setVisible(true);
			ui.nameitem6->setVisible(true);
			ui.nameitem7->setVisible(true);
			ui.nameitem8->setVisible(true);
			break;
		}
	}
	

}

void LBD_VideoMeeting_Meeting::on_btn_close_clicked() {
	;
	Quit *temp = new Quit(Q_NULLPTR);
	connect(temp, SIGNAL(QUITMEETING()), this, SLOT(QUITSIGNAL()));
	temp->show();

}
void LBD_VideoMeeting_Meeting::on_btn_close_2_clicked() {
	
	Quit *temp = new Quit(Q_NULLPTR);
	connect(temp, SIGNAL(QUITMEETING()), this, SLOT(QUITSIGNAL()));
	temp->show();

}

void LBD_VideoMeeting_Meeting::QUITSIGNAL()
{
	if (TypeUser == 1) {
		t_END();
	}
	else if (TypeUser == 0) {
		//学生离开会议
		s_LEAVE();
	}
	
}


//链表的初始化
//初始化链表的话，我们已经建立了两个表头，Actived和unActived，然后向两个链表中插入节点。
//初始化的时候，Actived链表不插入节点，unActived插入八个节点
//这个函数需要在initHWND函数中运行，也就是说现在已经得到了八个窗体的句柄
//链表为有头链表，不是无头链表
void LBD_VideoMeeting_Meeting::initNode()
{
	try {
		//首先初始化八个摄像头节点
		Camares Frame[8];
		//初始化八个节点
		Frame[0].label = ui.Cam_Stu1;
		Frame[1].label = ui.Cam_Stu2;
		Frame[2].label = ui.Cam_Stu3;
		Frame[3].label = ui.Cam_Stu4;
		Frame[4].label = ui.Cam_Stu5;
		Frame[5].label = ui.Cam_Stu6;
		Frame[6].label = ui.Cam_Stu7;
		Frame[7].label = ui.Cam_Stu8;
		Cam_Invite.name = nullptr;
		Cam_Invite.seat = nullptr;
		Cam_Invite.image = nullptr;
		Cam_Invite.label = ui.Cam_Invite;
		//将其插入到unactived中去
		for (int i = 0; i < 8; i++) {
			Frame[i].name = nullptr;
			Frame[i].seat = nullptr;
			Frame[i].image = nullptr;
			unActived->append(Frame[i]);
		}
		debug("initCamNode Success");
	}
	catch (QException ex) {
		debug("initCamNode Failed");
	}

	
}

void LBD_VideoMeeting_Meeting::initListWidget()
{
	//相当于是刷新整个ListWidget，先将所有成员清空，然后再将成员插入其中
	while (ui.listWidget->count() > 0)
	{
		QListWidgetItem *item = ui.listWidget->takeItem(0);
		delete item;
	}

	//1.找到Camares里面的元素，将其中的元素比对，若二者座位号相同，则对UserInfo Checked
	CheckList();

	//2.将users中的所有元素压入AddList
	for (int i = 0; i < userList->size(); i++) {
		AddList(userList->at(i));
	}



}

void LBD_VideoMeeting_Meeting::CheckList()
{

	for (int i = 0; i < Actived->size(); i++) {
		for (int j = 0; j < userList->size(); j++) {
			if (QString(Actived->at(i).seat) == QString(userList->at(j).seat)) {
				//找到了，将isSelected勾选上
				UserInfo temp;
				temp.name = userList->at(j).name;
				temp.seat = userList->at(j).seat;
				temp.image = userList->at(j).image;
				temp.isSelected = true;
				userList->replace(j, temp);
			}
		}
	}
}

void LBD_VideoMeeting_Meeting::InviteCheck()
{
	

	//直接将整个listWidget中所有被框选的用户全部传上去算了
	QString Invitation = "{";

	for(int i = 0;i<ui.listWidget->count();i++){
		listitem *temps = static_cast<listitem*>(ui.listWidget->itemWidget(ui.listWidget->item(i)));
		if (temps->CheckState) {
			Invitation = Invitation + QString(temps->seat);
			Invitation = Invitation + QString("}|{");
			//将其全部插入到actived中去
			InsertActived(QString2char(temps->name), QString2char(temps->seat), QString2char(temps->PicPath));

			//刷新界面
			InitGeometry(Actived->size());
		}
	}

	Invitation.chop(2);
	InviteStu(Invitation);
	
}

void LBD_VideoMeeting_Meeting::freshList()
{
}


bool LBD_VideoMeeting_Meeting::checkActivedLength() {
	if (Actived->size() <= 8 && Actived->size() > 0) {
		return true;
	}
	else {
		return false;
	}
}

bool LBD_VideoMeeting_Meeting::isUserActived(char * StuSeat)
{
	for (int i = 0; i < Actived->size(); i++) {
		//如果两个座位号相等
		if (strcmp(Actived->at(i).seat , StuSeat) == 0) {
			return true;
		}
	}
	return false;
}
//教师端入口
void LBD_VideoMeeting_Meeting::Start(char* hwndName, char* sip, int port, char* ClassName, char* InvitedUsers, char* userinfo)
{
	try {
		
		//1.连接到服务器
		initConnection(sip, port);
		this->setWindowTitle("LBD_VideoMeeting_Meeting_TEA");
		//2.获取主框架的窗口句柄
		mainFrameHWND =QString(hwndName);
		TypeUser = 1;
		//3.解析userinfo
		userList = AnalyseInsert(userinfo);
		//UserInfo *users = AnalyseInsert(userinfo);
		QList<UserInfo> *Invite = AnalyseInsert(InvitedUsers);

		clsName = ClassName;
		//4.获得教师的信息
		Teacher.name = userList->at(0).name;
		Teacher.seat = userList->at(0).seat;
		Teacher.image = userList->at(0).image;
		Teacher.label = ui.Cam_Teacher;
		Teacher.label->SetName(Teacher.name);
		Teacher.label->SetPic(Teacher.image);
		debug(QString("The Teacher'name is %1,seat is %2").arg(Teacher.name).arg(Teacher.seat));
		userList->removeAt(0);
		qDebug() << userList->at(0).name;
		//5.进行一些初始化活动，其中初始化窗体位置放到学生进入会议的内部了，故不在此初始化
		
		//初始化链表
		initNode();
		//将Invited用户插入链表中去
		for (int i = 0; i < Invite->size(); i++) {
			InsertActived(Invite->at(i).name, Invite->at(i).seat, Invite->at(i).image);
		}
		//初始化一些窗体控件
		InitItems(Invite->size());
		//初始化窗体
		InitGeometry(Invite->size());

		//初始化摄像头设置
		initCamare();
		ui.lab_className->setText(QString(ClassName));

		//5.将当前输入的用户数据插入到listwidget
		initListWidget();

		//6.开始一场会议
		//StartMeeting(Teacher.name, Teacher.seat);

		//7.将输入的学生用户插入到窗口中去
		StuEnterMeeting(Invite);

		//8.向主窗体发送信号
		InviteMessage();

		

		



		debug("Process Starting...");
	}
	catch (QException ex) {
		debug("Process Started failed");
		debug(ex.what());
	}


}
//学生端入口
void LBD_VideoMeeting_Meeting::Start(char* hwndName, char * sip, int port, char * currentSeat, char * ClassName, char * InvitedUsers, char * userinfo)
{
	try {


		//1.连接到服务器
		initConnection(sip, port);
		this->setWindowTitle("LBD_VideoMeeting_Meeting_STU");
		//2.获取主框架窗口句柄
		mainFrameHWND = QString(hwndName);
		TypeUser = 0;

		//3.解析接收信息
		userList = AnalyseInsert(userinfo);
		//解析受邀请用户
		QList<UserInfo> *Invite = AnalyseInsert(InvitedUsers);
		//解析班级名称
		clsName = ClassName;

		//4.获取教师的信息和当前学生的信息
		Teacher.name = userList->at(0).name;
		Teacher.seat = userList->at(0).seat;
		Teacher.image = userList->at(0).image;
		Teacher.label = ui.Cam_Teacher;
		Teacher.label->SetName(QString(Teacher.name));
		Teacher.label->SetPic(QString(Teacher.image));
		//ui.nameitem1->setText(Teacher.name);
		debug(QString("The Teacher'name is %1,seat is %2").arg(Teacher.name).arg(Teacher.seat));
		userList->removeAt(0);
		//获取当前学生信息,并将当前学生放到第二个点去
		QList<UserInfo> *currentUser = AnalyseInsert(currentSeat);
		CurrentStudent.name = currentUser->at(0).name;
		CurrentStudent.seat = currentUser->at(0).seat;
		CurrentStudent.image = currentUser->at(0).image;
		CurrentStudent.label = ui.Cam_Stu1;
		debug(QString("CurrentUser's name is %1,seat is %2").arg(CurrentStudent.name).arg(CurrentStudent.seat));
		InsertActived(CurrentStudent.name, CurrentStudent.seat, CurrentStudent.image);



		//进行初始化活动
		//初始化链表
		initNode();

		//将Invited用户插入链表中去
		for (int i = 0; i < Invite->size(); i++) {
			InsertActived(Invite->at(i).name, Invite->at(i).seat, Invite->at(i).image);
		}

		//初始化窗体控件
		InitItems(Invite->size());

		//初始化窗体
		InitGeometry(Invite->size());

		//初始化摄像头设置
		initCamare();
		ui.lab_className->setText(QString(ClassName));

		//5.进入会议
		//StartMeeting(Teacher.name, Teacher.seat);

		//6.将输入的学生插入到窗口去
		StuEnterMeeting(Invite);
		
	}
	catch (QException ex) {
		debug("Process Started failed");
		debug(ex.what());
	}

}

//输入教师的姓名、座位，开始一场会议
void LBD_VideoMeeting_Meeting::StartMeeting(char* TeaName, char* TeaSeat) {
	//1.先令教师端加入,向教师节点输入数据

	QString sperson = QString("{%1}{%2}{%3}{1}").arg(TeaName).arg(TeaSeat).arg((int)Teacher.label->winId());

	debug(QString("StartMeeting with sroom:%1 and sperson:%2").arg(QString2char(sperson)).arg(QString2char(sperson)));
	//2.开始一场会议
	JoinMeeting(sroom, QString2char(sperson));

}
//输入学生的姓名和座位进入本场会议
void LBD_VideoMeeting_Meeting::StuEnterMeeting(char* StuName, char* StuSeat,char* pic) {
	
	//1.先检查Actived是否已经满了
	if (!checkActivedLength()) {
		return;
	}

	//2.对节点进行操作，unActived从尾端拿出一个节点来加到Actived尾端
	InsertActived(StuName, StuSeat,pic);

	//3.刷新当前摄像头位次
	FreshCams();

}
void LBD_VideoMeeting_Meeting::StuEnterMeeting(QString inform)
{
	QList<UserInfo> *nUser = AnalyseInsert(QString2char(inform));

	for (int i = 0; i < nUser->size(); i++) {
		if (Actived->size() <= 8) {
			InsertActived(nUser->at(i).name, nUser->at(i).seat, nUser->at(i).image);
		}
		else {
			qDebug() << "Inserstion out of range";
		}

	}
	InitGeometry(Actived->size());

}
void LBD_VideoMeeting_Meeting::StuEnterMeeting(QList<UserInfo> *invited)
{
	//此方法时输入了一个学生列表，然后从这个学生列表中摘取学生信息压入Actived中去
	for (int i = 0; i < invited->size(); i++) {
		InsertActived(invited->at(i).name, invited->at(i).seat,invited->at(i).image);
	}
	//插入完毕后刷新界面
	InitGeometry(invited->size());

}
//输入学生座次离开会议
void LBD_VideoMeeting_Meeting::StuLeaveMeeting(char * StuSeat)
{
	//1.进行离开会议的检查，这里暂时先空着，等dll下来了再想办法
	//
	//应该有检查
	//
	//2.对节点进行操作，从Actived中找到StuSeat决定的座次并将其删去，并将该节点放到unActived中去
	DeleteActived(StuSeat);
	//3.将用户从userList中删除
	DeleteUserNode(StuSeat);
	//3.刷新当前摄像头位次
	FreshCams();
	initListWidget();

	
}

void LBD_VideoMeeting_Meeting::InsertActived(char * StuName, char * StuSeat,char* pic)
{
	try {
		//1.检查当前用户是否已经存在Actived中，如果存在则跳过
		for (int i = 0; i < Actived->size(); i++) {
			if (QString(Actived->at(i).seat) == QString(StuSeat)) {
				return;
			}
		}

		//2.取出一个节点
		if (unActived->isEmpty()) {
			debug("Unactived is empty");
			return;
		}
		if (isUserActived(StuSeat)) {
			//若该用户以在Actived链表中，则跳过该用户
			return;

		}
		//从unActived中拿出一个节点，注入姓名座位，但是保留label
		Camares temp = unActived->at(0);
		temp.name = StuName;
		temp.seat = StuSeat;
		temp.image = pic;
		temp.label = unActived->at(0).label;
		temp.label->SetName(QString(StuName));
		temp.label->SetPic(QString(pic));
		//3.将该节点从unActived中删除
		unActived->removeAt(0);
		//4.将该节点append进入Actived，此时结点迭代已完成
		Actived->append(temp);

		//5.此处保留接口：将当前的摄像头画面绑定在该结点的label上:::

		//

		//
		
		//
		debug("InsertActived success");
	}
	catch(QException ex) {
		debug("InsertActived failed");
		debug(ex.what());
		}


}

void LBD_VideoMeeting_Meeting::DeleteActived(char * StuSeat)
{
	try {
		bool isExist = false;
		//1.检查该座位用户是否在Actived内，如果不存在，则自动跳过
		for (int i = 0; i < Actived->size(); i++) {if (QString(Actived->at(i).seat) == QString(StuSeat)) {isExist = true;}}
		if (!isExist) { return; }
		//2.找到该结点并缓存其值
		Camares temp;
		for (int i = 0; i < Actived->size(); i++) {
			if (QString(Actived->at(i).seat) == QString(StuSeat)) {
				temp.label = Actived->at(i).label;
				temp.name = NULL;
				temp.seat = NULL;
				temp.image = NULL;
				
				Actived->removeAt(i);

				break;
			}
		}
		//将缓存下来的结点压入unActived中去
		unActived->append(temp);
		
		
		debug("DeleteActived success");
	}
	catch (QException ex) {
		debug("DeleteActived failed");
		debug(ex.what());
	}

	
}

QList<UserInfo> * LBD_VideoMeeting_Meeting::AnalyseInsert(char * insert)
{
	try {
		if (insert == nullptr) { //注意这里是两个等号用来判定其是否为空指针而不是拿来判
								 ///

								 //弹出提示，输入的参数为空
			qDebug() << "AnalyseInsert输入参数为空";
								 ///

			return nullptr;
		}

		//1.配置正则模式
		QString temp = insert;
		QRegExp re1("[|]");
		QRegExp re2("(\\{)(\\S*)(\\})(\\{)(\\S*)(\\})(\\{)(\\S*)(\\})");

		re1.setMinimal(true);
		re2.setMinimal(true);

		//2.通过正则模式切分字符串列表
		QStringList Seperate = temp.split(re1);//将输入的insert消息切分出一个QStringList
		const int sizes = Seperate.size();
		UsersLength = sizes;
		//3.根据字符串列表长度创建一个UserInfo类型，切分成两个部分，一个是教师，一个是剩余的学生	
		QList<UserInfo> *results = new QList<UserInfo>;
		//4.测试下判定结果，如果判定失败则返回
		if (re2.indexIn(temp) == -1) {
			//

			//弹出提示窗体，并返回

			//
			return nullptr;
		}
		//5.提取每一个Seperate中的有效数字即可
		for (int i = 0; i < Seperate.size(); i++) {
			//拆分Seperate
			//如果拆分失败，则countinue
			if (re2.indexIn(Seperate[i]) == -1) {
				debug(QString("Analyse fail on %1 ").arg(Seperate[i]));
				continue;
			}
			//读取对应数据
			UserInfo temp;
			qDebug() << re2.capturedTexts();
			temp.name = QString2char(re2.capturedTexts()[2]);
			temp.seat = QString2char(re2.capturedTexts()[5]);
			debug(re2.capturedTexts()[8]);
			temp.image = QString2char(re2.capturedTexts()[8]);
			
			//将数据appen进QList去
			results->append(temp);
		}
		//返回获取到的results数组

		qDebug() << "Analyse successful:" << results;
	
		return results;
	}
	catch (QException ex) {
		debug("Analyse failed");
		debug(ex.what());
	}

}

QList<QString>* LBD_VideoMeeting_Meeting::AnalyseSeat(char * seat)
{
	if (seat == nullptr) { //注意这里是两个等号用来判定其是否为空指针而不是拿来判
	
		qDebug() << " 注意，输入信息为空"  ;

		return nullptr;
	}

	//1.配置正则模式
	QString temp = seat;
	QRegExp re1("[|]");
	QRegExp re2("(\\{)(\\S*)(\\})");

	re1.setMinimal(true);
	re2.setMinimal(true);

	//2.通过正则模式切分字符串列表
	QStringList Seperate = temp.split(re1);//将输入的insert消息切分出一个QStringList
	const int sizes = Seperate.size();
	UsersLength = sizes;
	//3.根据字符串列表长度创建一个UserInfo类型，切分成两个部分，一个是教师，一个是剩余的学生	
	QList<QString> *results = new QList<QString>;
	//4.测试下判定结果，如果判定失败则返回
	if (re2.indexIn(temp) == -1) {
		//

		//弹出提示窗体，并返回

		//
		return nullptr;
	}
	//5.提取每一个Seperate中的有效数字即可
	for (int i = 0; i < Seperate.size(); i++) {
		//拆分Seperate
		//如果拆分失败，则countinue
		if (re2.indexIn(Seperate[i]) == -1) {
			debug(QString("Analyse fail on %1 ").arg(Seperate[i]));
			continue;
		}
		//读取对应数据
		QString temp;
		qDebug() << re2.capturedTexts();
		temp = QString2char(re2.capturedTexts()[2]);


		//将数据appen进QList去
		results->append(temp);
	}
	//返回获取到的results数组

	qDebug() << "Analyse successful:" << results;

	return results;
}

void LBD_VideoMeeting_Meeting::DeleteUserNode(QString seat)
{
	for (int i = 0; i < userList->size(); i++) {
		if (userList->at(i).seat == seat) {
			userList->removeAt(i);
		}
	}
	//刷新ListWidget
	initListWidget();
}

void LBD_VideoMeeting_Meeting::InserUserNode(QString Insert)
{
	qDebug() << "execting " << Insert;
	QList<UserInfo> *temp = AnalyseInsert(QString2char(Insert));
	for (int i = 0; i < temp->size(); i++) {
		UserInfo temps;
		temps.name = temp->at(i).name;
		temps.seat = temp->at(i).seat;
		temps.image = temp->at(i).image;
		temps.isSelected = false;
		userList->append(temps);
	}

}

void LBD_VideoMeeting_Meeting::AddList(UserInfo Students)
{

	listitem *item = new listitem();
	item->setName(Students.name);
	item->setPic(Students.image);
	item->seat = Students.seat;
	if (Students.isSelected) {
		item->setChecked();
		Selected++;
		ui.lab_num->setText(QString("(最多可邀请%1/8人)").arg(Selected));
	}
	//listitem选中按钮后就会发送一个消息给主窗体
	connect(item, SIGNAL(newCheck()), this, SLOT(getChecked()));
	connect(item, SIGNAL(cancelCheck()), this, SLOT(getCancel()));

	QListWidgetItem *temp = new QListWidgetItem();
	QSize size = temp->sizeHint();
	temp->setSizeHint(QSize(size.width(), 30));

	ui.listWidget->addItem(temp);
	ui.listWidget->setItemWidget(temp, item);

}

//接收消息事件
bool LBD_VideoMeeting_Meeting::nativeEvent(const QByteArray & eventType, void * message, long * result)
{

	Q_UNUSED(eventType);
	MSG *msg = static_cast<MSG*>(message);  //类型转换
											/*此处的结构也可用switch来代替*/
	if (msg->message == WM_COPYDATA)
	{

		COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
		//教师端接收消息
		if (TypeUser == 1) {
			//如果是主框架向教师端发送学生掉线信号
			if (cds->dwData == mt_sLEAVE)
			{
				QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);

				sLeave(strMessage);

				*result = 1;
				return true;
			}
			else if (cds->dwData == mt_sONLINE) {

				QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);

				InserUserNode(strMessage);
			}
			return false;  //返回值为false表示该事件还会继续向上传递，被其他捕获

		}
		else if (TypeUser == 0) {

			if (cds->dwData == ms_tLEAVE)
			{
				mtLEAVE();

				*result = 1;
				return true;
			}
			else if (cds->dwData == ms_sINVITED) {
				//这里应该接收到学生的所有信息
				QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
				StuEnterMeeting(strMessage);
				
			}
			return false;  //返回值为false表示该事件还会继续向上传递，被其他捕获

		}
	}

		return false;
	//	
	//}
	//return false;
}



void LBD_VideoMeeting_Meeting::onSendMessage(QString strMessage,QString Recivepath,ULONG_PTR MsgTYPE) {

	
	HWND hwnd = NULL;
	LPWSTR path = (LPWSTR)Recivepath.utf16(); //定义一个接收消息的窗口，这里我们应该是发送消息给主框架
	hwnd = ::FindWindowW(NULL, path);//找到接收消息窗体的窗口句柄


	if (::IsWindow(hwnd)) {

		QByteArray data = strMessage.toUtf8();
		COPYDATASTRUCT copydata;
		copydata.dwData = MsgTYPE; //The type of the data to be passed to the receiving application. The receiving application defines the valid types.
		copydata.lpData = data.data();// The data to be passed to the receiving application. This member can be NULL.
		copydata.cbData = data.size(); //The size, in bytes, of the data pointed to by the lpData member.
		//获得当前WinId
		HWND sender = (HWND)effectiveWinId();
		//进行消息的发送
		//LRESULT SendMessage（HWND hWnd，UINT Msg，WPARAM wParam，LPARAM IParam）；
		//hwnd ：接收消息的窗体句柄
		//Msg:WM_COPYDATA；
		//wParam：为发送进程的窗体句柄
		//IParam：为指向COPYDATASTRUCT数据结构的指针；
		::SendMessage(hwnd, WM_COPYDATA, reinterpret_cast<WPARAM>(sender), reinterpret_cast<LPARAM>(&copydata));
	}


}

bool LBD_VideoMeeting_Meeting::eventFilter(QObject * obj, QEvent * event)
{	if (obj == (QObject*)ui.centralWidget) {
		if (event->type() == QEvent::Enter) {
			ui.mengban->show();
			ui.mengban->raise();
			ui.wid_close->raise();
		}
		else if (event->type() == QEvent::Leave) {
			ui.mengban->hide();
			ui.wid_close->raise();
		}
	}else if (obj = (QObject*)ui.Cam_Invite) {
		if (event->type() == QMouseEvent::MouseButtonPress) {
			if (TypeUser == 1) { on_btn_invite_clicked(true); 
			}
		}
	}
	else if (obj == (QObject*)ui.wid_close) {
		if (event->type() == QMouseEvent::MouseButtonPress) {
			if (TypeUser == 1) {
				on_btn_invite_clicked(true);
			}
		}
	}

	return false;
}



char * LBD_VideoMeeting_Meeting::QString2char(QString qs)
{
	std::string str = qs.toStdString();
	const char* ch = str.c_str();
	int nLen = strlen(ch);
	char* ch2 = new char[nLen + 2];
	strcpy(ch2, ch);
	return ch2;
}




void LBD_VideoMeeting_Meeting::region(const QPoint & currentGlobalPoint)
{ // 获取窗体在屏幕上的位置区域，topLeft为坐上角点，rightButton为右下角点
	QRect rect = this->rect();

	QPoint topLeft = this->mapToGlobal(rect.topLeft()); //将左上角的(0,0)转化为全局坐标
	QPoint rightButton = this->mapToGlobal(rect.bottomRight());

	int x = currentGlobalPoint.x(); //当前鼠标的坐标
	int y = currentGlobalPoint.y();

	if (((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
		&& ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
	{
		// 左上角
		dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置光标形状
	}
	else if (((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		// 右下角
		dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		//左下角
		dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
		&& ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
	{
		// 右上角
		dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if ((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
	{
		// 左边
		dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
	{
		// 右边
		dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
	{
		// 上边
		dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if ((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
	{
		// 下边
		dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else
	{
		// 默认
		dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

void LBD_VideoMeeting_Meeting::InviteMessage()
{
	QString SendMessage = "{";
	//将Actived内的成员的座位编号发送给主框架代为转发
	for (int i = 0; i < Actived->size(); i++) {
		if (i != Actived->size() - 1) {
			SendMessage = SendMessage + QString(Actived->at(i).seat) + QString("}");
			SendMessage = SendMessage + QString("|{");
		}
		
		
	}
	SendMessage.chop(2);
	//将消息发送给主框架
	onSendMessage(SendMessage, mainFrameHWND, tINVITE);
}

void LBD_VideoMeeting_Meeting::InviteStu(QString seat)
{
	onSendMessage(seat, mainFrameHWND, tINVITE);
}

void LBD_VideoMeeting_Meeting::sLeave(QString seat)
{
	QList<QString> *leave = AnalyseSeat(QString2char(seat));
	for (int i = 0; i < leave->size(); i++) {
		StuLeaveMeeting(QString2char(leave->at(i)));

		qDebug() << QString("seat %1 Leave the Meeting...").arg(QString2char(leave->at(i)));
	}
}

void LBD_VideoMeeting_Meeting::t_END()
{
	QString STOP = QString("ExitMeeting");
	onSendMessage(STOP, mainFrameHWND, tEND);
}

void LBD_VideoMeeting_Meeting::s_LEAVE()
{
	//发送一个学生离开的信号
	QString seat = QString(CurrentStudent.seat);
	onSendMessage(seat, mainFrameHWND, sLEAVE);
	//发送后退出exe
	ExitMeeting();

	QApplication::exit();
}

void LBD_VideoMeeting_Meeting::mtLEAVE()
{ 
	qDebug() << "TEACHER LEAVE...STUDENT QUITING";
	
	ExitMeeting();

	QApplication::exit();
}

void LBD_VideoMeeting_Meeting::mousePressEvent(QMouseEvent * event)
{
	switch (event->button()) {

	case Qt::LeftButton: isLeftPressDown = true;

		if (dir != NONE)
		{
			this->mouseGrabber(); //返回当前抓取鼠标输入的窗口
		}
		else
		{
			m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
			//globalPos()鼠标位置，topLeft()窗口左上角的位置
		}
		break;
	case Qt::RightButton:
		//this->setWindowState(Qt::WindowMinimized);
		break;
	default:
		LBD_VideoMeeting_Meeting::mousePressEvent(event);
	}
}

void LBD_VideoMeeting_Meeting::mouseMoveEvent(QMouseEvent * event)
{
	QPoint globalPoint = event->globalPos(); //鼠标全局坐标
	QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
	QPoint topLeft = mapToGlobal(rect.topLeft());
	QPoint bottomRight = mapToGlobal(rect.bottomRight());

	if (this->windowState() != Qt::WindowMaximized)
	{
		if (!isLeftPressDown)  //没有按下左键时
		{
			this->region(globalPoint); //窗口大小的改变——判断鼠标位置，改变光标形状
		}
		else
		{
			if (dir != NONE)
			{
				QRect newRect(topLeft, bottomRight); //定义一个矩形  拖动后最大1000*1618

				switch (dir)
				{
				case LEFT:

					if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
					{
						newRect.setLeft(topLeft.x());  //小于界面的最小宽度时，设置为左上角横坐标为窗口x
													   //只改变左边界
					}
					else
					{
						newRect.setLeft(globalPoint.x());
					}
					break;
				case RIGHT:
					newRect.setWidth(globalPoint.x() - topLeft.x());  //只能改变右边界
					break;
				case UP:
					if (bottomRight.y() - globalPoint.y() <= this->minimumHeight())
					{
						newRect.setY(topLeft.y());
					}
					else
					{
						newRect.setY(globalPoint.y());
					}
					break;
				case DOWN:
					newRect.setHeight(globalPoint.y() - topLeft.y());
					break;
				case LEFTTOP:
					if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
					{
						newRect.setX(topLeft.x());
					}
					else
					{
						newRect.setX(globalPoint.x());
					}

					if (bottomRight.y() - globalPoint.y() <= this->minimumHeight())
					{
						newRect.setY(topLeft.y());
					}
					else
					{
						newRect.setY(globalPoint.y());
					}
					break;
				case RIGHTTOP:
					if (globalPoint.x() - topLeft.x() >= this->minimumWidth())
					{
						newRect.setWidth(globalPoint.x() - topLeft.x());
					}
					else
					{
						newRect.setWidth(bottomRight.x() - topLeft.x());
					}
					if (bottomRight.y() - globalPoint.y() >= this->minimumHeight())
					{
						newRect.setY(globalPoint.y());
					}
					else
					{
						newRect.setY(topLeft.y());
					}
					break;
				case LEFTBOTTOM:
					if (bottomRight.x() - globalPoint.x() >= this->minimumWidth())
					{
						newRect.setX(globalPoint.x());
					}
					else
					{
						newRect.setX(topLeft.x());
					}
					if (globalPoint.y() - topLeft.y() >= this->minimumHeight())
					{
						newRect.setHeight(globalPoint.y() - topLeft.y());
					}
					else
					{
						newRect.setHeight(bottomRight.y() - topLeft.y());
					}
					break;
				case RIGHTBOTTOM:
					newRect.setWidth(globalPoint.x() - topLeft.x());
					newRect.setHeight(globalPoint.y() - topLeft.y());
					break;
				default:
					break;
				}
				this->setGeometry(newRect);
			}
			else
			{
				move(event->globalPos() - m_movePoint); //移动窗口
				event->accept();
			}
		}
	}
}

void LBD_VideoMeeting_Meeting::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		isLeftPressDown = false;
		if (dir != NONE)
		{
			this->releaseMouse(); //释放鼠标抓取
			this->setCursor(QCursor(Qt::ArrowCursor));
			dir = NONE; //热心网友指正
		}
	}
}



//以下是listitem控件方法

listitem::listitem(QWidget *parent) {
	ui.setupUi(this);

}

void listitem::setPic(QString picpath) {
	QString tempsheet = ui.label->styleSheet();
	tempsheet = tempsheet + QString("border-image: url(%1);").arg(picpath);
	ui.label->setStyleSheet(tempsheet);
	PicPath = picpath;
}

void listitem::setName(QString stuname)
{
	ui.label_2->setText(stuname);
	name = stuname;
}

bool listitem::setChecked()
{
	//
	ui.pushButton->setChecked(true);
	CheckState = true;
	return CheckState;
}

void listitem::cancelChecked()
{
	ui.pushButton->setChecked(false);
	CheckState = false;
}

bool listitem::isChecked()
{
	return ui.pushButton->isChecked();
}

void listitem::notCancel()
{
	setChecked();
}

void listitem::on_pushButton_clicked(bool checked) {
	//如果是按钮被选中了的事件，那么则需要发送一个选中信号，交给listwidget去判断当前是否满人
	if (checked) {
		CheckState = checked;
		emit newCheck();
	}
	else {//如果取消一个按钮的选中的话，还需要发送消息给主窗体，如果是Actived的一员，还不能让取消选中
		CheckState = checked;
		emit cancelCheck();
	}

}

char * QString_2char(QString qs)

	{
		std::string str = qs.toStdString();
		const char* ch = str.c_str();
		int nLen = strlen(ch);
		char* ch2 = new char[nLen + 2];
		strcpy(ch2, ch);
		return ch2;
	}


nameItem::nameItem(QWidget *parent) {
	ui.setupUi(this);
}

void nameItem::setName(QString strMsg)
{
	ui.lab_name->setText(strMsg);
}


TnameItem::TnameItem(QWidget *parent) {
	ui.setupUi(this);
}
Quit::Quit(QWidget *parent) :QWidget(parent) {
	ui.setupUi(this);
	this->setWindowFlags(Qt::FramelessWindowHint);                //取消标题栏去掉标题栏,去掉工具栏，窗口置顶
	setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
}

void Quit::on_btn_Close_clicked() {
	emit QUITMEETING();
	ExitMeeting();

	QApplication::exit();

}

void Quit::on_btn_Cancel_clicked() {

	this->close();
}

void Quit::region(const QPoint & currentGlobalPoint)
{// 获取窗体在屏幕上的位置区域，topLeft为坐上角点，rightButton为右下角点
	QRect rect = this->rect();

	QPoint topLeft = this->mapToGlobal(rect.topLeft()); //将左上角的(0,0)转化为全局坐标
	QPoint rightButton = this->mapToGlobal(rect.bottomRight());

	int x = currentGlobalPoint.x(); //当前鼠标的坐标
	int y = currentGlobalPoint.y();

	if (((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
		&& ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
	{
		// 左上角
		dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // 设置光标形状
	}
	else if (((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		// 右下角
		dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		//左下角
		dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
		&& ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
	{
		// 右上角
		dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if ((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
	{
		// 左边
		dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
	{
		// 右边
		dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
	{
		// 上边
		dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if ((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
	{
		// 下边
		dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else
	{
		// 默认
		dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}

}

void Quit::mousePressEvent(QMouseEvent * event)
{
	switch (event->button())
	{
	case Qt::LeftButton:
		isLeftPressDown = true;

		if (dir != NONE)
		{
			this->mouseGrabber(); //返回当前抓取鼠标输入的窗口
		}
		else
		{
			m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
			//globalPos()鼠标位置，topLeft()窗口左上角的位置
		}
		break;
	case Qt::RightButton:
		//this->setWindowState(Qt::WindowMinimized);
		break;
	default:
		Quit::mousePressEvent(event);
	}
}

void Quit::mouseMoveEvent(QMouseEvent * event)
{
	QPoint globalPoint = event->globalPos(); //鼠标全局坐标
	QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
	QPoint topLeft = mapToGlobal(rect.topLeft());
	QPoint bottomRight = mapToGlobal(rect.bottomRight());

	if (this->windowState() != Qt::WindowMaximized)
	{
		if (!isLeftPressDown)  //没有按下左键时
		{
			this->region(globalPoint); //窗口大小的改变——判断鼠标位置，改变光标形状
		}
		else
		{
			if (dir != NONE)
			{
				QRect newRect(topLeft, bottomRight); //定义一个矩形  拖动后最大1000*1618

				switch (dir)
				{
				case LEFT:

					if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
					{
						newRect.setLeft(topLeft.x());  //小于界面的最小宽度时，设置为左上角横坐标为窗口x
													   //只改变左边界
					}
					else
					{
						newRect.setLeft(globalPoint.x());
					}
					break;
				case RIGHT:
					newRect.setWidth(globalPoint.x() - topLeft.x());  //只能改变右边界
					break;
				case UP:
					if (bottomRight.y() - globalPoint.y() <= this->minimumHeight())
					{
						newRect.setY(topLeft.y());
					}
					else
					{
						newRect.setY(globalPoint.y());
					}
					break;
				case DOWN:
					newRect.setHeight(globalPoint.y() - topLeft.y());
					break;
				case LEFTTOP:
					if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
					{
						newRect.setX(topLeft.x());
					}
					else
					{
						newRect.setX(globalPoint.x());
					}

					if (bottomRight.y() - globalPoint.y() <= this->minimumHeight())
					{
						newRect.setY(topLeft.y());
					}
					else
					{
						newRect.setY(globalPoint.y());
					}
					break;
				case RIGHTTOP:
					if (globalPoint.x() - topLeft.x() >= this->minimumWidth())
					{
						newRect.setWidth(globalPoint.x() - topLeft.x());
					}
					else
					{
						newRect.setWidth(bottomRight.x() - topLeft.x());
					}
					if (bottomRight.y() - globalPoint.y() >= this->minimumHeight())
					{
						newRect.setY(globalPoint.y());
					}
					else
					{
						newRect.setY(topLeft.y());
					}
					break;
				case LEFTBOTTOM:
					if (bottomRight.x() - globalPoint.x() >= this->minimumWidth())
					{
						newRect.setX(globalPoint.x());
					}
					else
					{
						newRect.setX(topLeft.x());
					}
					if (globalPoint.y() - topLeft.y() >= this->minimumHeight())
					{
						newRect.setHeight(globalPoint.y() - topLeft.y());
					}
					else
					{
						newRect.setHeight(bottomRight.y() - topLeft.y());
					}
					break;
				case RIGHTBOTTOM:
					newRect.setWidth(globalPoint.x() - topLeft.x());
					newRect.setHeight(globalPoint.y() - topLeft.y());
					break;
				default:
					break;
				}
				this->setGeometry(newRect);
			}
			else
			{
				move(event->globalPos() - m_movePoint); //移动窗口
				event->accept();
			}
		}
	}
}

void Quit::mouseReleaseEvent(QMouseEvent * event)
{
	if (event->button() == Qt::LeftButton)
	{
		isLeftPressDown = false;
		if (dir != NONE)
		{
			this->releaseMouse(); //释放鼠标抓取
			this->setCursor(QCursor(Qt::ArrowCursor));
			dir = NONE; //热心网友指正
		}
	}
}


void Quit::on_btn_Close_2_clicked() {
	emit QUITMEETING();
	ExitMeeting();

	QApplication::exit();
}