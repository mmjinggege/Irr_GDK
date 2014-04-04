#ifndef _IRRFSM_H_
#define _IRRFSM_H_

#include "IrrMarcos.h"
#include "IrrTypeDef.h"
#include "IrrStateEvent.h"

using namespace irr_event;

namespace irr_core
{

	class IrrFSMAction
	{
	public:
		virtual void Execute(void* data1,void* data2) = 0;
	};	
	
	class IrrFSMCondition
	{
	public:
		virtual bool checkCondition(void* data1,void* data2) = 0;
	};
	
	typedef std::list<IrrFSMAction*> FSMActionList;

	class IrrFSMachine;
	

	class IrrFSMState
	{  
	public:
		friend class IrrFSMachine;
	public:  
		IrrFSMState();
		virtual ~IrrFSMState();

		virtual void beginState(int state) = 0;
		virtual void updateState(int state) = 0; 
		virtual void endState(int state) = 0;  
		void setState( int state ) ;
		virtual void updateFSM( float delta_time );
		float getTimeInCurState() { return m_fTimeInState; }  
		int getState() { return m_iState; }
		void setFSM(IrrFSMachine* fsm);	
	protected:
		float m_fTimeInState;  
		int m_iState;
		IrrFSMachine* m_pFSM;
	};  

	
	//////////////////////////////////////////////////////////////////////////
	typedef std::list<IrrFSMState*> FSMStateList;
	typedef FSMStateList::iterator pFSMStateListItor;

	typedef std::map<int,IrrFSMAction*> MAP_FMSAction;
	typedef MAP_FMSAction::iterator pFSMActionMapItor;


	class IrrFSMachine
	{
	public:
		IrrFSMachine(void);
		~IrrFSMachine(void);

		void addFSMState(IrrFSMState* state);
		void removeFSMState(IrrFSMState* state);
		void updateFSMState(int state,void* data1,void* data2);
		IrrFSMState* getCurrentState();
		
		void onTransState(int state,void* data1,void* data2);
		void addAction(int state,IrrFSMAction* condition);
		void removeAction(int state);
		IrrFSMAction* getActionByID(int state);
		void updateFSM(float dt);
		void dispatchStateEvent(IrrStateEvent& event);
	private:
		IrrFSMState*m_pCurFSMState;
		FSMStateList m_FSMStateList;
		MAP_FMSAction m_FSMActionMap;
	};
}

#endif	//_IRRFSM_H_