#include "IrrMessageNotifyManager.h"

namespace irr_manager
{

	IrrMessageNofityObserver::IrrMessageNofityObserver( IrrObject* target,Irr_CallFuncO selector,const char* name,IrrObject* object )
	{
		m_target = target;
		m_selector = selector;
		m_object = object;
		
		m_name = new char[strlen(name)+1];
		memset(m_name,0,strlen(name)+1);
		IrrString orgi(name);
		//orgi.copy(m_name,strlen(name),0);
		m_nHandler = 0;
	}


	IrrMessageNofityObserver::~IrrMessageNofityObserver( void )
	{
		IRR_SAFE_DELETE_ARRAY(m_name);
	}

	void IrrMessageNofityObserver::performSelector( IrrObject *obj )
	{
		if(m_target)
		{
			if(obj)
			{
				(m_target->*m_selector)(obj);
			}
			else
			{
				(m_target->*m_selector)(m_object);
			}
		}
	}

	
	//////////////////////////////////////////////////////////////////////////
	IrrMessageNotifyManager::IrrMessageNotifyManager( void )
	{

	}

	IrrMessageNotifyManager::~IrrMessageNotifyManager( void )
	{

	}

	void IrrMessageNotifyManager::addObserver( IrrObject* target,Irr_CallFuncO selector,const char* name,IrrObject* obj )
	{
		IrrMessageNofityObserver* observer = new IrrMessageNofityObserver(target,selector,name,obj);
		if (!observer)
			return;
		m_Observers.push_back(observer);
	}

	void IrrMessageNotifyManager::removeObserver( IrrObject *target,const char *name )
	{
		IrrNofityObserverList::iterator pItor;
		IrrMessageNofityObserver* observer = NULL;
		for (pItor = m_Observers.begin();pItor!=m_Observers.end();pItor++)
		{
			observer = *pItor;
			if (!strcmp(observer->getName(),name) && observer->getTarget() == target)
			{
				m_Observers.erase(pItor);
				return;
			}
		}
	}

	int IrrMessageNotifyManager::removeAllObservers( IrrObject *target )
	{
		int size = 0;
		IrrNofityObserverList::iterator pItor = m_Observers.begin();
		IrrMessageNofityObserver* observer = NULL;
		while(pItor!=m_Observers.end())
		{
			if (observer->getTarget() == target)
			{
				m_Observers.erase(pItor++);
				size++;
			}
			else
			{
				pItor++;
			}
		}
		m_Observers.clear();
		return size;
	}

	void IrrMessageNotifyManager::postMessageNotification( const char* name )
	{
		 this->postMessageNotification(name,NULL);
	}

	void IrrMessageNotifyManager::postMessageNotification( const char *name, IrrObject *object )
	{
		IrrNofityObserverList::iterator pItor;
		IrrMessageNofityObserver* observer = NULL;
		for (pItor = m_Observers.begin();pItor!=m_Observers.end();pItor++)
		{
			observer = *pItor;
			if ((!strcmp(observer->getName(),name)) && (observer->getObject() == object || observer->getObject() == NULL || object == NULL))
			{
				if(observer->getHandler() == 0)
				{
					observer->performSelector(object);
				}
			}
		}
	}

	bool IrrMessageNotifyManager::observerExisted( const char *name, IrrObject *object )
	{
		IrrNofityObserverList::iterator pItor;
		IrrMessageNofityObserver* observer = NULL;
		for (pItor = m_Observers.begin();pItor!=m_Observers.end();pItor++)
		{
			observer = *pItor;
			if (!strcmp(observer->getName(),name) && observer->getObject() == object)
			{
				return true;
			}
		}
		return false;
	}


}