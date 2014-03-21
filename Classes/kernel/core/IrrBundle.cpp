#include "IrrBundle.h"
#include "IrrJsonUtils.h"

using namespace irr_utils;

namespace irr_core
{
	
	IrrBundle::IrrBundle( void )
	{
	}

	IrrBundle::IrrBundle( const char* jsonStr )
	{
		CSJson::Reader jRead;
		jRead.parse(jsonStr,root);
	}

	IrrBundle::IrrBundle( const IrrString& jsonStr )
	{
		CSJson::Reader jRead;
		jRead.parse(jsonStr.c_str(),root);
	}


	IrrBundle::~IrrBundle( void )
	{
	}

	void IrrBundle::addJsonValue( const char* key,int val )
	{
		root[key] = CSJson::Value(val);
	}

	void IrrBundle::addJsonValue( const char* key,IrrUint val )
	{
		root[key] = CSJson::Value(val);
	}

	void IrrBundle::addJsonValue( const char* key,float val )
	{
		root[key] = CSJson::Value(val);
	}

	void IrrBundle::addJsonValue( const char* key,bool val )
	{
		root[key] = CSJson::Value(val);
	}

	void IrrBundle::addJsonValue( const char* key,const char* val )
	{
		root[key] = CSJson::Value(val);
	}

	int IrrBundle::getJsonInt( const char* tag )
	{
		return IrrJsonUtils::getJsonInt(root,tag);
	}

	bool IrrBundle::getJsonBool( const char* tag )
	{
		return IrrJsonUtils::getJsonBoolean(root,tag);
	}

	IrrString IrrBundle::getJsonString( const char* tag )
	{
		return IrrJsonUtils::getJsonString(root,tag);
	}

	IrrUint IrrBundle::getJsonUint( const char* tag )
	{
		return IrrJsonUtils::getJsonUInt(root,tag);
	}

	float IrrBundle::getJsonFloat( const char* tag )
	{
		return IrrJsonUtils::getJsonFloat(root,tag);
	}

	bool IrrBundle::isEmpty()
	{
		return root.isNull();
	}
}