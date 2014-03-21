#include "IrrCodeTransUtils.h"
#include "iconv.h"

namespace irr_utils
{
	bool IrrCodeTransUtils::gb2312ToUTF8( IrrString strIn,IrrString& strOut )
	{
		bool ret = false;
		const char* pIn = strIn.c_str();
		int iBuffLengthIn = strIn.length();
		char* pOut = new char[iBuffLengthIn * 4];
		ret = IrrCodeTransUtils::gb2312TOUTF_8((char*)pIn,iBuffLengthIn,pOut,iBuffLengthIn * 4);
		strOut.assign(pOut);
		delete []pOut;
		return ret;
	}


	bool IrrCodeTransUtils::gb2312TOUTF_8( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("utf-8","gb2312",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::utf_8TOgb2312( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("gb2312","utf-16le",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::utf_8TOUTF_32( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("utf-8","UTF-32LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::utf_8TOUTF_16( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("utf-8","UTF-16LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::gb2312TOUTF_16( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("gb2312","utf-16le",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::gb2312TOUTF_32( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("gb2312","UTF-32LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::utf_16TOUTF_8( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("UTF-16LE","utf-8",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::utf_32TOUTF_8( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("UTF-32LE","utf-8",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}
	

	bool IrrCodeTransUtils::GBKTOUTF_16( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("GBK","UTF-16LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	bool IrrCodeTransUtils::GBKTOUTF_32( char* pStrIn,int inBufferLength,char* pOutBuffer,int outBufferLength )
	{
		bool ret = false;
		if (pStrIn && pOutBuffer)
		{
			ret = IrrCodeTransUtils::code_convert("GBK","UTF-32LE",pStrIn,inBufferLength,pOutBuffer,outBufferLength);
		}
		return ret;
	}

	
	bool IrrCodeTransUtils::code_convert( char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen )
	{
		bool ret  = false;
		iconv_t cd = 0;
		/*const */char *temp = inbuf;
		/*const */char **pin = &temp;
		char **pout = &outbuf;
		do 
		{
			cd = iconv_open(to_charset,from_charset);
			if (0 == cd)
			{
				break;
			}
			memset(outbuf,0,outlen);
			size_t tempInlength = inlen;
			size_t tempOutLength = outlen;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
			if(-1 == iconv(cd,/*(const char**)*/pin,&tempInlength,pout,&tempOutLength))
			{
				break;
			}
#else
#ifdef DEBUG
			if(-1 == iconv(cd,(const char**)pin,&tempInlength,pout,&tempOutLength))
			{
				break;
			}
#else
			if(-1 == iconv(cd,(char**)pin,&tempInlength,pout,&tempOutLength))
			{
				break;
			}
#endif
#endif

			iconv_close(cd);
			ret = true;
		} while (0);
		return ret;
	}

}