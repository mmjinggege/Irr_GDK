#include "IrrContainer.h"

namespace irr_ui
{


	IrrContainer::IrrContainer( void )
		:m_pCurrentSelWidget(NULL)
	{

	}

	IrrContainer::~IrrContainer( void )
	{

	}

	void IrrContainer::addWidget( IrrWidget* widget)
	{
		IRR_CHECK_NULL(widget);
		m_Childrens.push_back(widget);
	}

	void IrrContainer::addWidget( IrrWidget* widget,IrrVector2D pos )
	{
		IRR_CHECK_NULL(widget);
		addWidget(widget);
		widget->setLocation(pos.X,pos.Y);
	}

	void IrrContainer::removeWidget( IrrWidget* widget,bool isDel /*= true*/ )
	{
		pIrrWidgetItor itor;
		for (itor = m_Childrens.begin();itor!=m_Childrens.end();itor++)
		{
			if(*itor == widget)
			{
				m_Childrens.erase(itor);
				if(isDel)
				{
					delete *itor;
				}
				else
				{
					(*itor)->setParent(NULL);
				}
				break;
			}
		}
	}

	void IrrContainer::clearAllWidget()
	{
		pIrrWidgetItor itor = m_Childrens.begin();
		while(itor!=m_Childrens.end())
		{
			itor = m_Childrens.erase(itor);
		}
	}

	void IrrContainer::swapWidget( IrrWidget* sour,IrrWidget* desc )
	{
		if(sour == NULL || desc == NULL)
		{
			return;
		}
// 		int sourZorder = sour->getZOrder();
// 		int descZorder = desc->getZOrder();
// 		sour->setZOrder(descZorder);
// 		desc->setZOrder(sourZorder);
	}
	
	IrrWidget* IrrContainer::getWidgetByName( const char* name )
	{
		pIrrWidgetItor itor = m_Childrens.begin();
		IrrWidget* widget = NULL;
		for (itor = m_Childrens.begin();itor!=m_Childrens.end();itor++)
		{
			widget = *itor;
			if(widget->getName() == name)
			{
				break;
			}
		}
		return widget;
	} 


	IrrWidget* IrrContainer::getWidgetByPos( float x,float y )
	{
		IrrWidget* widget = NULL;
		IrrRect rc = this->getWidgetRect();
		if(rc.containsVector2D(x,y))
		{
			pIrrWidgetItor itor = m_Childrens.begin();
			for (itor = m_Childrens.begin();itor!=m_Childrens.end();itor++)
			{
				if((*itor)->isVisible() && (*itor)->getWidgetRect().containsVector2D(x,y))
				{
					widget = *itor;
					break;
				}
			}
		}
		return widget;
	}


	IrrUint IrrContainer::numberOfChildren() const
	{
		return m_Childrens.size();
	}

	
	//////////////////////////////////////////////////////////////////////////
	void IrrContainer::handleDown( IrrUIEvent& event )
	{

	}

	void IrrContainer::handleUp( IrrUIEvent& event )
	{

	}

	void IrrContainer::handleClick( IrrUIEvent& event )
	{

	}

	void IrrContainer::handleMoveIn( IrrUIEvent& event )
	{

	}

	void IrrContainer::handleMove( IrrUIEvent& event )
	{

	}

	void IrrContainer::handleMoveOut( IrrUIEvent& event )
	{

	}


	//////////////////////////////////////////////////////////////////////////
}