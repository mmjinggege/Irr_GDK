#ifndef _IRRSOCKET_H_
#define _IRRSOCKET_H_

#ifdef WIN32
#include <WinSock2.h>
#else
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <netdb.h>
#endif

#define SOCKET int

#define SOCKET_TIMEOUT 30				//��ʱ
#define _MAX_MSGSIZE 16 * 1024		// �ݶ�һ����Ϣ���Ϊ16k
#define BLOCKSECONDS	30			// INIT��������ʱ��
#define INBUFSIZE	(64*1024)		//?	����ߴ�������汨�����  �������ݵĻ���

#define OUTBUFSIZE	(8*1024)		//? ����ߴ�������汨������� �������ݵĻ��棬��������8Kʱ��FLUSHֻ��ҪSENDһ 

#define MAX_RECV_BUFFERSIZE 65535

#pragma warning (disable: 4786)

#include <string>
#include <vector>
#include <map>
using namespace std;

#ifndef CHECKF
#define CHECKF(x) \
	do \
{ \
	if (!(x)) { \
	log_msg("CHECKF", #x, __FILE__, __LINE__); \
	return 0; \
	} \
} while (0)
#endif

#pragma comment(lib, "ws2_32.lib")

namespace irr_net
{
	/************************************************************************/
	/* 
		CSocket
	*/
	class IrrSocket
	{
	public:
		IrrSocket(void);
		~IrrSocket(void);
		bool	create(const char* pszServerIP, int nServerPort, int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
		bool	sendMsg(void* pBuf, int nSize);
		bool	receiveMsg(void* pBuf, int& nSize);
		bool	Flush(void);
		bool	Check(void);
		void	Destroy(void);
		SOCKET getSocket(void) const { return m_sockClient; }
	private:
		bool	  recvFromSock(void);			// �������ж�ȡ�����ܶ������
		bool    hasError();							// �Ƿ�������ע�⣬�첽ģʽδ��ɷǴ���
		void    closeSocket();

		SOCKET	m_sockClient;

		// �������ݻ���
		char	m_bufOutput[OUTBUFSIZE];		//? ���Ż�Ϊָ������
		int		m_nOutbufLen;

		// ���λ�����
		char	m_bufInput[INBUFSIZE];
		int		m_nInbufLen;
		int		m_nInbufStart;							// INBUFʹ��ѭ��ʽ���У��ñ���Ϊ������㣬0 - (SIZE-1)
	};
}


/************************************************************************/
#endif  //_IRRSOCKET_H_