#ifndef _IRRJSONUTILS_H_
#define _IRRJSONUTILS_H_

#include "json_lib.h"
#include "IrrTypeDef.h"

namespace irr_utils
{
	class IrrJsonUtils
	{
	public:
		static IrrInt getJsonInt(const CSJson::Value& json_object,const char* tag);
		static IrrUint getJsonUInt(const CSJson::Value& json_object,const char* tag);
		static IrrFloat getJsonFloat(const CSJson::Value& json_object,const char* tag);
		static IrrString getJsonString(const CSJson::Value& json_object,const char* tag);
		static IrrBool getJsonBoolean(const CSJson::Value& json_object,const char* tag,IrrBool _default = false);
		static IrrInt getJsonIntEx(const CSJson::Value& json_object,const char* tag);
	};
}

#endif	//_IRRJSONUTILS_H_