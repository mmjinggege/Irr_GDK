#ifndef _IRRBUTTON_H_
#define _IRRBUTTON_H_

#include "IrrContainer.h"

using namespace irr_display;

namespace irr_ui
{
	typedef enum __Button_State
	{
		Button_State_Normal = 0,
		Button_State_Click,
		Button_State_Disable,
	} Irr_ButtonState;

	//////////////////////////////////////////////////////////////////////////
	class IrrButton : public IrrContainer
	{
	public:
		static IrrButton* create(const char *normalImage  = NULL, const char *selectedImage  = NULL,bool isPlist = false);

	public:
		IrrButton(void);
		~IrrButton(void);

		void setBtnState(Irr_ButtonState state);

		void handleDown(IrrUIEvent& event);
		void handleUp(IrrUIEvent& event);
		void handleClick(IrrUIEvent& event);
		void addClickEvent(CCObject* target,Irr_GUI_SEL_ClickEvent selector);
		virtual void setTouchable(bool var);
	protected:
		bool init(const char *normalImage  = NULL, const char *selectedImage  = NULL,bool isPlist = false);
	private:
		IrrWidget* m_pNormalWidget;
		IrrWidget* m_pSelectWidget;
		IrrWidget* m_pDisableWidget;
		Irr_ButtonState m_eButtonState;

		CCObject* m_pEventTarget;
		Irr_GUI_SEL_ClickEvent m_pClickSelector;
	};
}

#endif	//_IRRBUTTON_H_