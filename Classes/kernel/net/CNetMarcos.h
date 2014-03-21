#ifndef _CNETMARCOS_H_
#define _CNETMARCOS_H_

class IMsgObserver
{
public:
	//��������֪ͨ
	virtual void onUpdate(void* pMsgHead) = 0;
};

class ISocket
{
public:
	// �ر����ӻص�
	virtual void closeSocket() = 0;	
	// ���ӳɹ��ص�
	virtual void onHandlerConnected() = 0;	
	//Զ�̶Ͽ�����
	virtual void onConnectionAbort() = 0;
	//����ʧ��
	virtual void onConnectFaild() = 0;
};

struct  MsgHead
{
	unsigned int usSize;
	unsigned int usType;
};

struct SeqMsgHead : public MsgHead
{
	unsigned __int64 UserId;		 //�û�ID
	int	    SeqId;						 //���к� C-G֮����
};

#endif //_BBNETMARCOS_H_