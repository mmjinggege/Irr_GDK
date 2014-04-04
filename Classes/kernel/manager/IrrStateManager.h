#ifndef _IRRSTATEMANAGER_H_
#define _IRRSTATEMANAGER_H_

#include "IrrSingleton.h"
#include "IrrTypeDef.h"

namespace irr_manager
{

	class IrrFSMachine;

	typedef std::map<int,IrrFSMachine*> MAP_PCSTFSMACHINE;
	
	class IrrStateMachineManager : public irr_base::IrrSingleton<IrrStateMachineManager>
	{
	public:	
		void clearFSMachineAll(void);
		void addFSMachine(int fsmID,IrrFSMachine* fsm);
		IrrFSMachine* getFSMachine(int fsmId);
	private:
		friend class irr_base::IrrSingleton<IrrStateMachineManager>;
		IrrStateMachineManager(void);
		~IrrStateMachineManager(void);

		MAP_PCSTFSMACHINE m_stateFSM;
	};
}

#endif	//_IRRSTATEMANAGER_H_