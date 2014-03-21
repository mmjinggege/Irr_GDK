#ifndef _IRRITENT_H_
#define _IRRITENT_H_

#include "IrrTypeDef.h"
#include "IrrObject.h"

namespace irr_core
{
	
	
	class IrrObject;
	class IrrBundle;
	//////////////////////////////////////////////////////////////////////////
	//IrrIntent
	class IrrIntent
	{
	public:
		IrrIntent(void);
		IrrIntent(irr_IntentAction action);
		IrrIntent(const IrrIntent& other);
		IrrIntent(irr_IntentAction action,int targetId,int ServiceID);
		IrrIntent(irr_IntentAction action,IrrObject* obj);
 		IrrIntent(irr_IntentAction action,int targetId,int ServiceID,IrrObject* obj);
 		IrrIntent(irr_IntentAction action,int targetId,int ServiceID,IrrBundle* bundle);
		IrrIntent& operator=(IrrIntent& other);
		virtual ~IrrIntent(void);

		CREATE_PROPERTY(int,m_iTargetID,TargetID);
		CREATE_PROPERTY(irr_IntentAction,m_iAction,IntentAction);
 		CREATE_PROPERTY(int,m_iServiceID,ServiceID);
 		CREATE_PROPERTY(IrrObject*,m_TargetObject,TargetObj);
 		CREATE_PROPERTY(IrrBundle*,m_pBundle,Bundle);
	};
}

#endif	//_IRRITENT_H_