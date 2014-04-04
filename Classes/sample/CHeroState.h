#ifndef _CHEROSTATE_H_
#define _CHEROSTATE_H_

#include "IrrFSM.h"

using namespace irr_core;

typedef enum _heroState_
{
	STATE_IDEL = 1 << 1,
	STATE_ATTACK = 1 << 2,
	STATE_HURT = 1 << 3,
	STATE_SKILL = 1 << 4 ,
	STATE_WALKING = 1 << 5,
	STATE_ENGAGEING = 1 << 6
} EmHeroState;


struct CHeroData
{
	int m_uID;
	int m_uLevel;
	CHeroData()
	{
		m_uID = 0;
		m_uLevel = 0;
	}
};


class CHeroItem : public IrrFSMState
{
public:
	CHeroItem(void);
	~CHeroItem(void);

	virtual void beginState(int state);
	virtual void updateState(int state); 
	virtual void endState(int state);  

	virtual void updateFSM( float delta_time );

private:
	CHeroData data;
};


class CHeroAttackAction : public IrrFSMAction
{
public:
	CHeroAttackAction(void);
	~CHeroAttackAction(void);
	virtual void Execute(void* data1,void* data2);
};

#endif	//_CHEROSTATE_H_