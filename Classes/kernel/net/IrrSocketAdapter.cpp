#include "IrrSocketAdapter.h"
#include "IrrNetMsgSubject.h"
#include "IrrSocket.h"

namespace irr_net
{
	IrrSocketAdapter::IrrSocketAdapter(void)
		:m_iSocketConnectEvent(NULL),
		m_nCurDataStreamLen(0),
		m_bReady(false),
		m_pSocket(NULL),
		m_nConnectServerFlag(0)
	{
		memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
	}


	IrrSocketAdapter::~IrrSocketAdapter(void)
	{
		if(NULL != m_pSocket)
		{
			closeSocket(false);
		}
	}

	//����
	bool IrrSocketAdapter::Connect(std::string szServerIP, int wPort)
	{
#if USE_NEW_SOCKET
		if(szServerIP.empty() || wPort<0)
			return false;
		if(m_pSocket == NULL)
			m_pSocket = new IrrSocket();
		if (!m_pSocket) 
			return false;
		if( !m_pSocket->Check())
		{
			if(m_pSocket->create(szServerIP.c_str(), wPort, 30)) 
			{
				this->m_bReady	=true;
				connectionSucceed();
				return true;
			}
			else
			{
				this->m_bReady	=false;
				connectionFailed();
				return false;
			}
		}
#else
		m_Socket.setCallBack(this);
		bool bFlag = m_Socket.connect(szServerIP.c_str(), wPort);
		return bFlag;
#endif
		return false;
	}

	//���ͺ���
	bool IrrSocketAdapter::sendData(char* buf, int nLen, bool bPushQueue /*= false*/)
	{
#if USE_NEW_SOCKET
		if(!m_bReady || !buf) {
			return false;
		}

		bool bSucSend;
		try {
			//bSucSend	=::ClientSocketSendMsg(pbufMsg, dwSize);
			if (m_pSocket) {
				bSucSend = m_pSocket->sendMsg(buf, nLen);
			}
		}
		catch(...)
		{
			//LogMsg("catch error in send msg.");		
		}
#else
		m_Socket.sendMessage(buf, nLen, bPushQueue);
#endif
		return true;
	}
	//�ر�����
	void IrrSocketAdapter::closeSocket(bool bNotify)
	{
		if(NULL != m_iSocketConnectEvent && bNotify)
		{
			m_iSocketConnectEvent->closeSocket();
		}

#if USE_NEW_SOCKET
		if (m_bReady && m_pSocket)
		{
			// ::ClientSocketDestroy();
			m_pSocket->Flush();
			m_pSocket->Destroy();
			m_bReady	=false;
		}

		delete m_pSocket;
		m_pSocket = NULL;
#else
		m_Socket.close();
#endif
	}

	void IrrSocketAdapter::addEventListener(ISocket* value)
	{
		m_iSocketConnectEvent = value;
	}


	void IrrSocketAdapter::pushStream2Buffer(const char* pStream, int nLen)
	{
		if(m_nCurDataStreamLen + nLen >= kDataStreamBufferLen)
		{
			//		CCLOG("<<<<<<<<<<<<<<<< ERROR: data stream buffer is full! >>>>>>>>>>>>>>>>>>");
			return;
		}

		memcpy(m_dataStreamBuffer+m_nCurDataStreamLen, pStream, nLen);
		m_nCurDataStreamLen += nLen;
	}

	void IrrSocketAdapter::popStreamFromBuffer(int nLen)
	{
		if(m_nCurDataStreamLen - nLen <= 0)
		{
			m_nCurDataStreamLen = 0;
			memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);

			//       CCLOG(">>>>>>>>>>>>>>>>>>>>>>>  ClientSocket::popStreamFromBuffer popBufLen:%d Message Buffer stream is null!", nLen);

			return;
		}

		int nResidueLen = m_nCurDataStreamLen - nLen;

		//   CCLOG(">>>>>>>>>>>>>>>>>>>>>>>  ClientSocket::popStreamFromBuffer curBufLen:%d popBufLen:%d residueBufLen:%d ",
		//          m_nCurDataStreamLen, nLen, nResidueLen);

		//#ifndef _UNUSE_MEMPOOL_
		//	char *pTmpBuf = static_cast<char*>(CMemPool::getInstance().GetMemory(nResidueLen));
		//#else
		char *pTmpBuf = new char[nResidueLen];
		//#endif

		memset(pTmpBuf, 0, nResidueLen);
		memcpy(pTmpBuf, m_dataStreamBuffer + nLen, nResidueLen);
		memset(m_dataStreamBuffer, 0, kDataStreamBufferLen);
		memcpy(m_dataStreamBuffer, pTmpBuf, nResidueLen);
		m_nCurDataStreamLen = nResidueLen;

		//	CMemPool::getInstance().FreeMemory(pTmpBuf, nResidueLen);
		if(NULL != pTmpBuf)
		{
			delete[] pTmpBuf;
			pTmpBuf = NULL;
		}
		//if(m_nCurDataStreamLen - nLen >= 0)
		//	m_nCurDataStreamLen -= nLen;
		//else
		//	m_nCurDataStreamLen = 0;
	}

	void IrrSocketAdapter::processNetMsg()
	{
#if USE_NEW_SOCKET
		if (!m_pSocket) {
			return;
		}

		if (!m_pSocket->Check()) {
			m_pSocket = NULL;
			// ������
			onConnectionAbort();
			return;
		}

		// �������ݣ��������������Ϣ��
		//m_pSocket->Flush();

		// �������ݣ�ȡ�û������е�������Ϣ��ֱ��������Ϊ�գ�
		while (true)
		{
			char buffer[_MAX_MSGSIZE] = { 0 };
			int nSize = sizeof(buffer);
			char* pbufMsg = buffer;
			if(m_pSocket == NULL)
			{
				break;
			}
			if (!m_pSocket->receiveMsg(pbufMsg, nSize)) {
				break;
			}

			while (true)
			{
				SeqMsgHead* pReceiveMsg = (SeqMsgHead*)(pbufMsg);
				UINT16	dwCurMsgSize = pReceiveMsg->usSize;
				//CCLOG("msgsize: %d  msgtype:%d", dwCurMsgSize,pReceiveMsg->usType);

				if((int)dwCurMsgSize > nSize || dwCurMsgSize <= 0) {	// broken msg
					break;
				}
				IrrNetMsgSubject::getInstance()->OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);
				//CMessageSubject::instance().OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);	
				pbufMsg	+= dwCurMsgSize;
				nSize	-= dwCurMsgSize;
				if(nSize <= 0)
				{
					break;
				}
			}
		}
#else
		//	while (true) {
		m_Socket.processNetMsg();

		if(m_nCurDataStreamLen <= 0)
			return;


		SeqMsgHead* pReceiveMsg = (SeqMsgHead*)(m_dataStreamBuffer);

		if(m_nCurDataStreamLen < pReceiveMsg->usSize)
			return;

		CMessageSubject::instance().OnMessage((const char*)pReceiveMsg, pReceiveMsg->usSize);
		popStreamFromBuffer(pReceiveMsg->usSize);
		//	}
#endif
	}

	//���ӳɹ�
	void IrrSocketAdapter::connectionSucceed()
	{
		if(NULL != m_iSocketConnectEvent)
		{
			m_iSocketConnectEvent->onHandlerConnected();
		}

	}
	//����ʧ��
	void IrrSocketAdapter::connectionFailed()
	{
		// CCMessageBox("���ӷ�����ʧ��!", "Error!");
		/*CLoginModule::getInstance().connectFaild();*/
		//LoginManager::getInstance().onConnectFaild();
		m_bReady = false;
		if(NULL != m_iSocketConnectEvent)
		{
			m_iSocketConnectEvent->onConnectFaild();
		}
	}
	//�յ���Ϣ
	void IrrSocketAdapter::reciveMessage(const char* lpMsgBuf, int nLen)
	{
		//MessageSubject::instance().OnMessage(lpMsgBuf, nLen);
		// CC_SAFE_DELETE(buf);

		//CCLOG("ClientSocket::reciveMessage dataStramSize:%d", nLen);

		pushStream2Buffer(lpMsgBuf, nLen);
	}
	//����ʧ��
	/*void GClientSocket::requestFailed(ERROR_RES errorRes)
	{

	}*/
	//Զ�����ӶϿ�
	void IrrSocketAdapter::onConnectionAbort()
	{
		std::string strMessageInfo = "������������ж�!";
		//CCMessageBox("������������ж�!", "ERROR!!");
		m_bReady = false;
		if(NULL != m_iSocketConnectEvent)
		{
			m_iSocketConnectEvent->onConnectionAbort();
		}
	}


	bool IrrSocketAdapter::getIsConnect()
	{
		return m_bReady;
	}

	bool IrrSocketAdapter::StopThread()
	{
		if (!m_pSocket) {
			return true;
		}
		if (!m_pSocket->Check()) {
			m_pSocket = NULL;
			// ������
			onConnectionAbort();
			return true;
		}
		return false;
	}
}



