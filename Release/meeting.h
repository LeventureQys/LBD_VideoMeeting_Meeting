#pragma once

//设置mediasoupserver地址
void __stdcall SetMediasoupServerAddress(char *sserver,int iport);


//设置视频是否铺满窗口
void __stdcall SetVideoFullStretch(bool bflag);


//设置采集信号源(baudio:音频，bcamera：摄像头，bdesktop：电脑桌面)
//注意：bcamera和bdesktop为互斥，不能同时为true
void _stdcall SetSignalSource(bool baudio,bool bcamera,bool bdesktop);


//sroom：房间名称
//sperson：参会人员信息{张三}{seat01}{1230(窗口句柄)}{1(1:本人 0:非本人)}|{张三}{seat02}{1231}{0}
void  __stdcall  JoinMeeting(char *sroom, char *sperson);

//退出视频会议
void __stdcall  ExitMeeting();

//网络状态回调函数
//1：连接服务器
//2：连接服务器失败
//3：链接服务器成功
//4：自动重新链接服务器
//5：连接断开
typedef void(*pCallBack)(int isate);//定义一个函数指针，当多媒体退出时 调用该回调函数
void _stdcall  NetStateCallback(pCallBack p);

//新增参会人员
void  __stdcall  InserPerson(char *sperson);
