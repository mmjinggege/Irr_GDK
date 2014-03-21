#ifndef _CSOCKETADAPTER_H_
#define _CSOCKETADAPTER_H_

#include <string>

class CSocket;
class ISocket;

#define USE_NEW_SOCKET 1

class CSocketAdapter
{
	enum
	{
		kDataStreamBufferLen = 65536,
	};

public:
	CSocketAdapter(void);
	~CSocketAdapter(void);

	//���ӳɹ�
	virtual void connectionSucceed();
	//����ʧ��
	virtual void connectionFailed();
	//�յ���Ϣ
	virtual void reciveMessage(const char* lpMsgBuf, int nLen);
	//����ʧ��
	//virtual void requestFailed(ERROR_RES errorRes);
	//Զ�����ӶϿ�
	virtual void onConnectionAbort();

	//����
	bool Connect(std::string szServerIP,  int wPort);
	//���ͺ���
	bool sendData(char* buf, int nLen, bool bPushQueue = false);
	//�ر�����
	void closeSocket(bool bNotify = false);
	void addEventListener(ISocket* value);
	bool getIsConnect();

	void processNetMsg();
	bool StopThread();

private:
	void pushStream2Buffer(const char* pStream, int nLen);
	void popStreamFromBuffer(int nLen);
protected:
	ISocket* m_iSocketConnectEvent;

	//����������
	char	m_dataStreamBuffer[kDataStreamBufferLen];
	//��ǰ����������
	int		m_nCurDataStreamLen;
private:
	CSocket* m_pSocket;
	bool			m_bReady;
	int				m_nConnectServerFlag;
};


#endif //_CSOCKETADAPTER_H_