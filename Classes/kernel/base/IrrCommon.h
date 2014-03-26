#ifndef _IRRCOMMON_H_
#define _IRRCOMMON_H_

#include "IrrEnumDef.h"

namespace irr_base
{
	//////////////////////////////////////////////////////////////////////////
	// 32λ��ǣ�ֵ �������
	class IrrFlagValue
	{
	public: 
		IrrFlagValue(unsigned int flag = 0);
		virtual void setBit(unsigned int value, bool bSet);
		virtual void reset(void);
		virtual bool isBitSet(unsigned int value);
	protected:
		unsigned int m_iFlag;//32 bit flag for state using
	};

	//////////////////////////////////////////////////////////////////////////
	// 32λ��ǣ�����λ �������
	class IrrFlagIndex : public IrrFlagValue
	{
	public:
		IrrFlagIndex(unsigned int flag = 0);
		~IrrFlagIndex(void);
		virtual void setBit(unsigned int index, bool bSet);
		virtual bool isBitSet(unsigned int index);
	};

}

#endif //_IRRCOMMON_H_