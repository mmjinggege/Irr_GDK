#ifndef _IRRACTIVEMANAGER_H_
#define _IRRACTIVEMANAGER_H_

#include "IrrSingleton.h"
#include "IrrTypeDef.h"

namespace irr_core
{
	class IrrActivity;
};


namespace irr_manager
{
	//////////////////////////////////////////////////////////////////////////
	class IrrActivityManager : public irr_base::IrrSingleton<IrrActivityManager>
	{
	public:
		irr_core::IrrActivity* getActivityByID(int activityID);
		void addActivity(irr_core::IrrActivity* activity);
		void removeActivity(int activityID);
		void clearAll();
		void startActivity(int activityID);
		void startActivity(int activityID,bool isClearUp = true);
		void finishActivity(int activityID);
		void pendingActivity(int activityID);
	private:
		friend class irr_base::IrrSingleton<IrrActivityManager>;
		IrrActivityManager(void);
		~IrrActivityManager(void);
	private:
		int m_iActivityID;
	};
}

#endif	//_IRRACTIVEMANAGER_H_