#ifndef _IRRCHECKBOX_H_
#define _IRRCHECKBOX_H_

#include "IrrToggleButton.h"

namespace irr_ui
{

	class IrrCheckBox : public IrrToggleButton
	{
	public:
		static IrrCheckBox* create(const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist = false);
	public:
		IrrCheckBox(void);
		~IrrCheckBox(void);
		void setSelected(bool selected);
	private:
		bool init(const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist = false);
	};
}

#endif	//_IRRCHECKBOX_H_