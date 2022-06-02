#include "LBD_VideoMeeting_Meeting.h"

LBD_VideoMeeting_Meeting::LBD_VideoMeeting_Meeting(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	//ȡ��������ȥ��������,ȥ���������������ö�
	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
	//���ô������ƣ������շ�message
	
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

//��������밴ť���㿪��ʾlistwidget
void LBD_VideoMeeting_Meeting::on_btn_invite_clicked(bool checked)
{
	if (checked) {
		//ui.StuList->setWindowFlag(Qt::WindowStaysOnTopHint);
		ui.StuList->raise();
		ui.StuList->show();
	}
	else {
		//�رյ�ʱ��ǵ�ˢ��һ�£����⻺�浽δ���ӵ��û�
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
		//���++��numbers >=8�ˣ�Ҳ�����û������ˣ�������ʾ�򣬲�ȡ����ѡ���Checked״̬
		if (numbers > 8) {
			//
			// Ӧ������ʾ��
			//
			//ץȡ��Ϣ���͵Ķ���
			listitem *current = qobject_cast<listitem *>(sender());
			current->cancelChecked();

			return false;
		}

		ui.lab_num->setText(QString("(��������%1/8��)").arg(numbers));
	}

	return true;
	
}

bool LBD_VideoMeeting_Meeting::getCancel()
{
	//��ȡ�����źŵĶ���
	listitem *current = qobject_cast<listitem *>(sender());
	//��������Actived�б������ǰ�û������У�������ȡ��ѡ��
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

//��������������ȷ��
void LBD_VideoMeeting_Meeting::on_btn_InviteConfirm_clicked()
{
	//1.����listWidget����鵱ǰlistWidget����δ���뵱ǰ��Ƶ������û�ѹ��Actived
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
		//��ɶ�MediasoupServer������
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
		
		//��������ͷ������������
		SetVideoFullStretch(true);
		//�����ź�Դ
		SetSignalSource(true, true, false);
		debug("initCamare success");

		ui.listWidget->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{width:10px;background:rgba(0,0,0,0%);margin:0px,0px,0px,0px;padding-top:0px;padding-bottom:0px;}"
			"QScrollBar::handle:vertical{width:10px;background:rgba(0,0,0,25%);border-radius:2px;min-height:20;}"
			"QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical{height:10px;width:0px;}");

		ui.lab_num->setText(QString("(��������0/8��)"));
		

	
		
	}
	catch (QException ex) {
		debug("initCamare failed");
		qDebug() << ex.what()<<endl;
	}

}
//ˢ������ͷ����
void LBD_VideoMeeting_Meeting::FreshCams()
{
	//1.��Actived��������
	InitGeometry(Actived->size());

	//2.���û�������ͷ����ȥ

	//Ӧ�õ����ⲿ�ӿ�

	
	
}

void LBD_VideoMeeting_Meeting::InitGeometry(int i)
{
	try {
		int weight;
		int height;
		//ֱ����Actived�ڵ�label���ˣ�����Actived�Ѿ����ź������
		//ע�⣬ÿ��������ͬ�Ű治ͬ������ÿ����Ҫ��ȷ���������������в��ԣ��ٽ����Ű�
		//0����Զ�ǽ�ʦ��1-8����ѧ�� 
		//���ݲ�ͬ��ģʽ���벻ͬ�Ŀͻ���
		Camares temp;
		QString space = "   ";
		InitItems(i);
		ui.wid_close->setGeometry(906, 18, 16, 16);
		ui.wid_close->raise();
		Cam_Invite.label->setVisible(false);
	
		if (TypeUser == 1) {
			switch (i) {
			case 1:
				//���ý�ʦ�����Сλ�ú͵�һ��ѧ���Ĵ���λ�ã�Ȼ��ʣ�µĴ�������
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
			//�����ѧ�����������밴ť����һЩ��ť������λ��
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
			ui.nameitem1->setText(QString("%1��ʦ").arg(Teacher.name));

			switch (i) {
			case 1:
				//���ý�ʦ�����Сλ�ú͵�һ��ѧ���Ĵ���λ�ã�Ȼ��ʣ�µĴ�������
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
		//ѧ���뿪����
		s_LEAVE();
	}
	
}


//����ĳ�ʼ��
//��ʼ������Ļ��������Ѿ�������������ͷ��Actived��unActived��Ȼ�������������в���ڵ㡣
//��ʼ����ʱ��Actived��������ڵ㣬unActived����˸��ڵ�
//���������Ҫ��initHWND���������У�Ҳ����˵�����Ѿ��õ��˰˸�����ľ��
//����Ϊ��ͷ����������ͷ����
void LBD_VideoMeeting_Meeting::initNode()
{
	try {
		//���ȳ�ʼ���˸�����ͷ�ڵ�
		Camares Frame[8];
		//��ʼ���˸��ڵ�
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
		//������뵽unactived��ȥ
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
	//�൱����ˢ������ListWidget���Ƚ����г�Ա��գ�Ȼ���ٽ���Ա��������
	while (ui.listWidget->count() > 0)
	{
		QListWidgetItem *item = ui.listWidget->takeItem(0);
		delete item;
	}

	//1.�ҵ�Camares�����Ԫ�أ������е�Ԫ�رȶԣ���������λ����ͬ�����UserInfo Checked
	CheckList();

	//2.��users�е�����Ԫ��ѹ��AddList
	for (int i = 0; i < userList->size(); i++) {
		AddList(userList->at(i));
	}



}

void LBD_VideoMeeting_Meeting::CheckList()
{

	for (int i = 0; i < Actived->size(); i++) {
		for (int j = 0; j < userList->size(); j++) {
			if (QString(Actived->at(i).seat) == QString(userList->at(j).seat)) {
				//�ҵ��ˣ���isSelected��ѡ��
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
	

	//ֱ�ӽ�����listWidget�����б���ѡ���û�ȫ������ȥ����
	QString Invitation = "{";

	for(int i = 0;i<ui.listWidget->count();i++){
		listitem *temps = static_cast<listitem*>(ui.listWidget->itemWidget(ui.listWidget->item(i)));
		if (temps->CheckState) {
			Invitation = Invitation + QString(temps->seat);
			Invitation = Invitation + QString("}|{");
			//����ȫ�����뵽actived��ȥ
			InsertActived(QString2char(temps->name), QString2char(temps->seat), QString2char(temps->PicPath));

			//ˢ�½���
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
		//���������λ�����
		if (strcmp(Actived->at(i).seat , StuSeat) == 0) {
			return true;
		}
	}
	return false;
}
//��ʦ�����
void LBD_VideoMeeting_Meeting::Start(char* hwndName, char* sip, int port, char* ClassName, char* InvitedUsers, char* userinfo)
{
	try {
		
		//1.���ӵ�������
		initConnection(sip, port);
		this->setWindowTitle("LBD_VideoMeeting_Meeting_TEA");
		//2.��ȡ����ܵĴ��ھ��
		mainFrameHWND =QString(hwndName);
		TypeUser = 1;
		//3.����userinfo
		userList = AnalyseInsert(userinfo);
		//UserInfo *users = AnalyseInsert(userinfo);
		QList<UserInfo> *Invite = AnalyseInsert(InvitedUsers);

		clsName = ClassName;
		//4.��ý�ʦ����Ϣ
		Teacher.name = userList->at(0).name;
		Teacher.seat = userList->at(0).seat;
		Teacher.image = userList->at(0).image;
		Teacher.label = ui.Cam_Teacher;
		Teacher.label->SetName(Teacher.name);
		Teacher.label->SetPic(Teacher.image);
		debug(QString("The Teacher'name is %1,seat is %2").arg(Teacher.name).arg(Teacher.seat));
		userList->removeAt(0);
		qDebug() << userList->at(0).name;
		//5.����һЩ��ʼ��������г�ʼ������λ�÷ŵ�ѧ�����������ڲ��ˣ��ʲ��ڴ˳�ʼ��
		
		//��ʼ������
		initNode();
		//��Invited�û�����������ȥ
		for (int i = 0; i < Invite->size(); i++) {
			InsertActived(Invite->at(i).name, Invite->at(i).seat, Invite->at(i).image);
		}
		//��ʼ��һЩ����ؼ�
		InitItems(Invite->size());
		//��ʼ������
		InitGeometry(Invite->size());

		//��ʼ������ͷ����
		initCamare();
		ui.lab_className->setText(QString(ClassName));

		//5.����ǰ������û����ݲ��뵽listwidget
		initListWidget();

		//6.��ʼһ������
		//StartMeeting(Teacher.name, Teacher.seat);

		//7.�������ѧ���û����뵽������ȥ
		StuEnterMeeting(Invite);

		//8.�������巢���ź�
		InviteMessage();

		

		



		debug("Process Starting...");
	}
	catch (QException ex) {
		debug("Process Started failed");
		debug(ex.what());
	}


}
//ѧ�������
void LBD_VideoMeeting_Meeting::Start(char* hwndName, char * sip, int port, char * currentSeat, char * ClassName, char * InvitedUsers, char * userinfo)
{
	try {


		//1.���ӵ�������
		initConnection(sip, port);
		this->setWindowTitle("LBD_VideoMeeting_Meeting_STU");
		//2.��ȡ����ܴ��ھ��
		mainFrameHWND = QString(hwndName);
		TypeUser = 0;

		//3.����������Ϣ
		userList = AnalyseInsert(userinfo);
		//�����������û�
		QList<UserInfo> *Invite = AnalyseInsert(InvitedUsers);
		//�����༶����
		clsName = ClassName;

		//4.��ȡ��ʦ����Ϣ�͵�ǰѧ������Ϣ
		Teacher.name = userList->at(0).name;
		Teacher.seat = userList->at(0).seat;
		Teacher.image = userList->at(0).image;
		Teacher.label = ui.Cam_Teacher;
		Teacher.label->SetName(QString(Teacher.name));
		Teacher.label->SetPic(QString(Teacher.image));
		//ui.nameitem1->setText(Teacher.name);
		debug(QString("The Teacher'name is %1,seat is %2").arg(Teacher.name).arg(Teacher.seat));
		userList->removeAt(0);
		//��ȡ��ǰѧ����Ϣ,������ǰѧ���ŵ��ڶ�����ȥ
		QList<UserInfo> *currentUser = AnalyseInsert(currentSeat);
		CurrentStudent.name = currentUser->at(0).name;
		CurrentStudent.seat = currentUser->at(0).seat;
		CurrentStudent.image = currentUser->at(0).image;
		CurrentStudent.label = ui.Cam_Stu1;
		debug(QString("CurrentUser's name is %1,seat is %2").arg(CurrentStudent.name).arg(CurrentStudent.seat));
		InsertActived(CurrentStudent.name, CurrentStudent.seat, CurrentStudent.image);



		//���г�ʼ���
		//��ʼ������
		initNode();

		//��Invited�û�����������ȥ
		for (int i = 0; i < Invite->size(); i++) {
			InsertActived(Invite->at(i).name, Invite->at(i).seat, Invite->at(i).image);
		}

		//��ʼ������ؼ�
		InitItems(Invite->size());

		//��ʼ������
		InitGeometry(Invite->size());

		//��ʼ������ͷ����
		initCamare();
		ui.lab_className->setText(QString(ClassName));

		//5.�������
		//StartMeeting(Teacher.name, Teacher.seat);

		//6.�������ѧ�����뵽����ȥ
		StuEnterMeeting(Invite);
		
	}
	catch (QException ex) {
		debug("Process Started failed");
		debug(ex.what());
	}

}

//�����ʦ����������λ����ʼһ������
void LBD_VideoMeeting_Meeting::StartMeeting(char* TeaName, char* TeaSeat) {
	//1.�����ʦ�˼���,���ʦ�ڵ���������

	QString sperson = QString("{%1}{%2}{%3}{1}").arg(TeaName).arg(TeaSeat).arg((int)Teacher.label->winId());

	debug(QString("StartMeeting with sroom:%1 and sperson:%2").arg(QString2char(sperson)).arg(QString2char(sperson)));
	//2.��ʼһ������
	JoinMeeting(sroom, QString2char(sperson));

}
//����ѧ������������λ���뱾������
void LBD_VideoMeeting_Meeting::StuEnterMeeting(char* StuName, char* StuSeat,char* pic) {
	
	//1.�ȼ��Actived�Ƿ��Ѿ�����
	if (!checkActivedLength()) {
		return;
	}

	//2.�Խڵ���в�����unActived��β���ó�һ���ڵ����ӵ�Activedβ��
	InsertActived(StuName, StuSeat,pic);

	//3.ˢ�µ�ǰ����ͷλ��
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
	//�˷���ʱ������һ��ѧ���б�Ȼ������ѧ���б���ժȡѧ����Ϣѹ��Actived��ȥ
	for (int i = 0; i < invited->size(); i++) {
		InsertActived(invited->at(i).name, invited->at(i).seat,invited->at(i).image);
	}
	//������Ϻ�ˢ�½���
	InitGeometry(invited->size());

}
//����ѧ�������뿪����
void LBD_VideoMeeting_Meeting::StuLeaveMeeting(char * StuSeat)
{
	//1.�����뿪����ļ�飬������ʱ�ȿ��ţ���dll����������취
	//
	//Ӧ���м��
	//
	//2.�Խڵ���в�������Actived���ҵ�StuSeat���������β�����ɾȥ�������ýڵ�ŵ�unActived��ȥ
	DeleteActived(StuSeat);
	//3.���û���userList��ɾ��
	DeleteUserNode(StuSeat);
	//3.ˢ�µ�ǰ����ͷλ��
	FreshCams();
	initListWidget();

	
}

void LBD_VideoMeeting_Meeting::InsertActived(char * StuName, char * StuSeat,char* pic)
{
	try {
		//1.��鵱ǰ�û��Ƿ��Ѿ�����Actived�У��������������
		for (int i = 0; i < Actived->size(); i++) {
			if (QString(Actived->at(i).seat) == QString(StuSeat)) {
				return;
			}
		}

		//2.ȡ��һ���ڵ�
		if (unActived->isEmpty()) {
			debug("Unactived is empty");
			return;
		}
		if (isUserActived(StuSeat)) {
			//�����û�����Actived�����У����������û�
			return;

		}
		//��unActived���ó�һ���ڵ㣬ע��������λ�����Ǳ���label
		Camares temp = unActived->at(0);
		temp.name = StuName;
		temp.seat = StuSeat;
		temp.image = pic;
		temp.label = unActived->at(0).label;
		temp.label->SetName(QString(StuName));
		temp.label->SetPic(QString(pic));
		//3.���ýڵ��unActived��ɾ��
		unActived->removeAt(0);
		//4.���ýڵ�append����Actived����ʱ�����������
		Actived->append(temp);

		//5.�˴������ӿڣ�����ǰ������ͷ������ڸý���label��:::

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
		//1.������λ�û��Ƿ���Actived�ڣ���������ڣ����Զ�����
		for (int i = 0; i < Actived->size(); i++) {if (QString(Actived->at(i).seat) == QString(StuSeat)) {isExist = true;}}
		if (!isExist) { return; }
		//2.�ҵ��ý�㲢������ֵ
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
		//�����������Ľ��ѹ��unActived��ȥ
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
		if (insert == nullptr) { //ע�������������Ⱥ������ж����Ƿ�Ϊ��ָ�������������
								 ///

								 //������ʾ������Ĳ���Ϊ��
			qDebug() << "AnalyseInsert�������Ϊ��";
								 ///

			return nullptr;
		}

		//1.��������ģʽ
		QString temp = insert;
		QRegExp re1("[|]");
		QRegExp re2("(\\{)(\\S*)(\\})(\\{)(\\S*)(\\})(\\{)(\\S*)(\\})");

		re1.setMinimal(true);
		re2.setMinimal(true);

		//2.ͨ������ģʽ�з��ַ����б�
		QStringList Seperate = temp.split(re1);//�������insert��Ϣ�зֳ�һ��QStringList
		const int sizes = Seperate.size();
		UsersLength = sizes;
		//3.�����ַ����б��ȴ���һ��UserInfo���ͣ��зֳ��������֣�һ���ǽ�ʦ��һ����ʣ���ѧ��	
		QList<UserInfo> *results = new QList<UserInfo>;
		//4.�������ж����������ж�ʧ���򷵻�
		if (re2.indexIn(temp) == -1) {
			//

			//������ʾ���壬������

			//
			return nullptr;
		}
		//5.��ȡÿһ��Seperate�е���Ч���ּ���
		for (int i = 0; i < Seperate.size(); i++) {
			//���Seperate
			//������ʧ�ܣ���countinue
			if (re2.indexIn(Seperate[i]) == -1) {
				debug(QString("Analyse fail on %1 ").arg(Seperate[i]));
				continue;
			}
			//��ȡ��Ӧ����
			UserInfo temp;
			qDebug() << re2.capturedTexts();
			temp.name = QString2char(re2.capturedTexts()[2]);
			temp.seat = QString2char(re2.capturedTexts()[5]);
			debug(re2.capturedTexts()[8]);
			temp.image = QString2char(re2.capturedTexts()[8]);
			
			//������appen��QListȥ
			results->append(temp);
		}
		//���ػ�ȡ����results����

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
	if (seat == nullptr) { //ע�������������Ⱥ������ж����Ƿ�Ϊ��ָ�������������
	
		qDebug() << " ע�⣬������ϢΪ��"  ;

		return nullptr;
	}

	//1.��������ģʽ
	QString temp = seat;
	QRegExp re1("[|]");
	QRegExp re2("(\\{)(\\S*)(\\})");

	re1.setMinimal(true);
	re2.setMinimal(true);

	//2.ͨ������ģʽ�з��ַ����б�
	QStringList Seperate = temp.split(re1);//�������insert��Ϣ�зֳ�һ��QStringList
	const int sizes = Seperate.size();
	UsersLength = sizes;
	//3.�����ַ����б��ȴ���һ��UserInfo���ͣ��зֳ��������֣�һ���ǽ�ʦ��һ����ʣ���ѧ��	
	QList<QString> *results = new QList<QString>;
	//4.�������ж����������ж�ʧ���򷵻�
	if (re2.indexIn(temp) == -1) {
		//

		//������ʾ���壬������

		//
		return nullptr;
	}
	//5.��ȡÿһ��Seperate�е���Ч���ּ���
	for (int i = 0; i < Seperate.size(); i++) {
		//���Seperate
		//������ʧ�ܣ���countinue
		if (re2.indexIn(Seperate[i]) == -1) {
			debug(QString("Analyse fail on %1 ").arg(Seperate[i]));
			continue;
		}
		//��ȡ��Ӧ����
		QString temp;
		qDebug() << re2.capturedTexts();
		temp = QString2char(re2.capturedTexts()[2]);


		//������appen��QListȥ
		results->append(temp);
	}
	//���ػ�ȡ����results����

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
	//ˢ��ListWidget
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
		ui.lab_num->setText(QString("(��������%1/8��)").arg(Selected));
	}
	//listitemѡ�а�ť��ͻᷢ��һ����Ϣ��������
	connect(item, SIGNAL(newCheck()), this, SLOT(getChecked()));
	connect(item, SIGNAL(cancelCheck()), this, SLOT(getCancel()));

	QListWidgetItem *temp = new QListWidgetItem();
	QSize size = temp->sizeHint();
	temp->setSizeHint(QSize(size.width(), 30));

	ui.listWidget->addItem(temp);
	ui.listWidget->setItemWidget(temp, item);

}

//������Ϣ�¼�
bool LBD_VideoMeeting_Meeting::nativeEvent(const QByteArray & eventType, void * message, long * result)
{

	Q_UNUSED(eventType);
	MSG *msg = static_cast<MSG*>(message);  //����ת��
											/*�˴��ĽṹҲ����switch������*/
	if (msg->message == WM_COPYDATA)
	{

		COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
		//��ʦ�˽�����Ϣ
		if (TypeUser == 1) {
			//�������������ʦ�˷���ѧ�������ź�
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
			return false;  //����ֵΪfalse��ʾ���¼�����������ϴ��ݣ�����������

		}
		else if (TypeUser == 0) {

			if (cds->dwData == ms_tLEAVE)
			{
				mtLEAVE();

				*result = 1;
				return true;
			}
			else if (cds->dwData == ms_sINVITED) {
				//����Ӧ�ý��յ�ѧ����������Ϣ
				QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
				StuEnterMeeting(strMessage);
				
			}
			return false;  //����ֵΪfalse��ʾ���¼�����������ϴ��ݣ�����������

		}
	}

		return false;
	//	
	//}
	//return false;
}



void LBD_VideoMeeting_Meeting::onSendMessage(QString strMessage,QString Recivepath,ULONG_PTR MsgTYPE) {

	
	HWND hwnd = NULL;
	LPWSTR path = (LPWSTR)Recivepath.utf16(); //����һ��������Ϣ�Ĵ��ڣ���������Ӧ���Ƿ�����Ϣ�������
	hwnd = ::FindWindowW(NULL, path);//�ҵ�������Ϣ����Ĵ��ھ��


	if (::IsWindow(hwnd)) {

		QByteArray data = strMessage.toUtf8();
		COPYDATASTRUCT copydata;
		copydata.dwData = MsgTYPE; //The type of the data to be passed to the receiving application. The receiving application defines the valid types.
		copydata.lpData = data.data();// The data to be passed to the receiving application. This member can be NULL.
		copydata.cbData = data.size(); //The size, in bytes, of the data pointed to by the lpData member.
		//��õ�ǰWinId
		HWND sender = (HWND)effectiveWinId();
		//������Ϣ�ķ���
		//LRESULT SendMessage��HWND hWnd��UINT Msg��WPARAM wParam��LPARAM IParam����
		//hwnd ��������Ϣ�Ĵ�����
		//Msg:WM_COPYDATA��
		//wParam��Ϊ���ͽ��̵Ĵ�����
		//IParam��Ϊָ��COPYDATASTRUCT���ݽṹ��ָ�룻
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
{ // ��ȡ��������Ļ�ϵ�λ������topLeftΪ���Ͻǵ㣬rightButtonΪ���½ǵ�
	QRect rect = this->rect();

	QPoint topLeft = this->mapToGlobal(rect.topLeft()); //�����Ͻǵ�(0,0)ת��Ϊȫ������
	QPoint rightButton = this->mapToGlobal(rect.bottomRight());

	int x = currentGlobalPoint.x(); //��ǰ��������
	int y = currentGlobalPoint.y();

	if (((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
		&& ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
	{
		// ���Ͻ�
		dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // ���ù����״
	}
	else if (((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		// ���½�
		dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		//���½�
		dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
		&& ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
	{
		// ���Ͻ�
		dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if ((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
	{
		// ���
		dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
	{
		// �ұ�
		dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
	{
		// �ϱ�
		dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if ((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
	{
		// �±�
		dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else
	{
		// Ĭ��
		dir = NONE;
		this->setCursor(QCursor(Qt::ArrowCursor));
	}
}

void LBD_VideoMeeting_Meeting::InviteMessage()
{
	QString SendMessage = "{";
	//��Actived�ڵĳ�Ա����λ��ŷ��͸�����ܴ�Ϊת��
	for (int i = 0; i < Actived->size(); i++) {
		if (i != Actived->size() - 1) {
			SendMessage = SendMessage + QString(Actived->at(i).seat) + QString("}");
			SendMessage = SendMessage + QString("|{");
		}
		
		
	}
	SendMessage.chop(2);
	//����Ϣ���͸������
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
	//����һ��ѧ���뿪���ź�
	QString seat = QString(CurrentStudent.seat);
	onSendMessage(seat, mainFrameHWND, sLEAVE);
	//���ͺ��˳�exe
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
			this->mouseGrabber(); //���ص�ǰץȡ�������Ĵ���
		}
		else
		{
			m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
			//globalPos()���λ�ã�topLeft()�������Ͻǵ�λ��
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
	QPoint globalPoint = event->globalPos(); //���ȫ������
	QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
	QPoint topLeft = mapToGlobal(rect.topLeft());
	QPoint bottomRight = mapToGlobal(rect.bottomRight());

	if (this->windowState() != Qt::WindowMaximized)
	{
		if (!isLeftPressDown)  //û�а������ʱ
		{
			this->region(globalPoint); //���ڴ�С�ĸı䡪���ж����λ�ã��ı�����״
		}
		else
		{
			if (dir != NONE)
			{
				QRect newRect(topLeft, bottomRight); //����һ������  �϶������1000*1618

				switch (dir)
				{
				case LEFT:

					if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
					{
						newRect.setLeft(topLeft.x());  //С�ڽ������С���ʱ������Ϊ���ϽǺ�����Ϊ����x
													   //ֻ�ı���߽�
					}
					else
					{
						newRect.setLeft(globalPoint.x());
					}
					break;
				case RIGHT:
					newRect.setWidth(globalPoint.x() - topLeft.x());  //ֻ�ܸı��ұ߽�
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
				move(event->globalPos() - m_movePoint); //�ƶ�����
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
			this->releaseMouse(); //�ͷ����ץȡ
			this->setCursor(QCursor(Qt::ArrowCursor));
			dir = NONE; //��������ָ��
		}
	}
}



//������listitem�ؼ�����

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
	//����ǰ�ť��ѡ���˵��¼�����ô����Ҫ����һ��ѡ���źţ�����listwidgetȥ�жϵ�ǰ�Ƿ�����
	if (checked) {
		CheckState = checked;
		emit newCheck();
	}
	else {//���ȡ��һ����ť��ѡ�еĻ�������Ҫ������Ϣ�������壬�����Actived��һԱ����������ȡ��ѡ��
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
	this->setWindowFlags(Qt::FramelessWindowHint);                //ȡ��������ȥ��������,ȥ���������������ö�
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
{// ��ȡ��������Ļ�ϵ�λ������topLeftΪ���Ͻǵ㣬rightButtonΪ���½ǵ�
	QRect rect = this->rect();

	QPoint topLeft = this->mapToGlobal(rect.topLeft()); //�����Ͻǵ�(0,0)ת��Ϊȫ������
	QPoint rightButton = this->mapToGlobal(rect.bottomRight());

	int x = currentGlobalPoint.x(); //��ǰ��������
	int y = currentGlobalPoint.y();

	if (((topLeft.x() + PADDING >= x) && (topLeft.x() <= x))
		&& ((topLeft.y() + PADDING >= y) && (topLeft.y() <= y)))
	{
		// ���Ͻ�
		dir = LEFTTOP;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));  // ���ù����״
	}
	else if (((x >= rightButton.x() - PADDING) && (x <= rightButton.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		// ���½�
		dir = RIGHTBOTTOM;
		this->setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else if (((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
		&& ((y >= rightButton.y() - PADDING) && (y <= rightButton.y())))
	{
		//���½�
		dir = LEFTBOTTOM;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if (((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
		&& ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING)))
	{
		// ���Ͻ�
		dir = RIGHTTOP;
		this->setCursor(QCursor(Qt::SizeBDiagCursor));
	}
	else if ((x <= topLeft.x() + PADDING) && (x >= topLeft.x()))
	{
		// ���
		dir = LEFT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((x <= rightButton.x()) && (x >= rightButton.x() - PADDING))
	{
		// �ұ�
		dir = RIGHT;
		this->setCursor(QCursor(Qt::SizeHorCursor));
	}
	else if ((y >= topLeft.y()) && (y <= topLeft.y() + PADDING))
	{
		// �ϱ�
		dir = UP;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else if ((y <= rightButton.y()) && (y >= rightButton.y() - PADDING))
	{
		// �±�
		dir = DOWN;
		this->setCursor(QCursor(Qt::SizeVerCursor));
	}
	else
	{
		// Ĭ��
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
			this->mouseGrabber(); //���ص�ǰץȡ�������Ĵ���
		}
		else
		{
			m_movePoint = event->globalPos() - this->frameGeometry().topLeft();
			//globalPos()���λ�ã�topLeft()�������Ͻǵ�λ��
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
	QPoint globalPoint = event->globalPos(); //���ȫ������
	QRect rect = this->rect();  //rect == QRect(0,0 1280x720)
	QPoint topLeft = mapToGlobal(rect.topLeft());
	QPoint bottomRight = mapToGlobal(rect.bottomRight());

	if (this->windowState() != Qt::WindowMaximized)
	{
		if (!isLeftPressDown)  //û�а������ʱ
		{
			this->region(globalPoint); //���ڴ�С�ĸı䡪���ж����λ�ã��ı�����״
		}
		else
		{
			if (dir != NONE)
			{
				QRect newRect(topLeft, bottomRight); //����һ������  �϶������1000*1618

				switch (dir)
				{
				case LEFT:

					if (bottomRight.x() - globalPoint.x() <= this->minimumWidth())
					{
						newRect.setLeft(topLeft.x());  //С�ڽ������С���ʱ������Ϊ���ϽǺ�����Ϊ����x
													   //ֻ�ı���߽�
					}
					else
					{
						newRect.setLeft(globalPoint.x());
					}
					break;
				case RIGHT:
					newRect.setWidth(globalPoint.x() - topLeft.x());  //ֻ�ܸı��ұ߽�
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
				move(event->globalPos() - m_movePoint); //�ƶ�����
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
			this->releaseMouse(); //�ͷ����ץȡ
			this->setCursor(QCursor(Qt::ArrowCursor));
			dir = NONE; //��������ָ��
		}
	}
}


void Quit::on_btn_Close_2_clicked() {
	emit QUITMEETING();
	ExitMeeting();

	QApplication::exit();
}