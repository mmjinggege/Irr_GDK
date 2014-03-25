#include "IrrTabControl.h"
#include "IrrToggleButton.h"
#include "IrrPanel.h"

namespace irr_ui
{


	IrrTabControl::IrrTabControl( void )
	{
		m_pSelectButton = NULL;
	}

	IrrTabControl::~IrrTabControl( void )
	{
		removeAllChildrenWithCleanup(true);
		m_pEventTarget = NULL;
		m_pClickSelector = NULL;
	}
	

	void IrrTabControl::addTab( IrrToggleButton* button,int idx,CCObject* sender,Irr_GUI_SEL_ClickToggleEvent selector )
	{
		if(button)
		{
			m_ButtonVec.push_back(button);
			button->setIdx(idx);
			button->setPosition(m_ButtonVec.size() * button->getRect().size.width, 0);
			button->addClickEvent(sender,selector);
			this->addWidget(button);
		}
	}

	void IrrTabControl::selectButton( IrrToggleButton* button )
	{
		if(m_pSelectButton != NULL)
		{
			m_pSelectButton->setSelected(false);
		}
		m_pSelectButton = button;
		m_pSelectButton->setSelected(true);
	}

	IrrToggleButton* IrrTabControl::getSelectButton()
	{
		return m_pSelectButton;
	}
}