#include "CHeroState.h"

//////////////////////////////////////////////////////////////////////////
CHeroAttackAction::CHeroAttackAction( void )
{

}

CHeroAttackAction::~CHeroAttackAction( void )
{

}

void CHeroAttackAction::Execute( void* data1,void* data2 )
{

}
//////////////////////////////////////////////////////////////////////////


CHeroItem::CHeroItem( void )
{
	m_iState = STATE_IDEL;
}

CHeroItem::~CHeroItem( void )
{
}


void CHeroItem::beginState( int state )
{
	m_iState = state;
	IrrStateEvent evt(IRR_STATE_ENTER_STATE,state,this,NULL,NULL);
	if(m_pFSM)
		m_pFSM->dispatchStateEvent(evt);
}


void CHeroItem::updateState( int state )
{
	IrrStateEvent evt(IRR_STATE_UPDATESTATE,state,this,NULL,NULL);
	if(m_pFSM)
		m_pFSM->dispatchStateEvent(evt);
}

void CHeroItem::endState( int state )
{
	IrrStateEvent evt(IRR_STATE_END_STATE,state,this,NULL,NULL);
	if(m_pFSM)
		m_pFSM->dispatchStateEvent(evt);
}


void CHeroItem::updateFSM( float delta_time )
{
	if(m_iState != INVALIDATE)
	{
		//todo
		
	}
}
