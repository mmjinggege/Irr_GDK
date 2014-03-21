#ifndef _IRRCONTROLL_H_
#define _IRRCONTROLL_H_

#include "IrrObject.h"

namespace irr_core
{
	//////////////////////////////////////////////////////////////////////////
	class IrrCommand : public IrrObject
	{
	public:
		IrrCommand(IrrObject* target);
		~IrrCommand(void);
		virtual void Execute() = 0;
	protected:
		IrrObject* m_pTarget;
	};
}

#endif	//_IRRCONTROLL_H_