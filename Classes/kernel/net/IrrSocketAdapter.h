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

		//连接成功
		virtual void connectionSucceed();
		//连接失败
		virtual void connectionFailed();
		//收到信息
		virtual void reciveMessage(const char* lpMsgBuf, int nLen);
		//请求失败
		//virtual void requestFailed(ERROR_RES errorRes);
		//远程连接断开
		virtual void onConnectionAbort();

		//连接
		bool Connect(std::string szServerIP,  int wPort);
		//发送函数
		bool sendData(char* buf, int nLen, bool bPushQueue = false);
		//关闭连接
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

		//数据流缓冲
		char	m_dataStreamBuffer[kDataStreamBufferLen];
		//当前数据流长度
		int		m_nCurDataStreamLen;
	private:
		IrrSocket* m_pSocket;
		bool			m_bReady;
		int				m_nConnectServerFlag;
	};
}



#endif //_IRRSOCKETADAPTER_H_