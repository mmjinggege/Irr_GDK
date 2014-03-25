#ifndef _IRRTOGGLEBUTTON_H_
#define _IRRTOGGLEBUTTON_H_

#include "IrrContainer.h"
#include "IrrTypeDef.h"

namespace irr_ui
{

	class IrrToggleButton;

	typedef std::vector<IrrToggleButton*> IrrToggleButtonVec;
	typedef IrrToggleButtonVec::iterator pIrrToggleButtonItor;

	class IrrImage;

	class IrrToggleButton : public IrrContainer
	{
	public:
		static IrrToggleButtonVec ToggleButtonVec;
		static IrrToggleButton* create(const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist = false);
		static void addToggleButton(IrrToggleButton* button,int idx);
		static void clearToggleButton(IrrToggleButton* button);
		static void clearToggleButtonList();
	public:
		IrrToggleButton(void);
		~IrrToggleButton(void);

		void setToggleButtonStatue();
		void setGroupName(const char* group);
		IrrString& getGroupName();
		void setIdx(int index);
		int getIdx() const;

		virtual void setSelected(bool selected);
		bool isSelected() const;
		//////////////////////////////////////////////////////////////////////////
		void handleDown(IrrUIEvent& event);
		void handleUp(IrrUIEvent& event);
		void handleClick(IrrUIEvent& event);

		void addClickEvent(CCObject* target,Irr_GUI_SEL_ClickToggleEvent selector);
		//////////////////////////////////////////////////////////////////////////
	private:
		bool init(const char* normalTexture,const char* selectTexture,bool isPlist = false);
	protected:
		bool m_bIsSelected;
		IrrString m_GroupName;
		CCObject* m_pEventTarget;
		int m_iCellIdx;
		Irr_GUI_SEL_ClickToggleEvent m_pClickSelector;
		IrrImage* m_pNormalImage;
		IrrImage* m_pSelectedImage;

	};
}


#endif	//_IRRTOGGLEBUTTON_H_