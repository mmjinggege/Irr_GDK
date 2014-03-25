#ifndef _IRRPANEL_H_
#define _IRRPANEL_H_

#include "IrrContainer.h"

namespace irr_ui
{
	class IrrPanel : public IrrContainer
	{
	public:
		static IrrPanel* create(const char* texture,IrrSize size,bool isPlist = false);
	public:
		IrrPanel(void);
		virtual ~IrrPanel(void);
	protected:
		bool init(const char* texture,IrrSize size,bool isPlist = false);
	};
}

#endif	//_IRRPANEL_H_