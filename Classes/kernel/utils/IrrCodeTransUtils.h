#ifndef _IRRCODETRANSUTILS_H_
#define _IRRCODETRANSUTILS_H_

#include "IrrTypeDef.h"

namespace irr_utils
{	

	class IrrCodeTransUtils
	{
	public:
		//////////////////////////////////////////////////////////////////////////
		static bool gb2312ToUTF8(IrrString strIn,IrrString& strOut);
		//////////////////////////////////////////////////////////////////////////
		static bool gb2312TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
		static bool utf_8TOgb2312(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);

		static bool utf_8TOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
		static bool utf_8TOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
			
		static bool gb2312TOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
		static bool gb2312TOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);

		static bool utf_16TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
		static bool utf_32TOUTF_8(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);

		static bool GBKTOUTF_16(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
		static bool GBKTOUTF_32(char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength);
	private:
		static bool code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen);
	};
}

#endif	//_IRRCODETRANSUTILS_H_