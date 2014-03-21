#ifndef _IRRBUNDLE_H_
#define _IRRBUNDLE_H_

#include "IrrObject.h"
#include "json_lib.h"

namespace irr_core
{

	class IrrBundle : public IrrObject
	{
	public:
		IrrBundle(void);
		IrrBundle(const char* jsonStr);
		IrrBundle(const IrrString& jsonStr);
		~IrrBundle(void);
		void addJsonValue(const char* key,int val);
		void addJsonValue(const char* key,IrrUint val);
		void addJsonValue(const char* key,float val);
		void addJsonValue(const char* key,bool val);
		void addJsonValue(const char* key,const char* val);

		int getJsonInt(const char* tag);
		bool getJsonBool(const char* tag);
		IrrString getJsonString(const char* tag);
		IrrUint getJsonUint(const char* tag);
		float getJsonFloat(const char* tag);

		bool isEmpty();
	private:
		CSJson::Value root;
	};
}

#endif	//_IRRBUNDLE_H_