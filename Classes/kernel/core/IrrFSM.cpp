#include "IrrFSM.h"


namespace irr_core
{
	
	IrrFSMState::IrrFSMState()
		:m_iState(-1),
		m_fTimeInState(.0f),
		m_pFSM(NULL)
	{
	}

	IrrFSMState::~IrrFSMState()
	{
	}
	
	void IrrFSMState::setState( int state )
	{
		endState(m_iState);  
		m_iState = state;  
		m_fTimeInState = 0.0f;  
		beginState(m_iState);  
	}

	void IrrFSMState::updateFSM( float delta_time )
	{
		if( m_iState != -1 )  
		{  
			m_fTimeInState+=delta_time;  
			updateState(m_iState);  
		}  
	}

	void IrrFSMState::setFSM( IrrFSMachine* fsm )
	{
		m_pFSM = fsm;
	}
}


namespace irr_core
{

	IrrFSMachine::IrrFSMachine( void )
		:m_pCurFSMState(NULL)
	{

	}

	IrrFSMachine::~IrrFSMachine( void )
	{

	}

	void IrrFSMachine::addFSMState( IrrFSMState* state )
	{
		if(state)
		{
			m_FSMStateList.push_back(state);
		}
	}

	void IrrFSMachine::removeFSMState( IrrFSMState* state )
	{
		if(state == NULL)
			return;
		pFSMStateListItor itor;
		for (itor = m_FSMStateList.begin();itor !=m_FSMStateList.end();itor++)
		{
			if(*itor == state)
			{
				delete *itor;
				m_FSMStateList.erase(itor);
				break;
			}
		}
	}
	
	void IrrFSMachine::updateFSMState( int state,void* data1,void* data2 )
	{
		if(state != m_pCurFSMState->getState())
		{
			m_pCurFSMState->setState(state);
			onTransState(state,data1,data2);
		}
	}

	void IrrFSMachine::addAction(int state,IrrFSMAction* condition )
	{
		if(condition)
		{
			m_FSMActionMap.insert(std::make_pair<int,IrrFSMAction*>(state,condition));
		}
	}

	void IrrFSMachine::removeAction( int state )
	{
		if(state == INVALIDATE)
			return;
		pFSMActionMapItor itor = m_FSMActionMap.find(state);
		if(itor !=m_FSMActionMap.end())
		{
			delete itor->second;
			m_FSMActionMap.erase(itor);
		}
	}

	void IrrFSMachine::updateFSM( float dt )
	{
		if(m_pCurFSMState)
		{
			m_pCurFSMState->updateFSM(dt);
		}
	}
	
	IrrFSMAction* IrrFSMachine::getActionByID( int state )
	{
		if(state == INVALIDATE)
			return NULL;
		pFSMActionMapItor itor = m_FSMActionMap.find(state);
		if(itor != m_FSMActionMap.end())
			return itor->second;
		return NULL;
	}


	IrrFSMState* IrrFSMachine::getCurrentState()
	{
		return m_pCurFSMState;
	}

	void IrrFSMachine::onTransState( int state,void* data1,void* data2 )
	{

	}

	void IrrFSMachine::dispatchStateEvent( IrrStateEvent& event )
	{
		CCAssert(event.getCurState() == INVALIDATE,"State is Error!");
		int stateType = event.getStateType();
		IrrFSMAction* action = getActionByID(event.getCurState());
		if(action)
			action->Execute(event.getData1(),event.getData2());
// 		IrrFSMState* fsmState = (IrrFSMState*)event.getTargetState();
// 		switch(stateType)
// 		{
// 		case IRR_STATE_ENTER_STATE:
// 			{
// 				fsmState->updateState(event.getCurState());
// 				break;
// 			}
// 		case IRR_STATE_END_STATE:
// 			{
// 				break;
// 			}
// 		case IRR_STATE_NEXTSTATE:
// 			{
// 				break;
// 			}
// 		case IRR_STATE_UPDATESTATE:
// 			{
// 				break;
// 			}
// 		}
	}
}