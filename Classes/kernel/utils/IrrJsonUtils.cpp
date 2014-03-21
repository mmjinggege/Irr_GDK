#include "IrrJsonUtils.h"
#include "IrrStringUtils.h"

namespace irr_utils
{
	
	IrrInt IrrJsonUtils::getJsonInt( const CSJson::Value& json_object,const char* tag )
	{
		const CSJson::Value& value = json_object[tag];
		if(value.isNull() || !(value.isInt()) || value.isUInt())
			return 0;
		return value.asInt();
	}

	IrrUint IrrJsonUtils::getJsonUInt( const CSJson::Value& json_object,const char* tag )
	{
		const CSJson::Value& value = json_object[tag];
		if(value.isNull() || !(value.isInt()) || value.isUInt())
			return 0;
		return value.asUInt();
	}

	IrrFloat IrrJsonUtils::getJsonFloat( const CSJson::Value& json_object,const char* tag )
	{
		const CSJson::Value& value = json_object[tag];
		if(value.isNull())
			return 0.0f;
		return value.asDouble();
	}

	IrrString IrrJsonUtils::getJsonString( const CSJson::Value& json_object,const char* tag )
	{
		const CSJson::Value& value = json_object[tag];
		if(value.isNull() || !value.isString())
			return "";
		return value.asString();
	}


	IrrBool IrrJsonUtils::getJsonBoolean( const CSJson::Value& json_object,const char* tag,IrrBool _default /*= false*/ )
	{
		const CSJson::Value& value = json_object[tag];
		if(value.isNull() || !value.isBool())
			return _default;
		return value.asBool();
	}

	IrrInt IrrJsonUtils::getJsonIntEx( const CSJson::Value& json_object,const char* tag )
	{
		const CSJson::Value& value = json_object[tag];
		if(value.isNull())
			return 0;
		if(value.isInt() || value.isUInt())
			return value.asUInt();
		if(value.isString())
		{
			IrrInt nVal = IrrStringUtils::StringToInt((value.asString()).c_str());
			return nVal;
		}
		return 0;
	}
}