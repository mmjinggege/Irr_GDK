#include "IrrCommon.h"

namespace irr_base
{
	
	IrrFlagValue::IrrFlagValue( unsigned int flag /*= 0*/ )
		:m_iFlag(flag)
	{
	}

	void IrrFlagValue::setBit( unsigned int value, bool bSet )
	{
		if (bSet)
		{
			m_iFlag |= value;
		}
		else
		{
			m_iFlag &= ~value;
		}
	}

	void IrrFlagValue::reset( void )
	{
		m_iFlag = 0;
	}

	bool IrrFlagValue::isBitSet( unsigned int value )
	{
		return (m_iFlag & value) != 0;
	}
}

namespace irr_base
{
	IrrFlagIndex::IrrFlagIndex( unsigned int flag /*= 0*/ )
		:IrrFlagValue(flag)
	{	
	}

	IrrFlagIndex::~IrrFlagIndex( void )
	{
	}

	void IrrFlagIndex::setBit( unsigned int index, bool bSet )
	{
		IrrFlagValue::setBit(bSet ? 1<<index : ~(1<<index), bSet);
	}

	bool IrrFlagIndex::isBitSet( unsigned int index )
	{
		return IrrFlagValue::isBitSet(1<<index);
	}
}