#ifndef _IRRSOCKETADAPTER_H_
#define _IRRSOCKETADAPTER_H_

#include <string>

#define USE_NEW_SOCKET 1

namespace irr_net
{
	class IrrSocket;
	class ISocket;

	class IrrSocketAdapter
	{
		enum
		{
			kDataStreamBufferLen = 65536,
		};

	public:
		IrrSocketAdapter(void);
		~IrrSocketAdapter(void);

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
		IrrSocket* m_pSocket;
		bool			m_bReady;
		int				m_nConnectServerFlag;
	};
}



#endif //_IRRSOCKETADAPTER_H_