#ifndef _IRRIMAGE_H_
#define _IRRIMAGE_H_

#include "IrrWidget.h"

namespace irr_ui
{

	class IrrImage : public IrrWidget
	{
	public:
		static IrrImage* create(const char* texture,bool isPlist = false);
	public:
		IrrImage(void);
		~IrrImage(void);
	protected:		
		virtual bool init(const char* texture,bool isPlist = false);
	};
}

#endif	//_IRRIMAGE_H_