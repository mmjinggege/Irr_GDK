#ifndef _IRRKERNEL_H_
#define _IRRKERNEL_H_

#include "IrrSingleton.h"

namespace irr_core
{
	
	class IrrKernel : public irr_base::IrrSingleton<IrrKernel>
	{
	public:	
		void onLoop(float dt);
	private:
		friend class irr_base::IrrSingleton<IrrKernel>;
		IrrKernel(void);
		~IrrKernel(void);
	};
}

#endif	//_IRRKERNEL_H_