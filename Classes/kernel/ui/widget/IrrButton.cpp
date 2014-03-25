#include "IrrButton.h"

namespace irr_ui
{
	
	IrrButton::IrrButton( void )
		:m_pNormalWidget(NULL),
		m_pSelectWidget(NULL),
		m_pDisableWidget(NULL),
		m_eButtonState(Button_State_Normal),
		m_pEventTarget(NULL),
		m_pClickSelector(NULL)
	{
	}

	IrrButton::~IrrButton( void )
	{
	}

	IrrButton* IrrButton::create( const char *normalImage /*= NULL*/, const char *selectedImage /*= NULL*/,bool isPlist /*= false*/ )
	{
		IrrButton* ret = new IrrButton();
		if(ret && ret->init(normalImage,selectedImage,isPlist))
		{
			ret->autorelease();
			return ret;
		}
		IRR_SAFE_DELETE(ret);
		return ret;
	}

	bool IrrButton::init( const char *normalImage /*= NULL*/, const char *selectedImage /*= NULL*/,bool isPlist /*= false*/ )
	{
		m_pNormalWidget = IrrWidget::create(normalImage,isPlist);
		m_pSelectWidget = IrrWidget::create(selectedImage,isPlist);

		if(m_pSelectWidget)
			addWidget(m_pSelectWidget);
		if(m_pNormalWidget)
			addWidget(m_pNormalWidget);
		
		setDimensions(m_pNormalWidget->getDimensions());
		m_pSelectWidget->setVisible(false);
		return true;
	}
	//////////////////////////////////////////////////////////////////////////
	void IrrButton::handleDown( IrrUIEvent& event )
	{
		if(m_bIsTouchable)
		{
			event.setHandled(true);
			setBtnState(Button_State_Click);
		}
	}

	void IrrButton::handleUp( IrrUIEvent& event )
	{
		if(m_bIsTouchable)
		{
			event.setHandled(true);
			setBtnState(Button_State_Normal);
		}
	}


	void IrrButton::handleClick( IrrUIEvent& event )
	{
		if(m_pEventTarget && m_pClickSelector)
		{
			(m_pEventTarget->*m_pClickSelector)(this);
		}
	}
	

	void IrrButton::setBtnState( Irr_ButtonState state )
	{
		if(m_pNormalWidget == NULL || m_pSelectWidget == NULL)
			return;
		m_eButtonState = state;
		if(Button_State_Normal == m_eButtonState)
		{
			m_pNormalWidget->setVisible(true);
			m_pSelectWidget->setVisible(false);
			if(m_pDisableWidget)
			{
				m_pDisableWidget->setVisible(false);
			}
		}
		else if(Button_State_Click == m_eButtonState)
		{
			m_pNormalWidget->setVisible(false);
			m_pSelectWidget->setVisible(true);
			if(m_pDisableWidget)
			{
				m_pDisableWidget->setVisible(false);
			}
		}
		else if(Button_State_Disable == m_eButtonState)
		{
			m_pNormalWidget->setVisible(false);
			m_pSelectWidget->setVisible(false);
			if (m_pDisableWidget)
			{
				m_pDisableWidget->setVisible(true);
			}	
		}
	}


	void IrrButton::setTouchable( bool var )
	{
		m_bIsTouchable = var;
		if ( m_pNormalWidget == NULL || m_pSelectWidget == NULL )
			return;
		if(!m_bIsTouchable)
		{
			if(m_pDisableWidget == NULL)
			{

			}
			else
			{

			}
		}
		this->setBtnState(m_bIsTouchable == false ? Button_State_Disable : Button_State_Normal);
	}

	void IrrButton::addClickEvent( CCObject* target,Irr_GUI_SEL_ClickEvent selector )
	{
		m_pEventTarget = target;
		m_pClickSelector = selector;
	}
	//////////////////////////////////////////////////////////////////////////
}