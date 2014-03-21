#ifndef _IRROBJECT_H_
#define _IRROBJECT_H_

#include "IrrTypeDef.h"
#include "IrrMarcos.h"

namespace irr_core
{
	
	//////////////////////////////////////////////////////////////////////////
	//IrrObject 对象基类
	class IrrObject
	{
	public:
		IrrObject(void){};
		virtual ~IrrObject(void) {}
		CREATE_PROPERTY(int,m_iObjectID,ObjectID);
		CREATE_PROPERTY(int,m_iObjType,ObjType);
	};


	typedef void (IrrObject::*Irr_CallFuncO)(IrrObject*);
	#define irr_callBack(_SELECTOR)  (Irr_CallFuncO)(&_SELECTOR)
}



#endif //_IRROBJECT_H_