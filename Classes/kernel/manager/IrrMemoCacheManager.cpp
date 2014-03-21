#include "IrrMemoCacheManager.h"
#include "IrrObject.h"


namespace irr_manager
{
		
	IrrMemoCacheManager::IrrMemoCacheManager( void )
	{
	}

	IrrMemoCacheManager::~IrrMemoCacheManager( void )
	{
	}

	void IrrMemoCacheManager::pushMemoCache( Irr_ObjType irrObjType,irr_core::IrrObject* object )
	{
		__insertMemoCache__(irrObjType,object);
	}


	void IrrMemoCacheManager::popMemoCache( Irr_ObjType irrObjType,int targetID )
	{
		__removeMemoCache__(irrObjType,targetID);
	}

	void IrrMemoCacheManager::__insertMemoCache__( Irr_ObjType irrObjType,irr_core::IrrObject* object )
	{
		IRR_CHECK_NULL(object);
		pIrrMemoCacheItor pItor = mIrrObjMemoCache.find(irrObjType);
		if(pItor == mIrrObjMemoCache.end())
		{
			IrrObjMap objMap;
			objMap.insert(std::make_pair(object->getObjectID(),object));
			mIrrObjMemoCache.insert(std::make_pair(irrObjType,objMap));
		}
		else
		{
			IrrObjMap& objMap = pItor->second;
			IrrObjMap::iterator Itor = objMap.find(object->getObjectID());
			if(Itor == objMap.end())
				objMap.insert(std::make_pair(object->getObjectID(),object));
			else
				objMap[object->getObjectID()] = object;
		}
	}

	void IrrMemoCacheManager::__removeMemoCache__( Irr_ObjType irrObjType,int targetID )
	{
		pIrrMemoCacheItor pItor = mIrrObjMemoCache.find(irrObjType);
		if(pItor != mIrrObjMemoCache.end())
		{
			IrrObjMap& objMap = pItor->second;
			IrrObjMap::iterator Itor = objMap.find(targetID);
			if(Itor != objMap.end())
			{
				delete Itor->second;
				objMap.erase(Itor);
			}
		}
	}


	irr_core::IrrObject* IrrMemoCacheManager::getIrrObjectByID( Irr_ObjType objType,int objectID )
	{
		pIrrMemoCacheItor pItor = mIrrObjMemoCache.find(objType);
		if(pItor != mIrrObjMemoCache.end())
		{
			IrrObjMap& objMap = pItor->second;
			IrrObjMap::iterator Itor = objMap.find(objectID);
			if(Itor !=objMap.end())
			{
				return Itor->second;
			}
		}
		return NULL;
	}


	IrrObjMap* IrrMemoCacheManager::getIrrObjectList( Irr_ObjType irrObjType )
	{
		pIrrMemoCacheItor pItor = mIrrObjMemoCache.find(irrObjType);
		if(pItor!=mIrrObjMemoCache.end())
		{
			return &pItor->second;
		}
		return NULL;
	}


	void IrrMemoCacheManager::clearIrrObjListByType( Irr_ObjType irrType )
	{
		IrrObjMap* objList = getIrrObjectList( irrType );
		if(objList)
		{
			IrrObjMap::iterator pItor;
			while(pItor!=objList->end())
			{
				IRR_SAFE_DELETE(pItor->second);
				objList->erase(pItor++);
			}
			objList->clear();
		}
	}


	void IrrMemoCacheManager::clearAll()
	{
		pIrrMemoCacheItor pItor = mIrrObjMemoCache.begin();
		while(pItor!=mIrrObjMemoCache.end())
		{
			clearIrrObjListByType(pItor->first);
			mIrrObjMemoCache.erase(pItor++);
		}
	}
}