#ifndef _IRRMEMOCACHEMANAGER_H_
#define _IRRMEMOCACHEMANAGER_H_

#include "IrrSingleton.h"
#include "IrrTypeDef.h"
#include "IrrCommon.h"

namespace irr_core
{
	class IrrObject;
}

namespace irr_manager
{
	typedef std::map<int,irr_core::IrrObject*> IrrObjMap;
	typedef std::map<Irr_ObjType,IrrObjMap> IrrMemoCache;

	typedef IrrMemoCache::iterator pIrrMemoCacheItor;
	
	//////////////////////////////////////////////////////////////////////////
	//IrrMemoCacheManager
	class IrrMemoCacheManager : public irr_base::IrrSingleton<IrrMemoCacheManager>
	{
	public:
		void pushMemoCache(Irr_ObjType irrObjType,irr_core::IrrObject* object);
		void popMemoCache(Irr_ObjType irrObjType,int targetID);
		irr_core::IrrObject* getIrrObjectByID(Irr_ObjType objType,int objectID);
		IrrObjMap* getIrrObjectList(Irr_ObjType irrObjType);
		void clearIrrObjListByType(Irr_ObjType irrType);
		void clearAll();
	protected:
		void __insertMemoCache__(Irr_ObjType irrObjType,irr_core::IrrObject* object);
		void __removeMemoCache__(Irr_ObjType irrObjType,int targetID);
	private:
		friend class irr_base::IrrSingleton<IrrMemoCacheManager>;
		IrrMemoCacheManager(void);
		~IrrMemoCacheManager(void);
	private:
		IrrMemoCache mIrrObjMemoCache;
	};
}

#define IrrMemoCacheMgr IrrMemoCacheManager::getInstance()

#endif	//_IRRMEMOCACHEMANAGER_H_