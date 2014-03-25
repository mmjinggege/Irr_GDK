#ifndef _IRRTABCONTROL_H_
#define _IRRTABCONTROL_H_

#include "IrrContainer.h"
#include "IrrTypeDef.h"

namespace irr_ui
{

	class IrrToggleButton;
	class IrrPanel;

	typedef std::vector<IrrToggleButton*> IrrToggleButtonVec;
	typedef IrrToggleButtonVec::iterator pIrrToggleButtonVecItor;


	class IrrTabControl : public IrrContainer
	{
	public:
		IrrTabControl(void);
		~IrrTabControl(void);

		void addTab(IrrToggleButton* button,int idx,CCObject* sender,Irr_GUI_SEL_ClickToggleEvent selector);
		void selectButton(IrrToggleButton* button);
		IrrToggleButton* getSelectButton();
	private:
		IrrToggleButtonVec m_ButtonVec;
		IrrToggleButton* m_pSelectButton;
		IrrPanel* m_Panel;
		CCObject* m_pEventTarget;
		Irr_GUI_SEL_ClickToggleEvent m_pClickSelector;
	};
}

#endif	//_IRRTABCONTROL_H_