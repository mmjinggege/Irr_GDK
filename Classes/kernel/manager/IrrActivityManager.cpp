#include "IrrActivityManager.h"
#include "IrrMarcos.h"
#include "IrrPattern.h"
#include "IrrMemoCacheManager.h"
#include "IrrCommon.h"

namespace irr_manager
{
	using namespace irr_core;

	IrrActivityManager::IrrActivityManager( void )
	{
		m_iActivityID = INVALIDATE;
	}

	IrrActivityManager::~IrrActivityManager( void )
	{
	}


	irr_core::IrrActivity* IrrActivityManager::getActivityByID( int activityID )
	{
		return (irr_core::IrrActivity*)IrrMemoCacheMgr->getIrrObjectByID(IRR_ACTIVITY,activityID);
	}

	void IrrActivityManager::addActivity( irr_core::IrrActivity* activity )
	{
		IrrMemoCacheMgr->pushMemoCache(IRR_ACTIVITY,activity);
	}

	void IrrActivityManager::removeActivity( int activityID )
	{
		IrrMemoCacheMgr->popMemoCache(IRR_ACTIVITY,activityID);
	}


	void IrrActivityManager::clearAll()
	{
		IrrMemoCacheMgr->clearIrrObjListByType(IRR_ACTIVITY);
	}

	void IrrActivityManager::startActivity( int activityID )
	{
		this->startActivity(activityID,false);
	}
	

	void IrrActivityManager::startActivity( int activityID,bool isClearUp /*= true*/ )
	{
		if(isClearUp && m_iActivityID != INVALIDATE)
		{
			this->finishActivity(m_iActivityID);
		}
		IrrActivity* activity = getActivityByID(activityID);
		if(activity)
		{
			m_iActivityID = activityID;
			activity->onCreate();
		}
	}

	void IrrActivityManager::finishActivity( int activityID )
	{
		IrrActivity* activity = getActivityByID(activityID);
		if(activity)
		{
			activity->onFinish();
		}
	}

	void IrrActivityManager::pendingActivity( int activityID )
	{
		IrrActivity* activity = getActivityByID(activityID);
		if(activity)
		{
			activity->onPending();
		}
	}
}