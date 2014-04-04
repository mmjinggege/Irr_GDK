#ifndef _IRRSTATEEVENT_H_
#define _IRRSTATEEVENT_H_

namespace irr_event
{
	typedef enum __IrrStateEvent
	{
		IRR_STATE_ENTER_STATE,
		IRR_STATE_END_STATE,
		IRR_STATE_NEXTSTATE,
		IRR_STATE_UPDATESTATE,
	} Irr_StateEvent;

	
	class IrrStateEvent
	{
	public:
		IrrStateEvent(int stateType,int curState,void* target,void* data1,void* data2)
			:m_icurState(-1),
			m_data1(NULL),
			m_data2(NULL),
			m_TargetState(target),
			m_iStateType(stateType)
		{}
		CREATE_PROPERTY(int,m_iStateType,StateType);
		CREATE_PROPERTY(int,m_icurState,CurState);
		CREATE_PROPERTY(void*,m_TargetState,TargetState);
		CREATE_PROPERTY(void*,m_data1,Data1);
		CREATE_PROPERTY(void*,m_data2,Data2);
	};
}

#endif	//_IRRSTATEEVENT_H_