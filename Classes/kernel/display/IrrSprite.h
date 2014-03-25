#ifndef _IRRSPRITE_H_
#define _IRRSPRITE_H_

#include "IrrNode.h"

namespace irr_display
{	

	class IrrSprite : public IrrNode
	{
	public:
		static IrrSprite* create(const char* texture,bool isPlist = false);
	public:
		IrrSprite(void);
		~IrrSprite(void);
	protected:
		virtual bool init(const char* texture,bool isPlist = false);
	};
}

#endif	//_IRRSPRITE_H_