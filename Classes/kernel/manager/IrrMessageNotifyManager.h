#ifndef _IRRMESSAGENOTIFYMANAGER_H_
#define _IRRMESSAGENOTIFYMANAGER_H_

#include "IrrSingleton.h"
#include "IrrObject.h"

using namespace irr_core;
/* 
	@Desc消息通知中心
*/
namespace irr_manager
{
	//////////////////////////////////////////////////////////////////////////
	class IrrMessageNofityObserver : public IrrObject
	{
	public:
		IrrMessageNofityObserver(IrrObject* target,Irr_CallFuncO selector,const char* name,IrrObject* object);
		~IrrMessageNofityObserver(void);

		void performSelector(IrrObject *obj);

		CREATE_PROPERTY_READONLY(IrrObject *, m_target, Target);
		CREATE_PROPERTY_READONLY(Irr_CallFuncO, m_selector, Selector);
		CREATE_PROPERTY_READONLY(char *, m_name, Name);
		CREATE_PROPERTY_READONLY(IrrObject *, m_object, Object);
		CREATE_PROPERTY(int, m_nHandler,Handler);

	};

	typedef std::list<IrrMessageNofityObserver*> IrrNofityObserverList;
	
	//////////////////////////////////////////////////////////////////////////
	class IrrMessageNotifyManager : public irr_base::IrrSingleton<IrrMessageNotifyManager>
	{
	public:
		void addObserver(IrrObject* target,Irr_CallFuncO selector,const char* name,IrrObject* obj);
		void removeObserver(IrrObject *target,const char *name);
		int removeAllObservers(IrrObject *target);

		void postMessageNotification(const char* name);
		void postMessageNotification(const char *name, IrrObject *object);

	protected:
		bool observerExisted(const char *name, IrrObject *object);
	private:
		friend class irr_base::IrrSingleton<IrrMessageNotifyManager>;
		IrrMessageNotifyManager(void);
		~IrrMessageNotifyManager(void);

	private:
		IrrNofityObserverList m_Observers;
	};
}

#define IrrMessageNodityMgr IrrMessageNotifyManager::getInstance()

#endif	//_IRRMESSAGENOTIFYMANAGER_H_