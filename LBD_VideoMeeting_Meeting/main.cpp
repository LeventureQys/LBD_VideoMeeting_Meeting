#include "LBD_VideoMeeting_Meeting.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication::setQuitOnLastWindowClosed(false); 
    QApplication a(argc, argv);
	QApplication::addLibraryPath("./plugins");
    LBD_VideoMeeting_Meeting w;
	char* hwnd = "testmainframe";
	QString sip = "192.168.110.122";
	int port = 3334;
	QString classname = "高一三班";
	QString currentUser = "{李文轩轩}{12}{:/new/prefix1/3.png}";
	QString invitedusers = "{xx}{2}{:/new/prefix1/3.png}|{3}{3}{3}|{4}{4}{4}";
	QString userinfo = "{轩轩}{xx}{:/new/prefix1/3.png}|{xx}{2}{:/new/prefix1/3.png}|{hh}{3}{./images/1.png}|{zz}{4}{4}|{asd}{5}{5}|{嗯嗯}{6}{6}|{7}{7}{7}|{8}{8}{8}|{9}{9}{9}|{10}{10}{10}|{11}{11}{11}|{12}{12}{12}";
	//学生端入口
	w.Start(hwnd,QString_2char(sip),port ,QString_2char(currentUser), QString_2char(classname), QString_2char(invitedusers), QString_2char(userinfo));
		//教师端入口
	//w.Start(hwnd, QString_2chdar(sip), port,QString_2char(classname), QString_2char(invitedusers), QString_2char(userinfo));

	w.show();
		return a.exec();
	qDebug() << "Wrong agrc";
	return 0;
   
}
