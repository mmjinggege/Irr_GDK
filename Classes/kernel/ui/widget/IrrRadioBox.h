#ifndef _IRRRADIOBOX_H_
#define _IRRRADIOBOX_H_

#include "IrrToggleButton.h"

namespace irr_ui
{
	class IrrRadioBox : public IrrToggleButton
	{
	public:
		static IrrRadioBox* create(const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist = false);
	public:
		IrrRadioBox(void);
		~IrrRadioBox(void);

		void setSelected(bool selected);
	private:
		bool init(const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist = false);
	};
}

#endif	//_IRRRADIOBOX_H_