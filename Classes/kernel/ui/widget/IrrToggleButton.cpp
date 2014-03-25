#include "IrrToggleButton.h"
#include "IrrImage.h"

namespace irr_ui
{

	IrrToggleButtonVec IrrToggleButton::ToggleButtonVec;	

	IrrToggleButton::IrrToggleButton( void )
		:m_pEventTarget(NULL),
		m_pClickSelector(NULL),
		m_bIsSelected(false)
	{

	}

	IrrToggleButton::~IrrToggleButton( void )
	{
		removeAllChildrenWithCleanup(true);
	}
	
	IrrToggleButton* IrrToggleButton::create( const char* normalTexture,const char* selectTexture,const char* groupName,bool isPlist /*= false*/ )
	{
		IrrToggleButton* ret = new IrrToggleButton();
		if(ret && ret->init(normalTexture,selectTexture,isPlist))
		{
			ret->setGroupName(groupName);
			ret->autorelease();
			return ret;
		}
		IRR_SAFE_DELETE(ret);
		return ret;
	}


	bool IrrToggleButton::init( const char* normalTexture,const char* selectTexture,bool isPlist /*= false*/ )
	{
		m_pNormalImage = IrrImage::create(normalTexture,isPlist);
		m_pSelectedImage = IrrImage::create(selectTexture,isPlist);

		if(m_pSelectedImage)
			addWidget(m_pSelectedImage);
		if(m_pNormalImage)
			addWidget(m_pNormalImage);

		setDimensions(m_pNormalImage->getDimensions());
		m_pSelectedImage->setVisible(false);
		return true;
	}

	
	void IrrToggleButton::addToggleButton( IrrToggleButton* button,int idx )
	{
		if(button)
		{
			ToggleButtonVec.push_back(button);
			button->setIdx(idx);
			button->setPosition(button->getRect().getOriginX() + (ToggleButtonVec.size() - 1 ) * button->getRect().size.width, button->getRect().getOriginY());
		}
	}


	void IrrToggleButton::setToggleButtonStatue()
	{
		m_bIsSelected = !m_bIsSelected;
		if(m_bIsSelected)
		{
			m_pNormalImage->setVisible(!m_bIsSelected);
			m_pSelectedImage->setVisible(m_bIsSelected);
		}
		else
		{
			m_pNormalImage->setVisible(m_bIsSelected);
			m_pSelectedImage->setVisible(!m_bIsSelected);
		}
	}

	void IrrToggleButton::setGroupName( const char* group )
	{
		m_GroupName = group;
	}

	IrrString& IrrToggleButton::getGroupName()
	{
		return m_GroupName;
	}

	void IrrToggleButton::handleDown( IrrUIEvent& event )
	{
		if(m_bIsTouchable)
		{
			event.setHandled(true);
			m_bIsSelected = true;
		}
	}

	void IrrToggleButton::handleUp( IrrUIEvent& event )
	{
		if(m_bIsTouchable)
		{
			event.setHandled(true);
			setToggleButtonStatue();
		}
	}

	void IrrToggleButton::handleClick( IrrUIEvent& event )
	{
		if(m_pEventTarget && m_pClickSelector)
		{
			(m_pEventTarget->*m_pClickSelector)(this,getIdx());
		}
	}

	void IrrToggleButton::addClickEvent( CCObject* target,Irr_GUI_SEL_ClickToggleEvent selector )
	{
		m_pEventTarget = target;
		m_pClickSelector = selector;
	}

	void IrrToggleButton::clearToggleButtonList()
	{
		pIrrToggleButtonItor pItor = ToggleButtonVec.begin();
		while(pItor != ToggleButtonVec.end())
		{
			(*pItor)->removeFromParentAndCleanup(true);
			ToggleButtonVec.erase(pItor++);
		}

	}

	void IrrToggleButton::setIdx( int index )
	{
		m_iCellIdx = index;
	}

	int IrrToggleButton::getIdx() const
	{
		return m_iCellIdx;
	}

	void IrrToggleButton::setSelected( bool selected )
	{
		m_bIsSelected = selected;
	}

	bool IrrToggleButton::isSelected() const
	{
		return m_bIsSelected;
	}
	

	void IrrToggleButton::clearToggleButton( IrrToggleButton* button )
	{
		pIrrToggleButtonItor pItor = ToggleButtonVec.begin();
		while(pItor != ToggleButtonVec.end())
		{
			if(button == *pItor && button->getGroupName() == (*pItor)->getGroupName())
			{
				button->setSelected(false);
			}
		}
	}
}