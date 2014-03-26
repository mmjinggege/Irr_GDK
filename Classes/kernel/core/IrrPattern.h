#ifndef _IRRPATTERN_H_
#define _IRRPATTERN_H_

#include "IrrObject.h"
#include "IrrCommon.h"
#include "IrrNetMsgSubject.h"

namespace irr_core
{
	
	class IrrBundle;
	//////////////////////////////////////////////////////////////////////////
	//IrrResponse
	class IrrResponse : public IrrObject
	{
	public:
		IrrResponse(void)
			:m_pTarget(NULL),
			m_pBundle(NULL),
			m_eRespCode(RESPONSE_UNKOWN)
		{}
		~IrrResponse(void)
		{}
		CREATE_PROPERTY(int,m_eRespCode,RespCode);
		CREATE_PROPERTY(IrrObject*,m_pTarget,RespTarget);
		CREATE_PROPERTY(IrrBundle*,m_pBundle,Bundle);
	};
}


namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrItent
	class IrrIntent
	{
	public:
		IrrIntent(void);
		IrrIntent(const IrrIntent& other);
		IrrIntent(irr_IntentAction action);
		IrrIntent(irr_IntentAction action,int targetId,int ServiceID);
		IrrIntent(irr_IntentAction action,IrrObject* obj);
		IrrIntent(irr_IntentAction action,int targetId,int ServiceID,IrrObject* obj);
		IrrIntent(irr_IntentAction action,int targetId,int ServiceID,IrrBundle* bundle);
		IrrIntent& operator=(IrrIntent& other);
		virtual ~IrrIntent(void);

		CREATE_PROPERTY(int,m_iTargetID,TargetID);
		CREATE_PROPERTY(irr_IntentAction,m_iAction,IntentAction);
		CREATE_PROPERTY(int,m_iServiceID,ServiceID);
		CREATE_PROPERTY(IrrObject*,m_pTargetObject,TargetObj);
		CREATE_PROPERTY(IrrBundle*,m_pBundle,Bundle);
	};
}

namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrCommand
	class IrrCommand : public IrrObject
	{
	public:
		IrrCommand(void);
		~IrrCommand(void);
		virtual void Execute(void* data) = 0;
	};

}


namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrNetObserver
	class IrrNetObserver : public IrrObject,public irr_net::INetMsgObserver
	{
	public:
		IrrNetObserver(void);
		virtual~IrrNetObserver(void);
		virtual void registerCommander(IrrCommand* commander);
		virtual void unRegisterCommander(IrrCommand* commander);
		virtual void unRegisterCommander(int commandID);
		virtual void ExecuteCommander(int commanderID,void* data);
		virtual void onUpdate(void* pMsgHead);
	};
}


namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrActivity
	class IrrActivity : public IrrObject
	{
	public:
		IrrActivity(void);
		virtual ~IrrActivity(void);

		virtual void onCreate();
		virtual void onFinish();
		virtual void onPending();
		virtual void startActivity(IrrIntent* intent);
		virtual void startActivity(int activityId);
		virtual IrrNetObserver* getNetObserverByID(int observerID);
		virtual void loadGUI(IrrBundle* bundle);
		
		CREATE_PROPERTY_BY_BOOL(m_bisActive,Active);
		CREATE_PROPERTY(int,m_pNetObserverID,NetObserverID);
	};
	//////////////////////////////////////////////////////////////////////////
}

#endif	//_IRRPATTERN_H_