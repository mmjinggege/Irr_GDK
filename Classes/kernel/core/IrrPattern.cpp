#include "IrrPattern.h"
#include "IrrBundle.h"
#include "IrrCommon.h"
#include "IrrMemoCacheManager.h"

USING_IRR_MANAGER;

namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrIntent
	IrrIntent::IrrIntent( void )
		:m_iAction(irr_IntentAction::INTENT_UNKOWN),
		m_pBundle(NULL),
		m_pTargetObject(NULL),
		m_iTargetID(-1),
		m_iServiceID(-1)
	{
	}
		

	IrrIntent::IrrIntent( irr_IntentAction action )
	{
		m_iAction = action;
	}

	IrrIntent::IrrIntent( const IrrIntent& other )
	{
		m_pBundle = other.m_pBundle;
		m_iAction = other.m_iAction;
 		m_iServiceID = other.m_iServiceID;
 		m_iTargetID = other.m_iTargetID;
 		m_pTargetObject = other.m_pTargetObject;
	}

	IrrIntent::IrrIntent( irr_IntentAction action,int targetId,int ServiceID )
		:m_iAction(action),
		m_pTargetObject(NULL),
		m_iTargetID(targetId),
		m_iServiceID(ServiceID),
		m_pBundle(NULL)
	{
	}

	IrrIntent::IrrIntent( irr_IntentAction action,IrrObject* obj )
		:m_iAction(action),
		m_pTargetObject(obj),
		m_iTargetID(-1),
		m_iServiceID(-1),
		m_pBundle(NULL)
	{
	}

	IrrIntent::IrrIntent( irr_IntentAction action,int targetId,int ServiceID,IrrObject* obj )
		:m_iAction(action),
		m_iTargetID(targetId),
		m_iServiceID(ServiceID),
		m_pTargetObject(obj),
		m_pBundle(NULL)
	{
	}

	IrrIntent::IrrIntent( irr_IntentAction action,int targetId,int ServiceID,IrrBundle* bundle )
		:m_iAction(action),
		m_iTargetID(targetId),
		m_iServiceID(ServiceID),
		m_pTargetObject(NULL),
		m_pBundle(bundle)
	{
	}


	IrrIntent& IrrIntent::operator=( IrrIntent& other )
	{
		m_iAction = other.getIntentAction();
		m_iServiceID = other.getServiceID();
		m_iTargetID = other.getTargetID();
		m_pTargetObject = other.getTargetObj();
		m_pBundle = other.getBundle();
		return *this;
	}

	IrrIntent::~IrrIntent( void )
	{
		m_pTargetObject = NULL;
		m_pBundle = NULL;
	}
}

namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	IrrActivity::IrrActivity( void )
		:m_bisActive(false),
		m_pNetObserverID(INVALIDATE)
	{
		setObjType(Irr_ObjType::IRR_ACTIVITY);
	}

	IrrActivity::~IrrActivity( void )
	{

	}

	void IrrActivity::onCreate()
	{

	}


	void IrrActivity::onPending()
	{

	}


	void IrrActivity::onFinish()
	{

	}

	void IrrActivity::startActivity( IrrIntent* intent )
	{
		
	}

	void IrrActivity::startActivity( int activityId )
	{
		/*IrrIntent intent(INTENT_START_ACTIVITY,activityId);*/
	}

	void IrrActivity::loadGUI( IrrBundle* bundle )
	{
		/*IrrIntent intent(INTENT_LOAD_UI,getObjectID(),SERVICE_GUI,bundle);*/
	}

	IrrNetObserver* IrrActivity::getNetObserverByID( int observerID )
	{
		return (IrrNetObserver*)IrrMemoCacheMgr->getIrrObjectByID(IRR_NET_OBSERVER,observerID);
	}

}


namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	//IrrNetObserver
	IrrNetObserver::IrrNetObserver( void )
	{
	}

	IrrNetObserver::~IrrNetObserver( void )
	{
	}
	
	void IrrNetObserver::registerCommander( IrrCommand* commander )
	{
		IRR_CHECK_NULL(commander);
		IrrMemoCacheMgr->pushMemoCache(IRR_COMMAND,commander);
	}

	void IrrNetObserver::unRegisterCommander( IrrCommand* commander )
	{
		IRR_CHECK_NULL(commander);
		unRegisterCommander(commander->getObjectID());
	}

	void IrrNetObserver::unRegisterCommander( int commandID )
	{
		IrrMemoCacheMgr->popMemoCache(IRR_COMMAND,commandID);
	}

	
	void IrrNetObserver::ExecuteCommander( int commanderID,void* data )
	{
		IrrObjMap* commandList = IrrMemoCacheMgr->getIrrObjectList(IRR_COMMAND);
		IRR_CHECK_NULL(commandList);
		IrrObjMap::iterator pItor;
		IrrCommand* commander = NULL;
		for (pItor = commandList->begin();pItor!=commandList->end();pItor++)
		{
			commander = (IrrCommand*)pItor->second;
			if(commander->getObjectID() == commanderID)
			{
				commander->Execute(data);
				break;
			}
		}
	}

	void IrrNetObserver::onUpdate( void* pMsgHead )
	{
		;//TODO
	}
}