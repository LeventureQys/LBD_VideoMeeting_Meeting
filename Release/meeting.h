#pragma once

//����mediasoupserver��ַ
void __stdcall SetMediasoupServerAddress(char *sserver,int iport);


//������Ƶ�Ƿ���������
void __stdcall SetVideoFullStretch(bool bflag);


//���òɼ��ź�Դ(baudio:��Ƶ��bcamera������ͷ��bdesktop����������)
//ע�⣺bcamera��bdesktopΪ���⣬����ͬʱΪtrue
void _stdcall SetSignalSource(bool baudio,bool bcamera,bool bdesktop);


//sroom����������
//sperson���λ���Ա��Ϣ{����}{seat01}{1230(���ھ��)}{1(1:���� 0:�Ǳ���)}|{����}{seat02}{1231}{0}
void  __stdcall  JoinMeeting(char *sroom, char *sperson);

//�˳���Ƶ����
void __stdcall  ExitMeeting();

//����״̬�ص�����
//1�����ӷ�����
//2�����ӷ�����ʧ��
//3�����ӷ������ɹ�
//4���Զ��������ӷ�����
//5�����ӶϿ�
typedef void(*pCallBack)(int isate);//����һ������ָ�룬����ý���˳�ʱ ���øûص�����
void _stdcall  NetStateCallback(pCallBack p);

//�����λ���Ա
void  __stdcall  InserPerson(char *sperson);
